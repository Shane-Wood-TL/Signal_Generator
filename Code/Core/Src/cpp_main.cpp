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

/*extern TIM_HandleTypeDef htim7;

extern "C" void TIM7_IRQHandler(void) {
    static Semaphore button;
	static Semaphore knobs;
	static Semaphore switches;
	inputValues values = {0,false,0,0,0,0,0};
	static bool previousStateButton = false;
	static bool switchChange = false;
	if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET) {
		if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != RESET) {
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); // Clear the interrupt flag
	        // Button press detection
	        if(values.isButtonPressed != previousStateButton) {
	        	button.enqueue(1);
	            previousStateButton = values.isButtonPressed;
	        }

	        // Knob change detection
	        if(values.AmpKnob1 != 0 || values.AmpKnob2 != 0 ||
	        	values.FreqKnob1 != 0 || values.FreqKnob2 != 0 ||
	            values.DelayKnob2 != 0) {
	            knobs.enqueue(1);
	        }

	        // Switch change detection
	        if(values.Switch != switchChange) {
	        	switches.enqueue(1);
	            switchChange = values.Switch; // Update the tracked switch state
	        }
	    }
	}
}*/

void cpp_main(void){
	//baseWaves waves;

	//set up the queues
	inputQueue inputQueueInstance;
	signalQueue channel1;
	signalQueue channel2;
	Semaphore button;
	Waves waves(&inputQueueInstance, &channel1, &channel2);
	/*Semaphore switchs;
	Semaphore knobs;*/
	//button.enqueue(1);




	displayQueue displayInfo;

	inputValues x = {0, false, 1,1,1,1,0};
	inputQueueInstance.enqueue(x);
	waves.update();

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
		//waves.update();
		break;
	}
}
