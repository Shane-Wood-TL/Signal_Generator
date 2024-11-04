/*
 * dacDriver.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#include "allIncludes.h"

dacDriver::dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I,
		TIM_HandleTypeDef *timer1I, signalQueue *channel1I) {
	if (hdacI == nullptr || timer1I == nullptr || channel1I == nullptr) {
		NVIC_SystemReset();
	}
	assert(hdacI != nullptr);
	assert(timer1I != nullptr);
	assert(channel1I != nullptr);
	hdac = hdacI;
	DacChannel = DacChannel1I;
	timerInstance = timer1I;
	signalQueueInstance = channel1I;

	//ensure that something is in current signal
	HAL_StatusTypeDef DMA = HAL_DAC_Start_DMA(hdac, DacChannel,
			currentSignal.signalLocations,
			waveFormRes, DAC_ALIGN_12B_R);
	switch (DMA) {
	case HAL_ERROR: {
		//DMA failed to start, not recoverable
		NVIC_SystemReset();
		break;
	}
	default: {
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
	timerInstance->Instance->CNT = 0; //reset count incase it is above reload value
}

uint16_t dacDriver::getFreq() {
	return currentSignal.frequency;
}
uint16_t dacDriver::getAmp() {
	return currentSignal.amp;
}
uint8_t dacDriver::getShift() {
	return currentSignal.shiftAmount;
}
WaveShape dacDriver::getWave() {
	return currentSignal.wave;
}

bool dacDriver::update() {
	uint16_t oldFreq = currentSignal.frequency;

	bool newValue = signalQueueInstance->dequeue(&currentSignal);
	if (newValue) {
		assert(currentSignal.frequency > 0);
		if (oldFreq != currentSignal.frequency) {
			setReload(); //set new period
		}
	}else{
		return false;
	}
	//ensure that something is in current signal
	return newValue;
}

void dacDriver::enableTimer() {
	timerInstance->Instance->CR1 |= TIM_CR1_CEN;
}

void dacDriver::restartDMA() {
	setReload();
	HAL_StatusTypeDef DMA = HAL_DAC_Stop_DMA(hdac, DacChannel);
	//check if it turned it off here
	DMA = HAL_DAC_Start_DMA(hdac, DacChannel, currentSignal.signalLocations,
	waveFormRes, DAC_ALIGN_12B_R);
	switch (DMA) {
	case HAL_ERROR: {
		//problem, but recoverable.
		break;
	}
	default: {
		return;
		break;
	}
	}
}
