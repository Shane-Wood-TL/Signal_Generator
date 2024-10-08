/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2){

}

void KnobDriver::KnobStateMachine(){

	static bool PreviousStatePin1 = false;
	static bool PreviousStatePin2 = false;
	bool KnobChangeA = false;
	bool KnobChangeB = false;

	if ((gpio_name_1 -> IDR & (1<<pin_number_1)) == 0) KnobCurrentStatePin1 = true;
	else KnobCurrentStatePin1 = false;
	if ((gpio_name_2 -> IDR & (1<<pin_number_2)) == 0) KnobCurrentStatePin2 = true;
	else KnobCurrentStatePin2 = false;

	if ((KnobCurrentStatePin1 == true) && (PreviousStatePin1 == false) && (KnobCurrentStatePin2 == false)) KnobChangeA = true;
	else KnobChangeA = false;
	if ((KnobCurrentStatePin2 == true) && (PreviousStatePin2 == false) && (KnobCurrentStatePin1 == false)) KnobChangeB = true;
	else KnobChangeB = false;

	PreviousStatePin1 = KnobCurrentStatePin1;
	PreviousStatePin2 = KnobCurrentStatePin2;

	if (KnobChangeA == true); //enqueue true
	if (KnobChangeB == true); //enqueue false

	return;
}






ButtonDriver::ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI){

}

void ButtonDriver::ButtonStateMachine(){

	static bool ButtonPreviousState = false;
	bool ButtonChange = false;

	if ((gpio_name -> IDR & (1<<pin_number)) == 0) ButtonCurrentState = true;
	else ButtonCurrentState = false;

	if ((ButtonCurrentState == true) && (ButtonPreviousState == false)) ButtonChange = true;
	else ButtonChange = false;

	ButtonPreviousState = ButtonCurrentState;

	if (ButtonChange == true); //enqueue true

	return;
}






SwitchDriver::SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI){

}

void SwitchDriver::SwitchStateMachine(){

	static bool SwitchPreviousState = false;
	bool SwitchChange = false;

	if ((gpio_name -> IDR & (1<<pin_number)) == 1) SwitchCurrentState = true;
	else SwitchCurrentState = false;

	if (SwitchCurrentState != SwitchPreviousState) SwitchChange = true;
	else SwitchChange = false;

	SwitchPreviousState = SwitchCurrentState;

	if (SwitchChange == true); //enqueue SwitchCurrentState

	return;
}





InputDriver::InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI,ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI, Semaphore *KnobSemaphoreI){

}

void InputDriver::checkForUpdates(){
	return;
}

