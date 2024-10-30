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
}





void cpp_main(void){
	htim7.Instance->CR1 |= TIM_CR1_CEN;
	//set up the queues
	inputQueue inputQueueInstance;
	signalQueue channel1;
	signalQueue channel2;
	Semaphore button;
	Waves waves(&inputQueueInstance, &channel1, &channel2);
	/*Semaphore switchs;
	Semaphore knobs;*/
	//button.enqueue(1);



	displayQueue displayQueueInstance;

	//applicationLayer mainHandler(&inputQueueInstance, &channel1, &channel2);

	dacDriver DriverCh1(&hdac1,DAC_CHANNEL_1,&htim2,&channel1);
	dacDriver DriverCh2(&hdac1,DAC_CHANNEL_2,&htim6,&channel2);
	outputDriver outputDriverI(&DriverCh1, &DriverCh2, &displayQueueInstance);//

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
	memoryChecker mainMemoryChecker(memoryBarrier);




	//start spi + setup display
	display mainDisplay(&hspi3, &displayQueueInstance);//
	//draw freq + amp to the display
	mainDisplay.getNewValues();//

	uint8_t wasteofTime = 0;
	while(1){
		struct inputValues test = {1,true,0,0,0,0,0};
		wasteofTime = 0;
		inputQueueInstance.enqueue(test);
		//mainHandler.update();
		//outputDriverI.update();
		//mainDisplay.getNewValues();
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

