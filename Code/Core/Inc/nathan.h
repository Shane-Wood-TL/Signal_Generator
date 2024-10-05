/*
 * nathan.h
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#ifndef INC_NATHAN_H_
#define INC_NATHAN_H_

#include "allIncludes.h"

class KnobDriver
{
private:
	GPIO_TypeDef* gpio_name_1;
	uint8_t pin_number_1;
	GPIO_TypeDef* gpio_name_2;
	uint8_t pin_number_2;
	inputValues currentInput;
	uint8_t CurrentOutput;
	bool ActivatedPin1 = false;
	bool ActivatedPin2 = false;
	void KnobStateMachine(bool* KnobChange, bool ActivatedPin1, bool ActivatedPin2);
public:
	KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2);
	uint8_t getCurrentOutput();
	void checkForInput();
};

class ButtonDriver
{
private:
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;
	bool currentOutput;
	Semaphore *ButtonSemaphoreInstance;
	bool ButtonCurrentState = false;
	void ButtonStateMachine(bool* ButtonChange, bool CurrentState);
public:
	ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber,Semaphore *ButtonSemaphoreI);
	bool getCurrentOutput();
	void checkForInput();
};

class SwitchDriver
{
private:
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;
	uint8_t CurrentOutput;
	Semaphore *SwitchSemaphoreInstance;
	bool SwitchCurrentState = false;
	void SwitchStateMachine(bool* SwitchChange, bool CurrentState);
public:
	SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber,Semaphore *SwitchSemaphoreI);
};

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
	InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI,ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI,Semaphore *KnobSemaphoreI);
	void checkForUpdates();
};







#endif /* INC_NATHAN_H_ */
