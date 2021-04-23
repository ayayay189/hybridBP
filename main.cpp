#include <pin.H>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "predictors/predictor.h"
#include "predictors/two_bit_saturating_counter_predictor.h"
#include "predictors/perceptron_predictor.h"
#include "predictors/gshare.h"
#include "predictors/hybrid.h"

ostream *out = &cerr;
// Contains all the predictors that should be used when instrumentating a
// program with this Pin tool.
std::vector<int> xs (3,100);

std::vector<bp::Predictor*> bps;
bp::Hybrid *d = new bp::Hybrid();
void PopulateVector(){
  
  
  bp::TwoBitSaturatingCounterPredictor *a=new bp::TwoBitSaturatingCounterPredictor();// = new bp::TwoBitSaturatingCounterPredictor();
  bp::PerceptronPredictor *b = new bp::PerceptronPredictor();// = new bp::PerceptronPredictor();
  //bp::GsharePredictor *c = new bp::GsharePredictor();// = new bp::PerceptronPredictor();
  
 
  bps.push_back(a);
  bps.push_back(b);
  //bps.push_back(c);
    
}



// Runs the branch at the given address through each of the branch predictors
// with whether the branch was taken and its instruction mnemonic.
void ProcessBranch(ADDRINT pc, bool brTaken, void *arg) { // ADDRINT: the address of the instrumented instruction
  string *mnemonic = reinterpret_cast<string *>(arg);
  
  //single predictor
  for (bp::Predictor *bp : bps) {
    bp->GetPredictionAndUpdate(pc, brTaken, mnemonic);
  }
  //hybrid predictor
  //d->GetPredictionAndUpdate(pc, brTaken, mnemonic, bps);
     
}

// Installs a call on conditional branches that then calls through to our
// branch predictors.
void InstrumentInstruction(INS ins, void *v) {
  if (INS_IsBranch(ins) && INS_HasFallThrough(ins)) {
    string *mnemonic = new string(INS_Mnemonic(ins));
    cout << "mnemonic: " << mnemonic << " value: " << *mnemonic << endl;
    //Insert a call to ProcessBranch
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) ProcessBranch, 
        IARG_INST_PTR, IARG_BRANCH_TAKEN, IARG_PTR, mnemonic, IARG_END);
  }
}

// Once the program has terminated, prints out all the branch predictor results
// and statistics.
void Finished(int code, void *v) {
  *out << endl << "Done! Results:" << endl << endl;
  for (bp::Predictor *bp : bps) {
    bp->PrintStatistics(out);
  }
   //d->PrintStatistics(out, bps);
}

int main(int argc, char *argv[]) {
  cout << argc << endl;
  cout << *argv << endl;
  PIN_Init(argc, argv);
  INS_AddInstrumentFunction(InstrumentInstruction, 0);
  PIN_AddFiniFunction(Finished, 0);
  PopulateVector();

  *out << "Running with the following branch predictor(s):" << endl;
  for (bp::Predictor *bp : bps) {
    *out << "in the loop";
    *out << "  " << bp->get_name() << endl;
  }
  *out << endl;

  PIN_StartProgram();

  return 0;
}
