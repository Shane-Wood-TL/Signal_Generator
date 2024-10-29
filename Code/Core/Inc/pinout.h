/*
 * pinout.h
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#ifndef INC_SHANE_PINOUT_H_
#define INC_SHANE_PINOUT_H_


//Pinout
//Display
#define dcPort GPIOB
#define dcPin LL_GPIO_PIN_7

#define rstPort GPIOB
#define rstPin LL_GPIO_PIN_6

#define sclkPort GPIOB
#define sclkPin LL_GPIO_PIN_3

#define mosiPort GPIOB
#define mosiPin LL_GPIO_PIN_5

//PA12 FreqKnob1
//PA11 FreqKnob2

//PA10 AmpKnob1
//PA9 AmpKnob2

//PA8 ShiftKnob1
//PB1 ShiftKnob2

//PB0 ModeBtn
//PA7 Switch

//Inputs
//Switch
#define channelSwitchPort GPIOA //A6
#define channelSwitchPin 7

//Button
#define modeButtonPort GPIOB //D3
#define modeButtonPin  LL_GPIO_PIN_0

//Knobs
//Frequency Knob
#define freqKnobAPort GPIOB //D6
#define freqKnobAPin LL_GPIO_PIN_1 //D6

#define freqKnobBPort GPIOA //D9
#define freqKnobBPin LL_GPIO_PIN_8 //D9

//Amplitude Knob
#define ampKnobAPort GPIOA //D10
#define ampKnobAPin LL_GPIO_PIN_11 //D10

#define ampKnobBPort GPIOB //D11
#define ampKnobBPin LL_GPIO_PIN_5 //D11

//Shift Knob
#define shiftKnobAPort GPIOA //A6
#define shiftKnobAPin LL_GPIO_PIN_7 //A6

#define shiftKnobBPort GPIOA //A5
#define shiftKnobBPin LL_GPIO_PIN_6 //A5


#endif /* INC_SHANE_PINOUT_H_ */
