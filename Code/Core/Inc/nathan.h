/*
 * nathan.h
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#ifndef INC_NATHAN_H_
#define INC_NATHAN_H_

#include "allIncludes.h"

///KnobDriver class determines if there is an input on any knobs present in the system (This system uses three knobs).
/**
 * A single knob needs two input GPIO pins with pull-up resistors, designate these with the constructor.
 * A GPIO name (ex: A, B, H,...), and the pin's number (11, 1, 5,...).
 * Two private member variables for each GPIO pin's previous state (1 or 0) are required to run a state machine for multiple knobs simultaneously.
 * Member function "UpdateKnob" reads the knob's pins for input with a simple state machine and then returns the output (1 for increase, -1 for decrease, 0 for no activity).
 */
class KnobDriver
{
private:
	GPIO_TypeDef* gpio_name_1;
	uint8_t pin_number_1;
	GPIO_TypeDef* gpio_name_2;
	uint8_t pin_number_2;
	bool previousStatePin1;
	bool previousStatePin2;
public:
	KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2);
	int8_t UpdateKnob();
};

///ButtonDriver class determines if there is an input on the button present in the system (This system uses one button).
/**
 * Each button uses one GPIO input pin with a pull-up resistor which is designated by the constructor, a GPIO name (A, H, G,...) and a pin number (1, 3, 12,...).
 * Also requires a pointer to a semaphore (created by another class). These are all assigned in the constructor.
 * The "UpdateButton" member function reads the designated pin for input and with a simple state machine it checks for a falling edge.
 * If it recognizes a falling edge it will change a the "isButtonPressed" value to 1 in an inputValues struct.
 * The UpdateButton function will only run when the semaphore value is "true".
 * This function returns void.
 */
class ButtonDriver
{
private:
	Semaphore *ButtonSemaphoreInstance;
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;
public:
	ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *ButtonSemaphoreI);
	void UpdateButton(struct inputValues *queue_data);
};

///SwitchDriver class determines if there is an input on the switch present in the system (This system uses one switch).
/**
 * Each switch uses one GPIO input pin with a pull-up resistor which is designated by the constructor, a GPIO name (A, H, G,...) and a pin number (1, 3, 12,...).
 * Also requires a pointer to a semaphore (created by another class). These are all assigned in the constructor.
 * The "UpdateSwitch" member function reads the designated pin for input.
 * It passes the switch logic level to the "Switch" location in an inputValues struct.
 * The UpdateSwitch function will only run when the semaphore value is "true".
 * This function returns the previous state value that is used in the InputDriver class to check for change.
 */
class SwitchDriver
{
private:
	Semaphore *SwitchSemaphoreInstance;
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;
public:
	SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI);
	int8_t UpdateSwitch(struct inputValues *queue_data);
};

///InputDriver class holds pointers to all the other classes and uses them in an update function.
/**
 * The constructor for this class hold a pointer to three KnobDriver classes, one SwitchDriver class, and one ButtonDriver class.
 * It also holds a pointer to an inputQueue instance, which is the location that all the inputs will be enqueued to,
 * as well as a semaphore instance for the Knobs which will run all three knobs at the same time.
 * The InputDriver class also initializes an inputValues struct which is where all the data from the inputs will be placed to be enqueued.
 * The "checkForUpdates" member function does three things.
 * Firstly, it fills the inputValue struct with values of 0 and then calls all the update functions from each instantiated input.
 * The in this function the knob input driver update functions are only called when the semaphore reads true,
 * this is done with two variables, knobSemaContents and knobSemaStatus, and an if statement.
 * In each call of checkForUpdates, the struct will be filled with the proper inputs from the knob, button, and switch drivers.
 * Secondly, after the inputValues struct has been filled with the inputs from the latest call of the checkForUpdates function,
 * each portion of the struct will be compared with a "no change" value,
 * if there has been any change the inputValues struct is immediately enqueued into the inputQueue.
 * Thirdly, in order for there to be a "no change" value for the switch, which only relays its current logic level,
 * checkForUpdates runs a very basic state machine for the past and present values of the switch to detect if there has been any change.
 * This uses two variables, switchPastState and switchPreviousState.
 */
class InputDriver
{
	KnobDriver *AmpKnob;
	KnobDriver *FreqKnob;
	KnobDriver *ShiftKnob;
	SwitchDriver *channelSwitcher;
	ButtonDriver *modeSwitcher;
	inputQueue *inputQueueInstance;
	Semaphore *KnobSemaphoreInstance;
public:
	InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI, ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI,Semaphore *KnobSemaphoreI);
	void checkForUpdates();
	inputValues queue_data{}; //struct of all update data that gets enqueued into inputQueue
};







#endif /* INC_NATHAN_H_ */
