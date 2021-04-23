# Branch predictor Pin Tool
This repository provides a Pin tool that can be used for performing branch prediction

I started the implementation based on a completed branch prediction pintools from GitHub. The link is: https://github.com/kodbe/branch-predictor. I used the 2-bit counter predictor and perceptron branch predictor from it and implement gshare and hybrid branch predictor (gshare+2-bit counter and 2-bit counter + perceptron).

## algorithms
implementations of branch predictors:

1. Two-bit saturating counter branch predictor
2. Perceptron branch predictor 
3. Gshare branch predictor
4. Hybrid branch predictor

To chage from one predictor to hybrid predictor, you need to modify main.cpp ProcessBranch function from single predictor to hybrid predictor and then compile again.

Additional branch predictors can be implemented by inheriting from the Predictor
abstract class.

## Running
To run, make sure you have Pin installed. You can then compile:

    export PIN_ROOT=/path/to/pin
    make

and instrument any executable:

    ~/pin-3.18-98332-gaebd7b1e6-gcc-linux/pin -t obj-intel64/branch_predictor.so -- ~/basicmath_large
