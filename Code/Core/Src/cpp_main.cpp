/*
 * mainCpp.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */
#include "allIncludes.h"

extern "C" void cpp_main(void);
extern SPI_HandleTypeDef hspi3;
extern DAC_HandleTypeDef hdac1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;
static Semaphore button;
static Semaphore knobs;
static Semaphore switches;
static Semaphore memoryCheckerSemaphore;

extern "C" void myTIM7_IRQHandler(void) {
	if (__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE)) {
		if (__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE)) {
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); // Clear the interrupt flag
			button.enqueue(1);
			knobs.enqueue(1);
			switches.enqueue(1);
		}
	}
}

extern "C" void myTIM16_IRQHandler(void) {
	if (__HAL_TIM_GET_FLAG(&htim16, TIM_FLAG_UPDATE)) {
		if (__HAL_TIM_GET_IT_SOURCE(&htim16, TIM_IT_UPDATE)) { // != RESET) {
			__HAL_TIM_CLEAR_IT(&htim16, TIM_IT_UPDATE); // Clear the interrupt flag
			memoryCheckerSemaphore.enqueue(1);
		}
	}
}

void cpp_main(void) {
	static_assert(sizeof(uint32_t) ==4);
	static_assert(sizeof(uint16_t) ==2);
	static_assert(sizeof(uint8_t) ==1);
	static_assert(waveFormRes > 0);
	//start the semaphore timers
	htim7.Instance->CR1 |= TIM_CR1_CEN;
	htim16.Instance->CR1 |= TIM_CR1_CEN;

	//set up the queues
	inputQueue inputQueueInstance;
	uint32_t barrierA[8] = { 1, 11, 111, 1111, 1, 11, 111, 1111 };
	memoryChecker miniMemBarrierA(barrierA, 8);

	signalQueue channel1;
	uint32_t barrierB[8] = { 1, 11, 111, 1111, 1, 11, 111, 1111 };
	memoryChecker miniMemBarrierB(barrierB, 8);

	signalQueue channel2;
	uint32_t barrierC[8] = { 1, 11, 111, 1111, 1, 11, 111, 1111 };
	memoryChecker miniMemBarrierC(barrierC, 8);

	displayQueue displayQueueInstance;
	uint32_t barrierD[8] = { 1, 11, 111, 1111, 1, 11, 111, 1111 };
	memoryChecker miniMemBarrierD(barrierD, 8);

	//application layer / wave gen
	applicationLayer mainHandler(&inputQueueInstance, &channel1, &channel2);

	//dac drivers
	dacDriver DriverCh1(&hdac1, DAC_CHANNEL_1, &htim2, &channel1);
	dacDriver DriverCh2(&hdac1, DAC_CHANNEL_2, &htim6, &channel2);

	//output driver
	outputDriver outputDriverI(&DriverCh1, &DriverCh2, &displayQueueInstance);

	//input drivers
	SwitchDriver channel(channelSwitchPort, channelSwitchPin, &switches);
	ButtonDriver mode(modeButtonPort, modeButtonPin, &button);

	KnobDriver freq(freqKnobAPort, freqKnobAPin, freqKnobBPort, freqKnobBPin);
	KnobDriver amp(ampKnobAPort, ampKnobAPin, ampKnobBPort, ampKnobBPin);
	KnobDriver shift(shiftKnobAPort, shiftKnobAPin, shiftKnobBPort,
			shiftKnobBPin);

	//overall input driver
	InputDriver input(&amp, &freq, &shift, &channel, &mode, &inputQueueInstance,
			&knobs); //fill nullptr with semaphore knob

	//display setup
	struct ssd1306Setup displaySetup = { SSD1306VerticalRes,
			SSD1306HorizontalRes, dcPort, dcPin, rstPort, rstPin };
	//start spi + setup display
	display mainDisplay(&hspi3, &displayQueueInstance, &displaySetup);
	//draw freq + amp to the display
	mainDisplay.getNewValues();

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = { 1, 11, 111, 1111, 1, 11, 111, 1111, 1, 11,
			111, 1111, 1, 11, 111, 1111, 1, 11, 111, 1111, 1, 11, 111, 1111, 1,
			11, 111, 1111, 1, 11, 111, 1111 };
	memoryChecker largerMemoryChecker(memoryBarrier, 32);

	//all memory barriers combined so they can be indexed using phased execution
	overallMemoryChecker overallMemoryCheckerInstance(&miniMemBarrierA,
			&miniMemBarrierB, &miniMemBarrierC, &miniMemBarrierD,
			&largerMemoryChecker, &memoryCheckerSemaphore);

	while (1) {
		TOGGLE
		//WRITEON
		//WRITEOFF
		input.checkForUpdates(); //updates all input, needs semaphores
		mainHandler.update();
		outputDriverI.update();
		//WRITEON
		mainDisplay.getNewValues();
		overallMemoryCheckerInstance.checkMemory();
	}
}
