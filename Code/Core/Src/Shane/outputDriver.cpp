#include "allIncludes.h"

outputDriver::outputDriver(dacDriver *DACchannel1I, dacDriver *DACchannel2I,
		displayQueue *displayInfoQI) {
	displayInfoQ = displayInfoQI;
	DACchannel1 = DACchannel1I;
	DACchannel2 = DACchannel2I;
	DACchannel1->enableTimer();
	DACchannel2->enableTimer();
	update();
}

void outputDriver::update() {
	oldFreq1 = DACchannel1->getFreq();
	oldFreq2 = DACchannel2->getFreq();
	DACchannel1->update();
	DACchannel2->update();
	displayInfoValues toWrite = {DACchannel1->getFreq(),DACchannel1->getAmp(),DACchannel1->getWave(),
			DACchannel2->getFreq(),DACchannel2->getAmp(),DACchannel2->getShift(),DACchannel2->getWave()};
//	if(DACchannel1->getFreq() == DACchannel2->getFreq() && oldFreq1 != oldFreq2 && DACchannel2->getWave() != ECHO){
//		DACchannel1->restartDMA();
//		DACchannel2->restartDMA();
//	}
	displayInfoQ->enqueue(toWrite);

}
