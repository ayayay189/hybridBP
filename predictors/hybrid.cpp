#include <pin.H>

#include <string>

#include "predictors/hybrid.h"


namespace bp{
    
    Hybrid::Hybrid(){
        //init chooserTable to state 3
        for(int i = 0; i< size; i++){
            chooserTable[i] = 3;
        }
    }
    
    bool Hybrid::GetPredictionAndUpdate(ADDRINT pc, bool br_taken, string *mnemonic,
                                        std::vector<bp::Predictor*> bps){
        //for (bp::Predictor *bp : bps) {
        bool cur;
        int index = get_key(pc);//get index of branch address
        
        if(chooserTable[index]>=3){// >=3, use second Predictor
            
            cur = bps[1]->GetPredictionAndUpdate(pc, br_taken, mnemonic);
            
            if(cur == br_taken && chooserTable[index]<4){ // predict is true
                chooserTable[index]++;
            }
            else if(cur != br_taken ){ // mis predict
                chooserTable[index]--;
            }
        }
        else{ // < 3, first predictor
            
            cur = bps[0]->GetPredictionAndUpdate(pc, br_taken, mnemonic);
            
            if(cur == br_taken && chooserTable[index]>1){
                chooserTable[index]--;
            }
            else if(cur != br_taken ){
                chooserTable[index]++;
            }
        }
        //}
        return true;
    }
    
    void Hybrid::PrintStatistics(std::ostream *out, std::vector<bp::Predictor*> bps) const{
        //*out <<  "analysis results: " << endl;
        for (bp::Predictor *bp : bps) {
            bp->PrintStatistics(out);
        }
    }
}
