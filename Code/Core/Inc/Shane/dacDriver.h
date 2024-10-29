/*
 * dacDriver.h
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#ifndef INC_SHANE_DACDRIVER_H_
#define INC_SHANE_DACDRIVER_H_

#include "allIncludes.h"
//https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Projects/NUCLEO-L432KC/Examples/DAC/DAC_SignalsGeneration/readme.txt
//https://deepbluembedded.com/stm32-dac-sine-wave-generation-stm32-dac-dma-timer-example/

class dacDriver{
	DAC_HandleTypeDef *hdac;
	uint32_t DacChannel;
	TIM_HandleTypeDef *timerInstance;
	signalQueue *signalQueueInstance;
	signalInfo currentSignal;
	uint32_t currentReloadValue = 0;
	void setReload();
	public:
		dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I, TIM_HandleTypeDef *timer1Il, signalQueue *channel1I);
		//signalInfo* getSignalInfo();
		void update();
		void enableTimer();
		uint32_t getFreq();
		uint16_t getAmp();
		uint8_t getShift();
		WaveShape getWave();
};


#endif /* INC_SHANE_DACDRIVER_H_ */
