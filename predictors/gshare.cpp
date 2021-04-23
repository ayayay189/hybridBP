#include <string>

#include "predictors/gshare.h"

namespace bp {

GsharePredictor::GsharePredictor() {
  for (int i = 0; i < kSize; ++i) {
    states_[i] = WEAKLY_TAKEN;
  }
}

TwoBitState GsharePredictor::GetPrediction(int key) const {
  return states_[key];
}

// Implements the two-bit FSM.
void GsharePredictor::Update(int key, TwoBitState prediction,
    bool br_taken) {
  switch (states_[key]) {
    case STRONGLY_NOT_TAKEN:
      states_[key] = br_taken ? WEAKLY_NOT_TAKEN : STRONGLY_NOT_TAKEN;
      break;
    case WEAKLY_NOT_TAKEN:
      states_[key] = br_taken ? WEAKLY_TAKEN : STRONGLY_NOT_TAKEN;
      break;
    case WEAKLY_TAKEN:
      states_[key] = br_taken ? STRONGLY_TAKEN : WEAKLY_NOT_TAKEN;
      break;
    case STRONGLY_TAKEN:
      states_[key] = br_taken ? STRONGLY_TAKEN : WEAKLY_TAKEN;
      break;
  }
  gr <<= 1;
  gr |= br_taken;
}
}  // namespace bp
