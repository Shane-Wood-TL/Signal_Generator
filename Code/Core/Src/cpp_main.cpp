/*
 * mainCpp.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */
#include "main.h"
#include "allIncludes.h"


extern "C" void cpp_main(void);
extern I2C_HandleTypeDef hi2c1;
extern DAC_HandleTypeDef hdac1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;



void cpp_main(void){
	//baseWaves waves;

	//set up the queues
	inputQueue inputQueueInstance;
	signalQueue channel1;
	signalQueue channel2;

	displayQueue displayInfo;

	//start i2c + setup display
	display mainDisplay(&hi2c1, &displayInfo);
	//signalInfo channelB = waves.shift(*waves.getSinePlot(), 128);

	//a starting signal will need to be created + enqueued here
	//this will need to occur in someone else's code at some point
	//channel1.enqueue(*(waves.getSinePlot()));
	//channel2.enqueue(channelB);



	struct dacSetup DACchannel1 = {&hdac1,DAC_CHANNEL_1,&htim2,&channel1};
	struct dacSetup DACchannel2 = {&hdac1,DAC_CHANNEL_2,&htim6,&channel2};


	dacDriver DriverCh1(&DACchannel1);
	dacDriver DriverCh2(&DACchannel2);

	outputDriver outputDriverI(&DriverCh1, &DriverCh2, &DACchannel1, &DACchannel2, &displayInfo);

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
	memoryChecker mainMemoryChecker(memoryBarrier);

	//draw freq + amp to the display
	mainDisplay.getNewValues();

	while(1){
		//outputDriverI.update();
	}
}
