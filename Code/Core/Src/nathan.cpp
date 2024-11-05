/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

KnobDriver::KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2){
	if((GpioName1 == nullptr) ||  (GpioName2 == nullptr) || (PinNumber1 > 12) || (PinNumber2 > 12)){
		NVIC_SystemReset();
	}
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
	if((GpioName == nullptr) ||  (ButtonSemaphoreI == nullptr) || (PinNumber > 12)){
			NVIC_SystemReset();
		}
	//Assigns the semaphore that triggers a run of the state machine
	assert(GpioName != nullptr);
	assert(ButtonSemaphoreI != nullptr);
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
	assert(queue_data != nullptr);
	if(queue_data == nullptr){
		return;
	}
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
	if((GpioName == nullptr)|| (PinNumber > 12) || (SwitchSemaphoreI == nullptr)){
			NVIC_SystemReset();
	}
	//Assigns the semaphore that triggers a run of the state machine
	assert(GpioName != nullptr);
	assert(SwitchSemaphoreI != nullptr);
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
	assert(queue_data != nullptr);
	if(queue_data == nullptr){
		return 0;
	}
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
	if((AmpKnobI == nullptr)|| (FreqKnobI == nullptr)|| (ShiftKnobI == nullptr)|| (channelSwitcherI == nullptr)|| (modeSwitcherI == nullptr)|| (inputQueueInstanceI == nullptr)|| (KnobSemaphoreI == nullptr)){
		NVIC_SystemReset();
	}
	//pointers to 3 knobs, 1 button, 1 switch drivers
	assert(AmpKnobI != nullptr);
	assert(FreqKnobI != nullptr);
	assert(ShiftKnobI != nullptr);
	assert(channelSwitcherI != nullptr);
	assert(modeSwitcherI != nullptr);
	assert(inputQueueInstanceI != nullptr);
	assert(KnobSemaphoreI != nullptr);
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
    inputValues queue_data1 = {0,false,0,0,0};

    //Variables needed to determine if there is change in logic levels of the switch, a basic state machine
    static int8_t switchPastState = 0;
    int8_t switchPresentState = 0;

    //Both variables are true if the semaphore declares it is time for the knobs to check for an input
	bool knobSemaContents;
	bool knobSemaStatus = KnobSemaphoreInstance -> dequeue(&knobSemaContents);

	if ((knobSemaStatus == true) && (knobSemaContents == true)){

		//Update all knob instances
		assert((knobSemaStatus == true) && (knobSemaContents == true));
		queue_data1.FreqKnob = FreqKnob -> UpdateKnob();
		queue_data1.AmpKnob = AmpKnob -> UpdateKnob();
		queue_data1.DelayKnob = ShiftKnob -> UpdateKnob();
	}
	else{

		//Insert a "no change" value into the inputValue struct if the semaphore doesn't allow the knobs to check for an input
		queue_data1.FreqKnob = 0;
		queue_data1.AmpKnob = 0;
		queue_data1.DelayKnob = 0;
	}

	//Update Button and Switch instances
	modeSwitcher -> UpdateButton(&queue_data1);
	switchPresentState = channelSwitcher -> UpdateSwitch(&queue_data1);

	//Sanity check
	assert((switchPresentState == 1) or (switchPresentState == 0));

	//Check all values of the inputValues struct. The instant a change value is found, enqueue the inputValues struct. Otherwise, skip the enqueueing step
	if (queue_data1.FreqKnob != 0){
		inputQueueInstance -> enqueue(queue_data1);
	}
	else if (queue_data1.AmpKnob != 0){
		inputQueueInstance -> enqueue(queue_data1);
	}
	else if (queue_data1.DelayKnob != 0){
		inputQueueInstance -> enqueue(queue_data1);
	}
	else if (queue_data1.isButtonPressed != false){
		inputQueueInstance -> enqueue(queue_data1);
	}
	else if (switchPastState != switchPresentState){
		inputQueueInstance -> enqueue(queue_data1);
	}

	switchPastState = switchPresentState;

	return;
}

