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



void cpp_main(void){
	//set up the queues
	inputQueue inputQueueInstance;
	signalQueue channel1;
	signalQueue channel2;
	displayQueue displayQueueInstance;

	//Waves waves(&inputQueueInstance, &channel1, &channel2);

	//applicationLayer mainHandler(&inputQueueInstance, &channel1, &channel2);

	dacDriver DriverCh1(&hdac1,DAC_CHANNEL_1,&htim2,&channel1);
	dacDriver DriverCh2(&hdac1,DAC_CHANNEL_2,&htim6,&channel2);
	outputDriver outputDriverI(&DriverCh1, &DriverCh2, &displayQueueInstance);

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
	memoryChecker mainMemoryChecker(memoryBarrier);




	//start spi + setup display
	display mainDisplay(&hspi3, &displayQueueInstance);
	//draw freq + amp to the display
	mainDisplay.getNewValues();

	uint8_t wasteofTime = 0;
	while(1){
		struct inputValues test = {0,true,0,0,0,0,0};
		wasteofTime = 0;
		inputQueueInstance.enqueue(test);
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

