/*
 * dacDriver.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */


#include "allIncludes.h"


dacDriver::dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I, TIM_HandleTypeDef *timer1I, signalQueue *channel1I) {
	hdac = hdacI;
	DacChannel = DacChannel1I;
	timerInstance = timer1I;
	signalQueueInstance = channel1I;

	//ensure that something is in current signal
	HAL_StatusTypeDef DMA =  HAL_DAC_Start_DMA(hdac, DacChannel, currentSignal.signalLocations,
			waveFormRes, DAC_ALIGN_12B_R);
	switch(DMA){
	case HAL_ERROR:{
		//DMA failed to start, not recoverable
		NVIC_SystemReset();
		break;
	}
	default:{
		return;
		break;
	}
	}
}


void dacDriver::setReload() {
	currentReloadValue = (uint32_t) FCLK
			/ ((timerPSC + 1) * (currentSignal.frequency) * waveFormRes);

	//hal method
	//__HAL_TIM_SET_AUTORELOAD(timerInstance, currentReloadValue);

	//no hal method
	timerInstance->Instance->ARR = currentReloadValue;
}


uint32_t dacDriver::getFreq(){
	return currentSignal.frequency;
}
uint16_t dacDriver::getAmp(){
	return currentSignal.amp;
}
uint8_t dacDriver::getShift(){
	return currentSignal.shiftAmount;
}
WaveShape dacDriver::getWave(){
	return currentSignal.wave;
}

void dacDriver::update() {
	if (signalQueueInstance->dequeue(&currentSignal)) {
			setReload(); //set new period
	}
	//ensure that something is in current signal
}

void dacDriver::enableTimer(){
	timerInstance->Instance->CR1 |= TIM_CR1_CEN;
}

