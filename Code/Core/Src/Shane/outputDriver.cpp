#include "allIncludes.h"

outputDriver::outputDriver(dacDriver *DACchannel1I, dacDriver *DACchannel2I,
		displayQueue *displayInfoQI) {
	if(DACchannel1I == nullptr || DACchannel2I == nullptr || displayInfoQI == nullptr){
		NVIC_SystemReset();
	}
	assert(DACchannel1I != nullptr && DACchannel2I != nullptr && displayInfoQI != nullptr);
	displayInfoQ = displayInfoQI;
	DACchannel1 = DACchannel1I;
	DACchannel2 = DACchannel2I;
	update();
}

void outputDriver::update() {
	DACchannel1->getFreq(&oldFreq1);
	DACchannel2->getFreq(&oldFreq2);
	WaveShape oldShape;
	DACchannel2->getWave(&oldShape);
	bool update1 = DACchannel1->update();
	bool update2 = DACchannel2->update();

	if(update1 || update2){
		uint16_t newFreq1;
		uint16_t newFreq2;
		uint16_t newAmp1;
		uint16_t newAmp2;
		uint16_t newShift2;
		WaveShape ch1NewShape;
		WaveShape ch2NewShape;

		DACchannel1->getAmp(&newAmp1);
		DACchannel2->getAmp(&newAmp2);
		DACchannel1->getFreq(&newFreq1);
		DACchannel2->getFreq(&newFreq2);
		DACchannel2->getShift(&newShift2);
		DACchannel1->getWave(&ch1NewShape);
		DACchannel2->getWave(&ch2NewShape);

		displayInfoValues toWrite = {newFreq1,newAmp1,ch1NewShape,
				newFreq2,newAmp2,newShift2,ch2NewShape};
		if((ch2NewShape == ECHO) && (oldShape != ECHO)){
			DACchannel1->restartDMA();
			DACchannel2->restartDMA();
		}else if((oldFreq1 != oldFreq2) && (newFreq1== newFreq2)){
			DACchannel1->restartDMA();
			DACchannel2->restartDMA();
		}
		bool enqueued = displayInfoQ->enqueue(toWrite);
		if(enqueued || !enqueued){
			return;
		}
	}
}
