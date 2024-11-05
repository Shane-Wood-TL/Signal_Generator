/*
 * dacDriver.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#include "allIncludes.h"

dacDriver::dacDriver(DAC_HandleTypeDef *hdacI, const uint32_t DacChannel1I,
		 TIM_HandleTypeDef *timer1I, signalQueue *channel1I) {
	//check inputs
	if ((hdacI == nullptr) || (timer1I == nullptr) || (channel1I == nullptr)) {
		NVIC_SystemReset();
	}else if(!((DacChannel1I == DAC_CHANNEL_1) ||(DacChannel1I == DAC_CHANNEL_2))){
		NVIC_SystemReset();
	}
	//use asserts
	assert(hdacI != nullptr);
	assert(timer1I != nullptr);
	assert(channel1I != nullptr);
	assert((DacChannel1I == DAC_CHANNEL_1) ||(DacChannel1I == DAC_CHANNEL_2));
	//assign parameters to member variables
	hdac = hdacI;
	DacChannel = DacChannel1I;
	timerInstance = timer1I;
	signalQueueInstance = channel1I;

	//ensure that DMA is started, with it looking at the correct location
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
		break;
	}
	}
	//start the timer for the DAC
	enableTimer();
	return;
}

void dacDriver::setReload() {
	//calculate the new reload value based on prescaling, clock speed and waveForm resolution
	currentReloadValue = (uint32_t) FCLK
			/ ((timerPSC + 1) * (currentSignal.frequency) * waveFormRes);


	//set tje reload value
	timerInstance->Instance->ARR = currentReloadValue;
	timerInstance->Instance->CNT = 0; //reset count in-case it is above reload value
	return;
}

void dacDriver::getFreq(uint16_t *freq) {
	if(freq != nullptr){
		assert(freq != nullptr);
	*freq = currentSignal.frequency;
	}
	return;
}
void dacDriver::getAmp(uint16_t *amp) {
	if(amp != nullptr){
	assert(amp != nullptr);
	*amp = currentSignal.amp;
	}
	return;
}
void dacDriver::getShift(uint16_t *shift) {
	if(shift != nullptr){
	assert(shift != nullptr);
	*shift =  currentSignal.shiftAmount;
	}
	return;
}
void dacDriver::getWave(WaveShape *shape) {
	if(shape != nullptr){
	assert(shape != nullptr);
	*shape = currentSignal.wave;
	}
	return;
}

bool dacDriver::update() {
	uint16_t oldFreq = currentSignal.frequency;

	bool newValue = signalQueueInstance->dequeue(&currentSignal);
	if (newValue) {
		assert(currentSignal.frequency > 0);
		if (oldFreq != currentSignal.frequency) {
			setReload(); //set new period if freq different
		}
	}else{
		return false;
	}
	return newValue;
}

void dacDriver::enableTimer() {
	timerInstance->Instance->CR1 |= TIM_CR1_CEN; //enable the timer
	return;
}

void dacDriver::restartDMA() {
	//set the timer period
	setReload();
	//stop DMA
	HAL_StatusTypeDef DMA = HAL_DAC_Stop_DMA(hdac, DacChannel);
	switch (DMA) {
		case HAL_ERROR: {
			//problem, but recoverable.
			break;
		}
		default: {
			break;
		}
	}
	//restart dma
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
	return;
}
