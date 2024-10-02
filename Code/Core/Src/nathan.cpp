/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2){}
void KnobDriver::KnobStateMachine(uint32_t* KnobValue){
	return;
}
uint8_t KnobDriver::getCurrentOutput(){
	return 0;
}

void KnobDriver::checkForInput(){
	return;
}






ButtonDriver::ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI){}
void ButtonDriver::ButtonStateMachine(uint8_t* ButtonValue){
	return;
}

bool ButtonDriver::getCurrentOutput(){
	return true;
}

void ButtonDriver::checkForInput(){
	return;
}






SwitchDriver::SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI){

}

void SwitchDriver::SwitchStateMachine(bool* SwitchState){
	return;
}

uint8_t SwitchDriver::getCurrentOutput(){
	return 0;
}



void SwitchDriver::checkForInput(){
	return;
}







InputDriver::InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI,ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI, Semaphore *KnobSemaphoreI){

}

void InputDriver::checkForUpdates(){
	return;
}

