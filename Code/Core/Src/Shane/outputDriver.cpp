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
	DACchannel1->update();
	DACchannel2->update();
	displayInfoValues toWrite = {DACchannel1->getFreq(),DACchannel1->getAmp(),DACchannel1->getWave(),
			DACchannel2->getFreq(),DACchannel2->getAmp(),DACchannel2->getShift(),DACchannel2->getWave()};
	displayInfoQ->enqueue(toWrite);

}
