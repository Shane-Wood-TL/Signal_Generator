/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2){

	gpio_name_1 = GpioName1;
	pin_number_1 = PinNumber1;
	gpio_name_2 = GpioName2;
	pin_number_2 = PinNumber2;

	previousStatePin1 = false;
	previousStatePin2 = false;

	assert(gpio_name_1 != nullptr);
	assert(gpio_name_2 != nullptr);
}

int8_t KnobDriver::UpdateKnob(){

	int8_t knobUpdateValue = 0;

	bool knobCurrentStatePin1;
	bool knobCurrentStatePin2;

	if ((gpio_name_1 -> IDR & (1<<pin_number_1)) == 0){
		knobCurrentStatePin1 = true;
	}
	else{
		knobCurrentStatePin1 = false;
	}
	if ((gpio_name_2 -> IDR & (1<<pin_number_2)) == 0){
		knobCurrentStatePin2 = true;
	}
	else{
		knobCurrentStatePin2 = false;
	}

	if ((knobCurrentStatePin1 == true) && (previousStatePin1 == false) && (knobCurrentStatePin2 == false) && (previousStatePin2 == false)){
		knobUpdateValue = 1;
	}
	else if ((knobCurrentStatePin2 == true) && (previousStatePin2 == false) && (knobCurrentStatePin1 == false) && (previousStatePin1 == false)){
		knobUpdateValue = -1;
	}

	previousStatePin1 = knobCurrentStatePin1;
	previousStatePin2 = knobCurrentStatePin2;

	return knobUpdateValue;
}

ButtonDriver::ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI){
	ButtonSemaphoreInstance = ButtonSemaphoreI;
	gpio_name = GpioName;
	pin_number = PinNumber;
}

void ButtonDriver::UpdateButton(struct inputValues *queue_data){
	bool semaContents;
	bool semaStatus = ButtonSemaphoreInstance -> dequeue(&semaContents);

	if ((semaStatus == true) && (semaContents == true)){
		static bool ButtonPreviousState = false;
		bool ButtonCurrentState;

		if ((gpio_name -> IDR & (1<<pin_number)) == 0){
			ButtonCurrentState = true;
		}
		else{
			ButtonCurrentState = false;
		}

		if ((ButtonCurrentState == true) && (ButtonPreviousState == false)){
			queue_data -> isButtonPressed = true;
		}
		else{
			queue_data -> isButtonPressed = false;
		}

		ButtonPreviousState = ButtonCurrentState;
	}
	else{
		queue_data -> isButtonPressed = false;
	}

	return;
}

SwitchDriver::SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI){
	SwitchSemaphoreInstance = SwitchSemaphoreI;
	gpio_name = GpioName;
	pin_number = PinNumber;
}

void SwitchDriver::UpdateSwitch(struct inputValues *queue_data){
	bool semaContents;
	bool semaStatus = SwitchSemaphoreInstance -> dequeue(&semaContents);
	int8_t previousSwitchState = false;

	if ((semaStatus == true) && (semaContents == true)){
		bool SwitchCurrentState;

		if ((gpio_name -> IDR & (1<<pin_number)) == 0){
			SwitchCurrentState = true;
		}
		else{
			SwitchCurrentState = false;
		}

		if (SwitchCurrentState == true){
			queue_data -> Switch = 1;
			previousSwitchState = 1;
		}
		else{
			queue_data -> Switch = 0;
			previousSwitchState = 0;
		}
	}
	else{
		queue_data -> Switch = previousSwitchState;
	}

	return;
}

InputDriver::InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI, ButtonDriver *modeSwitcherI, inputQueue *inputQueueInstanceI, Semaphore *KnobSemaphoreI){
	AmpKnob = AmpKnobI;
	FreqKnob = FreqKnobI;
	ShiftKnob = ShiftKnobI;
	channelSwitcher = channelSwitcherI;
	modeSwitcher = modeSwitcherI;
	inputQueueInstance = inputQueueInstanceI;
	KnobSemaphoreInstance = KnobSemaphoreI;
}

void InputDriver::checkForUpdates(){
    inputValues queue_data = {0};

	bool knobSemaContents;
	bool knobSemaStatus = KnobSemaphoreInstance -> dequeue(&knobSemaContents);

	if ((knobSemaStatus == true) && (knobSemaContents == true)){
		queue_data.FreqKnob = FreqKnob -> UpdateKnob();

		queue_data.AmpKnob = AmpKnob -> UpdateKnob();

		queue_data.DelayKnob = ShiftKnob -> UpdateKnob();
	}
	else{
		queue_data.FreqKnob = 0;

		queue_data.AmpKnob = 0;

		queue_data.DelayKnob = 0;
	}

	modeSwitcher -> UpdateButton(&queue_data);
	channelSwitcher -> UpdateSwitch(&queue_data);

	inputQueueInstance -> enqueue(queue_data);


	return;
}

