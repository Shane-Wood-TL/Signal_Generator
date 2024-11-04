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
	DACchannel1->enableTimer();
	DACchannel2->enableTimer();
	update();
}

void outputDriver::update() {
	oldFreq1 = DACchannel1->getFreq();
	oldFreq2 = DACchannel2->getFreq();
	WaveShape oldShape = DACchannel2->getWave();
	bool update1 = DACchannel1->update();
	bool update2 = DACchannel2->update();

	if(update1 || update2){
		uint16_t newAmp1 = DACchannel1->getAmp();
		uint16_t newAmp2 = DACchannel2->getAmp();
		uint16_t newFreq1 =DACchannel1->getFreq();
		uint16_t newFreq2 = DACchannel2->getFreq();
		uint8_t newShift2 = DACchannel2->getShift();
		WaveShape ch1NewShape = DACchannel1->getWave();
		WaveShape ch2NewShape = DACchannel2->getWave();
		if(newAmp1 > 4095){
			newAmp1 = 4095;
		}
		if(newAmp2 > 4095){
					newAmp2 = 4095;
		}
		if(newFreq1 <= 0){
			newFreq1 = 1;
		}
		if(newFreq2 <= 0){
			newFreq1 = 2;
		}
		if(newShift2 > 255){
			newShift2 = 255;
		}
		if((ch1NewShape != SINE && ch1NewShape != SQUARE && ch1NewShape != PULSE) || (ch1NewShape == ECHO)){
			ch1NewShape = SINE;
		}
		if((ch2NewShape != SINE && ch2NewShape != SQUARE && ch2NewShape != PULSE) && ch2NewShape != ECHO){
			ch2NewShape = SINE;
		}
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
