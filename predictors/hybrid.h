#ifndef hybrid_H_
#define hybrid_H_

#include "predictors/predictor.h"
#include "predictors/two_bit_saturating_counter_predictor.h"
#include "predictors/gshare.h"
#include "predictors/perceptron_predictor.h"
#include <pin.H>

#include <ostream>
#include <map>
#include <string>

namespace bp {
    
    
    class Hybrid {
    public:
        Hybrid();
        
        bool GetPredictionAndUpdate(ADDRINT pc, bool br_taken,
                              string *mnemonic, std::vector<bp::Predictor*> bps) ;
        void PrintStatistics(std::ostream *out, std::vector<bp::Predictor*> bps) const ;
        
    private:
        //int counter = 2;
        static const int size = 16;
        int chooserTable[size]; // two bit counter chooserTable to decide which predictor to use
        
        int get_key(ADDRINT pc) const  { return pc % size; };
    };
}

#endif
