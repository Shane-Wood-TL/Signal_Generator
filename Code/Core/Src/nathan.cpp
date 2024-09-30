/*
 * nathan.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"
class InputDriver
{
public:
	struct
	{
		bool ChannelSel;
		uint8_t ModeSel;
		uint32_t AmpValue1;
		uint32_t FreqValue1;
		uint32_t DelayValue1;
		uint32_t AmpValue2;
		uint32_t FreqValue2;
		uint32_t DelayValue2;
	};

	class KnobDriver
	{
	private:
		GPIO_TypeDef* gpio_name_1;
		uint8_t pin_number_1;
		GPIO_TypeDef* gpio_name_2;
		uint8_t pin_number_2;

	public:
		void KnobStateMachine(uint32_t* KnobValue);

		KnobDriver(GPIO_TypeDef* GpioName1, uint8_t PinNumber1, GPIO_TypeDef* GpioName2, uint8_t PinNumber2);
	};

	class ButtonDriver
	{
	private:
		GPIO_TypeDef* gpio_name;
		uint8_t pin_number;

	public:
		void ButtonStateMachine(uint8_t* ButtonValue);

		ButtonDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber);
	};

	class SwitchDriver
	{
	private:
		GPIO_TypeDef* gpio_name;
		uint8_t pin_number;

	public:
		void SwitchStateMachine(bool* SwitchState);

		SwitchDriver(GPIO_TypeDef* GpioName, uint8_t PinNumber);
	};
};
