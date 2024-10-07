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
extern DMA_HandleTypeDef hdma_dac_ch1;
extern DMA_HandleTypeDef hdma_dac_ch2;

//baseWaves waves;

//bool update1 = true;
//bool update2 = true;

void cpp_main(void){
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1); // Start the DAC
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);

	//set up the queues
	signalQueue channel1;
	signalQueue channel2;

	displayQueue displayInfo;

	//start i2c + setup display
	display mainDisplay(&hi2c1, &displayInfo);


	//a starting signal will need to be created + enqueued here
	//this will need to occur in someone else's code at some point
	//channel1.enqueue(*(waves.getSinePlot()));
	//channel2.enqueue(*(waves.getSinePlot()));



	struct dacSetup DACchannel1 = {&hdac1,DAC_CHANNEL_1,&htim2,&channel1};
	struct dacSetup DACchannel2 = {&hdac1,DAC_CHANNEL_2,&htim6,&channel2};


	dacDriver DriverCh1(&DACchannel1, &hdma_dac_ch1);
	dacDriver DriverCh2(&DACchannel2, &hdma_dac_ch2);

	static outputDriver outputDriverI(&DriverCh1, &DriverCh2, &DACchannel1, &DACchannel2, &displayInfo);

	//draw freq + amp to the display
	mainDisplay.getNewValues();

	while(1){
		//outputDriverI.update();
	}
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac) {
	//update1 = true;
}

void HAL_DAC_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac) {
}
