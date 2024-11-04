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
static Semaphore button;
static Semaphore knobs;
static Semaphore switches;
extern "C" void myTIM7_IRQHandler(void) {
	if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE)){
		if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE)){// != RESET) {
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); // Clear the interrupt flag
			button.enqueue(1);
			knobs.enqueue(1);
			switches.enqueue(1);
	    }
	}
}

void cpp_main(void){
	htim7.Instance->CR1 |= TIM_CR1_CEN;
	//set up the queues
	inputQueue inputQueueInstance;
	signalQueue channel1;
	signalQueue channel2;

	//Waves waves(&inputQueueInstance, &channel1, &channel2);


	displayQueue displayQueueInstance;

	//applicationLayer mainHandler(&inputQueueInstance, &channel1, &channel2);

	dacDriver DriverCh1(&hdac1,DAC_CHANNEL_1,&htim2,&channel1);
	dacDriver DriverCh2(&hdac1,DAC_CHANNEL_2,&htim6,&channel2);
	outputDriver outputDriverI(&DriverCh1, &DriverCh2, &displayQueueInstance);

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
	memoryChecker mainMemoryChecker(memoryBarrier);


	SwitchDriver channel(GPIOA, 7, &switches);
	ButtonDriver mode(GPIOB, 0, &button);

	KnobDriver freq(GPIOA, 12, GPIOA, 11);
	KnobDriver amp(GPIOA, 9, GPIOA, 10);
	KnobDriver shift(GPIOA, 8, GPIOB, 1);

	InputDriver input(&amp, &freq, &shift, &channel, &mode, &inputQueueInstance, &knobs); //fill nullptr with semaphore knob


	//start spi + setup display
	display mainDisplay(&hspi3, &displayQueueInstance);
	//draw freq + amp to the display
	mainDisplay.getNewValues();
	uint8_t wasteofTime = 0;
	//bool x = 0;
	//bool y = 0;
	//bool z = 0;
	while(1){
		input.checkForUpdates();
		//struct inputValues test = {0,true,0,0,0,0,0}; too many initializers for 'inputValues'
		wasteofTime = 0;
		//inputQueueInstance.enqueue(test); test struct has been commented out

		//button.dequeue(&x);
		//knobs.dequeue(&z);
		//switches.dequeue(&y);

		//waves.update();
		//mainHandler.update();
		outputDriverI.update();
		mainDisplay.getNewValues();
		wasteofTime++;
	}
}




//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
//uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
//memoryChecker mainMemoryChecker(memoryBarrier);
////		struct inputValues
////			{
////				int8_t Switch;
////				bool isButtonPressed;
////				int8_t AmpKnob1;
////				int8_t FreqKnob1;
////				int8_t AmpKnob2;
////				int8_t FreqKnob2;
////				int8_t DelayKnob2;
////			};
//		//struct inputValues test = {1,true,0,0,0,0,0};
//		//struct inputValues test = {0,false,0,0,0,0,0};

