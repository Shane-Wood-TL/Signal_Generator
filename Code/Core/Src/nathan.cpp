/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2, int8_t AmpKnobInc1, int8_t FreqKnobInc1, int8_t AmpKnobInc2, int8_t FreqKnobInc2, int8_t DelayKnobInc2, int8_t AmpKnobDec1, int8_t FreqKnobDec1, int8_t AmpKnobDec2, int8_t FreqKnobDec2, int8_t DelayKnobDec2){

	gpio_name_1 = GpioName1;
	pin_number_1 = PinNumber1;
	gpio_name_2 = GpioName2;
	pin_number_2 = PinNumber2;

	amp_knob_inc1 = AmpKnobInc1;
	freq_knob_inc1 = FreqKnobInc1;

	amp_knob_inc2 = AmpKnobInc2;
	freq_knob_inc2 = FreqKnobInc2;
	delay_knob_inc2 = DelayKnobInc2;

	amp_knob_dec1 = AmpKnobDec1;
	freq_knob_dec1 = FreqKnobDec1;

	amp_knob_dec2 = AmpKnobDec2;
	freq_knob_dec2 = FreqKnobDec2;
	delay_knob_dec2 = DelayKnobDec2;
}

void KnobDriver::UpdateKnob(struct inputValues *queue_data){

	static bool PreviousStatePin1 = false;
	static bool PreviousStatePin2 = false;
	bool KnobCurrentStatePin1;
	bool KnobCurrentStatePin2;

	if ((gpio_name_1 -> IDR & (1<<pin_number_1)) == 0) KnobCurrentStatePin1 = true;
	else KnobCurrentStatePin1 = false;
	if ((gpio_name_2 -> IDR & (1<<pin_number_2)) == 0) KnobCurrentStatePin2 = true;
	else KnobCurrentStatePin2 = false;

	if ((KnobCurrentStatePin1 == true) && (PreviousStatePin1 == false) && (KnobCurrentStatePin2 == false)){
		queue_data -> AmpKnob1 = amp_knob_inc1;
		queue_data -> FreqKnob1 = freq_knob_inc1;
		queue_data -> AmpKnob2 = amp_knob_inc2;
		queue_data -> FreqKnob2 = freq_knob_inc2;
		queue_data -> DelayKnob2 = delay_knob_inc2;
	}
	else if ((KnobCurrentStatePin2 == true) && (PreviousStatePin2 == false) && (KnobCurrentStatePin1 == false)){
		queue_data -> AmpKnob1 = amp_knob_dec1;
		queue_data -> FreqKnob1 = freq_knob_dec1;
		queue_data -> AmpKnob2 = amp_knob_dec2;
		queue_data -> FreqKnob2 = freq_knob_dec2;
		queue_data -> DelayKnob2 = delay_knob_dec2;
	}
	else{
		queue_data -> AmpKnob1 = 0;
		queue_data -> FreqKnob1 = 0;
		queue_data -> AmpKnob2 = 0;
		queue_data -> FreqKnob2 = 0;
		queue_data -> DelayKnob2 = 0;
	}

	PreviousStatePin1 = KnobCurrentStatePin1;
	PreviousStatePin2 = KnobCurrentStatePin2;

	return;
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

	AmpKnob -> UpdateKnob(&queue_data);
    FreqKnob -> UpdateKnob(&queue_data);
    ShiftKnob -> UpdateKnob(&queue_data);
	channelSwitcher->UpdateSwitch(&queue_data);
	modeSwitcher -> UpdateButton(&queue_data);

	inputQueueInstance -> enqueue(queue_data);


	return;
}

