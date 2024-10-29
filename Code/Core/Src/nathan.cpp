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

	assert(gpio_name_1 != nullptr);
	assert(gpio_name_2 != nullptr);
}

int8_t KnobDriver::UpdateKnob(){

	int8_t KnobUpdateValue = 0;

	static bool PreviousStatePin1 = false;
	static bool PreviousStatePin2 = false;
	bool KnobCurrentStatePin1;
	bool KnobCurrentStatePin2;

	if ((gpio_name_1 -> IDR & (1<<pin_number_1)) == 0) KnobCurrentStatePin1 = true;
	else KnobCurrentStatePin1 = false;
	if ((gpio_name_2 -> IDR & (1<<pin_number_2)) == 0) KnobCurrentStatePin2 = true;
	else KnobCurrentStatePin2 = false;

	if ((KnobCurrentStatePin1 == true) && (PreviousStatePin1 == false) && (KnobCurrentStatePin2 == false)){
		KnobUpdateValue = 1;
	}
	else if ((KnobCurrentStatePin2 == true) && (PreviousStatePin2 == false) && (KnobCurrentStatePin1 == false)){
		KnobUpdateValue = -1;
	}

	PreviousStatePin1 = KnobCurrentStatePin1;
	PreviousStatePin2 = KnobCurrentStatePin2;

	return KnobUpdateValue;
}

ButtonDriver::ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI){
	ButtonSemaphoreInstance = ButtonSemaphoreI;
	gpio_name = GpioName;
	pin_number = PinNumber;
}

void ButtonDriver::UpdateButton(struct inputValues *queue_data){

	static bool ButtonPreviousState = false;
	bool ButtonCurrentState;

	if ((gpio_name -> IDR & (1<<pin_number)) == 0) ButtonCurrentState = true;
	else ButtonCurrentState = false;

	if ((ButtonCurrentState == true) && (ButtonPreviousState == false)){
		queue_data -> isButtonPressed = true;
	}
	else{
		queue_data -> isButtonPressed = false;
	}

	ButtonPreviousState = ButtonCurrentState;

	return;
}

SwitchDriver::SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI){
	SwitchSemaphoreInstance = SwitchSemaphoreI;
	gpio_name = GpioName;
	pin_number = PinNumber;
}

void SwitchDriver::UpdateSwitch(struct inputValues *queue_data){

	bool SwitchCurrentState;

	if ((gpio_name -> IDR & (1<<pin_number)) == 0) SwitchCurrentState = true;
	else SwitchCurrentState = false;

	if (SwitchCurrentState == true){
		queue_data -> Switch = 1;
	}
	else{
		queue_data -> Switch = 0;
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

    int8_t freq_value = FreqKnob -> UpdateKnob();
    queue_data.FreqKnob1 = freq_value;
    queue_data.FreqKnob2 = freq_value;

    int8_t amp_value = AmpKnob -> UpdateKnob();
    queue_data.AmpKnob1 = amp_value;
    queue_data.AmpKnob2 = amp_value;

    queue_data.DelayKnob2 = ShiftKnob -> UpdateKnob();

	modeSwitcher -> UpdateButton(&queue_data);
	channelSwitcher->UpdateSwitch(&queue_data);

	inputQueueInstance -> enqueue(queue_data);


	return;
}

