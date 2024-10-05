/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2){

}

void KnobDriver::KnobStateMachine(bool* KnobChange, bool ActivatedPin1, bool ActivatedPin2){

	static bool PreviousStatePin1 = false;
	static bool PreviousStatePin2 = false;
	bool CurrentStatePin1 = false;
	bool CurrentStatePin2 = false;

	if ((gpio_name_1 -> IDR & (1<<pin_number_1)) == 1) CurrentStatePin1 = true;
	else CurrentStatePin1 = false;
	if ((gpio_name_2 -> IDR & (1<<pin_number_2)) == 1) CurrentStatePin2 = true;
	else CurrentStatePin2 = false;

	if ((CurrentStatePin1 == true) && (PreviousStatePin1 == false)) ActivatedPin1 = true;
	else ActivatedPin1 = false;
	if ((CurrentStatePin2 == true) && (PreviousStatePin2 == false)) ActivatedPin2 = true;
	else ActivatedPin2 = false;

	if (ActivatedPin1 != ActivatedPin2) *KnobChange = true;
	else *KnobChange = false;

	return;
}
uint8_t KnobDriver::getCurrentOutput(){
	return 0;
}

void KnobDriver::checkForInput(){
	return;
}






ButtonDriver::ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI){

}

void ButtonDriver::ButtonStateMachine(bool* ButtonChange, bool CurrentState){

	static bool ButtonPreviousState = false;

	if ((gpio_name -> IDR & (1<<pin_number)) == 0) CurrentState = true;
	else CurrentState = false;

	if ((CurrentState == true) && (ButtonPreviousState == false)){
		*ButtonChange = true;
		ButtonPreviousState = CurrentState;
	}
	else *ButtonChange = false;

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

void SwitchDriver::SwitchStateMachine(bool* SwitchChange, bool CurrentState){

	static bool SwitchPreviousState = false;

	if ((gpio_name -> IDR & (1<<pin_number)) == 1) CurrentState = true;
	else CurrentState = false;

	if (CurrentState != SwitchPreviousState){
		*SwitchChange = true;
		SwitchPreviousState = CurrentState;
	}
	else *SwitchChange = false;

	return;
}







InputDriver::InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI,ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI, Semaphore *KnobSemaphoreI){

}

void InputDriver::checkForUpdates(){
	return;
}

