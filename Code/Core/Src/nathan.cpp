/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"

class ButtonSwitchQueue
{
public:
	void enqueue(uint8_t in_dat);

	void dequeue(uint8_t out_dat);

	ButtonSwitchQueue();

	uint32_t buffer[4] = {0};

private:
	uint8_t tail = 0;
	uint8_t head = 0;
};

class KnobQueue
{
public:
	void enqueue(uint32_t in_dat);

	void dequeue(uint32_t out_dat);

	KnobQueue();

	uint32_t buffer[4] = {0};

private:
	uint8_t tail = 0;
	uint8_t head = 0;
};

class KnobDriver
{
private:
	GPIO_TypeDef* gpio_name_1;
	uint8_t pin_number_1;
	GPIO_TypeDef* gpio_name_2;
	uint8_t pin_number_2;

public:
	void KnobStateMachine(KnobQueue* input_queue);

	KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2);
};

class ButtonSwitchDriver
{
private:
	GPIO_TypeDef* gpio_name;
	uint8_t pin_number;

public:
	void KnobStateMachine(ButtonSwitchQueue* input_queue);

	ButtonSwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber);
};
