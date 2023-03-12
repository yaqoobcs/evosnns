#pragma once
#include "typedefs.h"
#include "Parameters.h"
extern Parameters params;
class ComputationalUnit
{
public:

	double inv_C;
	double inv_taum;
	double DeltaT;
	double aDiv1000;
	double b;
	double i_offset;
	double inv_tauw;
	double Vreset;
	double Vresting;
	double Vthreshold;
	double Vspike;
	double inv_tau_syn_E;
	double inv_tau_syn_I;
	double e_rev_E;
	double e_rev_I;
	double absRefractoryTime;
	int spikeCount;
	bool hasSpiked;

	NeuronType nModel; 

	ComputationalUnit(void);
	~ComputationalUnit(void);

	//void makeNeuronOfType(void);
	void createNeuron();
	double resetVoltage();
	double resetAdaptation(double Adaptation);
	double updateVoltage(double currentVoltage, double excitatory_conductance, double inhibatory_conductance, double Adaptation);
	double updateAdaptation(double Adaptation, double currentVoltage);
	double updateExcitatoryCond(double current_excitatory_conductance);
	double updateInhibitoryCond(double current_inhibatory_conductance);
	bool hasSpike(double voltage);

};

