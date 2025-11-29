#pragma once
#include <vector>
#include "ComputationalUnit.h"

using namespace std;
class Neuron {

public:
    // state variables
    double voltage;
    double adaptation;
    double exConductance;
    double inConductance;
    int synapticDelayBuffer;
    int delayCount;
    // parameters
    ComputationalUnit cUnit;

    double refrectoryPeriod;
    vector<bool> spikeBitmap;

    vector<double> voltageBuffer;


    Neuron(void);
    ~Neuron(void);
};
