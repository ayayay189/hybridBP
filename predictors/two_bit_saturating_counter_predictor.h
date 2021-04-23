

#ifndef PREDICTORS_TWO_BIT_SATURATING_COUNTER_PREDICTOR_H_
#define PREDICTORS_TWO_BIT_SATURATING_COUNTER_PREDICTOR_H_

#include <pin.H>

#include <string>

#include "predictors/predictor.h"

namespace bp {



// Simple branch predictor that uses the TwoBitState FSM to train predictions
// for addresses that hash to a given entry.
class TwoBitSaturatingCounterPredictor : public PredictorImpl<TwoBitState> {
  // The number of entries in this predictor.
  static const int kSize = 65536;
  // The array of all the states.
  TwoBitState states_[kSize];

 public:
  TwoBitSaturatingCounterPredictor();
  string get_name() const override {
    return "Two-bit saturating counter branch predictor (";
  }

 private:
  TwoBitState GetPrediction(int key) const override;
  void Update(int key, TwoBitState prediction, bool br_taken) override;
  int get_key(ADDRINT pc) const override { return pc % kSize; };
  bool as_boolean(TwoBitState t) const override {
    return t == WEAKLY_TAKEN || t == STRONGLY_TAKEN;
  }
};

}  // namespace bp

#endif  // PREDICTORS_TWO_BIT_SATURATING_COUNTER_PREDICTOR_H_
