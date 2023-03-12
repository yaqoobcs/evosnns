#include "stdafx.h"
#include "ComputationalUnit.h"
#include <math.h>


ComputationalUnit::ComputationalUnit(void)
{
	inv_C= 0.0;
	inv_taum= 0.0;
	DeltaT= 0.0;
	aDiv1000= 0.0;
	b= 0.0;
	i_offset= 0.0;
	inv_tauw= 0.0;
	Vreset= 0.0;
	Vresting= 0.0;
	Vthreshold= 0.0;
	Vspike= 0.0;
	inv_tau_syn_E= 0.0;
	inv_tau_syn_I= 0.0;
	e_rev_E= 0.0;
	e_rev_I= 0.0;
	absRefractoryTime= 0.0;
	spikeCount= 0;
	hasSpiked= false;
}

void ComputationalUnit::createNeuron()
{
	if(params.neuronalType ==LIF)
	{
		absRefractoryTime = 0;
		Vreset = -70.0;
		Vthreshold = -50.0;
		inv_taum = 1.0/20.0;
		inv_tau_syn_E = 1.0/5.0;
		inv_tau_syn_I = 1.0/5.0;
		e_rev_E = 0;
		e_rev_I = -70.0;
		inv_C  = 1.0/0.2;
		Vresting = -70.0;
		i_offset = 0.0;	
		nModel=LIF;

	}
	else if(params.neuronalType==ADX)
	{
		absRefractoryTime= 0.0;
		Vreset= -58.0;
		Vresting= -70.0;
		Vthreshold= -50.0;
		Vspike= 0.0;
		inv_taum= 1.0/20.0;
		DeltaT= 2.0;
		inv_tau_syn_E= 1.0/5.0;
		inv_tau_syn_I= 1.0/5.0;
		e_rev_E= 0.0;
		e_rev_I= -70.0;
		inv_C= 1.0/0.20;
		i_offset= 0;
		inv_tauw= 1.0/30.0;
		aDiv1000= 2.0/1000.0;
		b= 0.0;
		spikeCount= 0;
		hasSpiked= false;
		nModel=ADX;

	}

}
double ComputationalUnit::resetVoltage()
{

	return Vreset;
}

bool ComputationalUnit::hasSpike(double voltage)
{
	double VCut;
	if (nModel==LIF)
		VCut = Vthreshold;
	else if (nModel==ADX)
		VCut = Vspike;
	else 
		VCut = Vthreshold;

	if (voltage >= VCut)
			return true;	
	else
		return false;
}

double ComputationalUnit::resetAdaptation(double Adaptation)
{
	Adaptation += b; 
	return Adaptation; 
}

double ComputationalUnit::updateAdaptation(double Adaptation, double currentVoltage)
{
	if (nModel==ADX)
			return 	Adaptation + ((aDiv1000 * (currentVoltage - Vresting) - Adaptation) * inv_tauw)*params.timeStep; 
	else if (nModel == IZH)
		return	Adaptation + ((aDiv1000 * (currentVoltage - Vresting)  - Adaptation) * inv_tauw)*params.timeStep;	
	else
		return Adaptation;
}

double ComputationalUnit::updateVoltage(double currentVoltage, double excitatory_conductance, double inhibitory_conductance, double Adaptation)
{
	double voltageChange;
	if (nModel==LIF)
	{
		voltageChange=(
			(Vresting - currentVoltage)*inv_taum + 
			(excitatory_conductance*(e_rev_E-currentVoltage) + inhibitory_conductance*(e_rev_I-currentVoltage) + i_offset)*inv_C
			)*params.timeStep;
	}
	else if (nModel==ADX)
	{
		voltageChange = (
			(Vresting - currentVoltage + DeltaT * exp((currentVoltage - Vthreshold)/DeltaT))*inv_taum +
			(excitatory_conductance*(e_rev_E - currentVoltage) + inhibitory_conductance*(e_rev_I - currentVoltage) + i_offset - Adaptation)*inv_C 
			)*params.timeStep;
	}
	else if (nModel== IZH)
	{
		voltageChange =  (
			0.04 * pow(currentVoltage, 2) + 5 * currentVoltage + 140 - Adaptation 
			+ (excitatory_conductance*(e_rev_E - currentVoltage) + inhibitory_conductance*(e_rev_I - currentVoltage) + i_offset)*inv_C
			)*params.timeStep;
	}
	else
		voltageChange=0;

	return currentVoltage+voltageChange;

}

double ComputationalUnit::updateExcitatoryCond(double current_excitatory_conductance)
{
		return current_excitatory_conductance - current_excitatory_conductance*inv_tau_syn_E*params.timeStep;
}

double ComputationalUnit::updateInhibitoryCond(double current_inhibitory_conductance)
{
		return current_inhibitory_conductance - current_inhibitory_conductance*inv_tau_syn_I*params.timeStep;
}

ComputationalUnit::~ComputationalUnit(void)
{
}
