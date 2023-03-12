#include "stdafx.h"
#include "Neuron.h"


Neuron::Neuron(void)
{
	voltage=-70.0;
	adaptation=0.0;
	exConductance=0.0;
	inConductance=0.0;
	cUnit.createNeuron();
	synapticDelayBuffer=0;
	delayCount = 0;

	spikeBitmap.clear();
	voltageBuffer.clear();
	refrectoryPeriod=0;
}




Neuron::~Neuron(void)
{
}
