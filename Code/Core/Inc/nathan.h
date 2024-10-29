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
public:
	KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2);
	int8_t UpdateKnob();
};

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

class SwitchDriver
{
private:
	Semaphore *SwitchSemaphoreInstance;
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;
public:
	SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber, Semaphore *SwitchSemaphoreI);
	void UpdateSwitch(struct inputValues *queue_data);
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
	InputDriver(KnobDriver *AmpKnobI, KnobDriver *FreqKnobI, KnobDriver *ShiftKnobI, SwitchDriver *channelSwitcherI, ButtonDriver *modeSwitcherI,inputQueue *inputQueueInstanceI,Semaphore *KnobSemaphoreI);
	void checkForUpdates();
	inputValues queue_data{};
};







#endif /* INC_NATHAN_H_ */
