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
	void KnobStateMachine(uint32_t* KnobValue);
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
	void ButtonStateMachine(uint8_t* ButtonValue);
public:
	ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber);
	bool getCurrentOutput();
	void checkForInput();
};

class SwitchDriver
{
private:
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;
	uint8_t CurrentOutput;
	void SwitchStateMachine(bool* SwitchState);
public:
	SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber);
	void checkForInput();
	uint8_t getCurrentOutput();
};

class InputDriver
{
	KnobDriver *AmpKnob;
	KnobDriver *FreqKnob;
	KnobDriver *ShiftKnob;
	SwitchDriver *channelSwitcher;
	ButtonDriver *modeSwitcher;
	inputQueue *inputQueueInstance;
public:
	InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI,ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI);
	void checkForUpdates();
};







#endif /* INC_NATHAN_H_ */
