/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2){

	//Assigns pin A (=1) and pin B (=2) on the knob to a GPIO pin on the board
	gpio_name_1 = GpioName1;
	pin_number_1 = PinNumber1;
	gpio_name_2 = GpioName2;
	pin_number_2 = PinNumber2;

	//Part of the knob state machine in UpdateKnob
	previousStatePin1 = false;
	previousStatePin2 = false;

	//Sanity check
	assert(gpio_name_1 != nullptr);
	assert(gpio_name_2 != nullptr);
}

int8_t KnobDriver::UpdateKnob(){

	//Variable for increase (1), decrease (-1), or no change (0). Value will be inserted into an inputValue struct
	int8_t knobUpdateValue = 0;

	//Begin knob state machine
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
	//End knob state machine

	//Assign value based off of state machine results that will be inserted into an inputValue struct
	if ((knobCurrentStatePin1 == true) && (previousStatePin1 == false) && (knobCurrentStatePin2 == false) && (previousStatePin2 == false)){
		knobUpdateValue = 1;
	}
	else if ((knobCurrentStatePin2 == true) && (previousStatePin2 == false) && (knobCurrentStatePin1 == false) && (previousStatePin1 == false)){
		knobUpdateValue = -1;
	}

	//Prepare state machine for next run
	previousStatePin1 = knobCurrentStatePin1;
	previousStatePin2 = knobCurrentStatePin2;

	//Sanity check
	assert((knobUpdateValue == 1) or (knobUpdateValue == -1) or (knobUpdateValue == 0));

	return knobUpdateValue;
}

ButtonDriver::ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI){

	//Assigns the semaphore that triggers a run of the state machine
	ButtonSemaphoreInstance = ButtonSemaphoreI;

	//Assigns a GPIO pin to for use by the button
	gpio_name = GpioName;
	pin_number = PinNumber;

	//Sanity check
	assert(gpio_name != nullptr);
	assert(ButtonSemaphoreInstance != nullptr);
}

void ButtonDriver::UpdateButton(struct inputValues *queue_data){

	//Both variables are true if the semaphore declares it is time for the button to check for an input
	bool semaContents;
	bool semaStatus = ButtonSemaphoreInstance -> dequeue(&semaContents);

	if ((semaStatus == true) && (semaContents == true)){

		//Begin button state machine
		static bool ButtonPreviousState = false;
		bool ButtonCurrentState;

		if ((gpio_name -> IDR & (1<<pin_number)) == 0){
			ButtonCurrentState = true;
		}
		else{
			ButtonCurrentState = false;
		}

		//Sanity check
		assert((ButtonCurrentState == true) or (ButtonCurrentState == false));

		if ((ButtonCurrentState == true) && (ButtonPreviousState == false)){
			queue_data -> isButtonPressed = true;
		}
		else{
			queue_data -> isButtonPressed = false;
		}

		ButtonPreviousState = ButtonCurrentState;
		//End button state machine
	}
	else{
		//Insert a "no change" value into the inputValue struct if the semaphore doesn't allow the button to check for an input
		queue_data -> isButtonPressed = false;
	}

	return;
}

SwitchDriver::SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI){

	//Assigns the semaphore that triggers a run of the state machine
	SwitchSemaphoreInstance = SwitchSemaphoreI;

	//Assigns a GPIO pin to for use by the switch
	gpio_name = GpioName;
	pin_number = PinNumber;

	//Sanity check
	assert(gpio_name != nullptr);
	assert(SwitchSemaphoreInstance != nullptr);
}

int8_t SwitchDriver::UpdateSwitch(struct inputValues *queue_data){

	//Both variables are true if the semaphore declares it is time for the switch to check for an input
	bool semaContents;
	bool semaStatus = SwitchSemaphoreInstance -> dequeue(&semaContents);

	static int8_t previousSwitchState = 0;

	if ((semaStatus == true) && (semaContents == true)){

		//Read current switch logic level
		bool SwitchCurrentState;

		if ((gpio_name -> IDR & (1<<pin_number)) == 0){
			SwitchCurrentState = true;
		}
		else{
			SwitchCurrentState = false;
		}

		//Sanity check
		assert((SwitchCurrentState == true) or (SwitchCurrentState == false));

		//Insert current logic level into inputValues struct and assign previousSwitchState to the current logic level
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
		//Insert a "no change" value into the inputValue struct if the semaphore doesn't allow the switch to check for an input
		queue_data -> Switch = previousSwitchState;
	}

	return previousSwitchState;
}

InputDriver::InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI, ButtonDriver *modeSwitcherI, inputQueue *inputQueueInstanceI, Semaphore *KnobSemaphoreI){

	//pointers to 3 knobs, 1 button, 1 switch drivers
	AmpKnob = AmpKnobI;
	FreqKnob = FreqKnobI;
	ShiftKnob = ShiftKnobI;
	channelSwitcher = channelSwitcherI;
	modeSwitcher = modeSwitcherI;

	//Pointer to a input queue instance, where the input data will go
	inputQueueInstance = inputQueueInstanceI;

	//input to the knob semaphore instance, what will communicate that it is time for the knob drivers to run
	KnobSemaphoreInstance = KnobSemaphoreI;

	//Sanity check
	assert(AmpKnob != nullptr);
	assert(FreqKnob != nullptr);
	assert(ShiftKnob != nullptr);
	assert(channelSwitcher != nullptr);
	assert(modeSwitcher != nullptr);
	assert(inputQueueInstance != nullptr);
	assert(KnobSemaphoreInstance != nullptr);
}

void InputDriver::checkForUpdates(){

	//initialize struct to 0
    inputValues queue_data = {0};

    //Variables needed to determine if there is change in logic levels of the switch, a basic state machine
    static int8_t switchPastState = 0;
    int8_t switchPresentState = 0;

    //Both variables are true if the semaphore declares it is time for the knobs to check for an input
	bool knobSemaContents;
	bool knobSemaStatus = KnobSemaphoreInstance -> dequeue(&knobSemaContents);

	if ((knobSemaStatus == true) && (knobSemaContents == true)){

		//Update all knob instances
		queue_data.FreqKnob = FreqKnob -> UpdateKnob();
		queue_data.AmpKnob = AmpKnob -> UpdateKnob();
		queue_data.DelayKnob = ShiftKnob -> UpdateKnob();
	}
	else{

		//Insert a "no change" value into the inputValue struct if the semaphore doesn't allow the knobs to check for an input
		queue_data.FreqKnob = 0;
		queue_data.AmpKnob = 0;
		queue_data.DelayKnob = 0;
	}

	//Update Button and Switch instances
	modeSwitcher -> UpdateButton(&queue_data);
	switchPresentState = channelSwitcher -> UpdateSwitch(&queue_data);

	//Sanity check
	assert((switchPresentState == 1) or (switchPresentState == 0));

	//Check all values of the inputValues struct. The instant a change value is found, enqueue the inputValues struct. Otherwise, skip the enqueueing step
	if (queue_data.FreqKnob != 0){
		inputQueueInstance -> enqueue(queue_data);
	}
	else if (queue_data.AmpKnob != 0){
		inputQueueInstance -> enqueue(queue_data);
	}
	else if (queue_data.DelayKnob != 0){
		inputQueueInstance -> enqueue(queue_data);
	}
	else if (queue_data.isButtonPressed != false){
		inputQueueInstance -> enqueue(queue_data);
	}
	else if (switchPastState != switchPresentState){
		inputQueueInstance -> enqueue(queue_data);
	}

	switchPastState = switchPresentState;

	return;
}

