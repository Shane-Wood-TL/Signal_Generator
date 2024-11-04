/*
 * @file pinout.h
 * @brief This file contains the port and number for all pins used
 *
 *  Created on: Oct 29, 2024
 *      Author: Shane Wood
 */

#ifndef INC_SHANE_PINOUT_H_
#define INC_SHANE_PINOUT_H_


//Pinout
//Display
#define dcPort GPIOB
#define dcPin 7

#define rstPort GPIOB
#define rstPin 6

#define sclkPort GPIOB
#define sclkPin LL_GPIO_PIN_3

#define mosiPort GPIOB
#define mosiPin LL_GPIO_PIN_5

//Inputs
//Switch
#define channelSwitchPort GPIOA //A6
#define channelSwitchPin 7

//Button
#define modeButtonPort GPIOB //D3
#define modeButtonPin  0

//Knobs
//Frequency Knob
#define freqKnobAPort GPIOA
#define freqKnobAPin 12

#define freqKnobBPort GPIOA
#define freqKnobBPin 11

//Amplitude Knob
#define ampKnobAPort GPIOA
#define ampKnobAPin 9

#define ampKnobBPort GPIOA
#define ampKnobBPin 10

//Shift Knob
#define shiftKnobAPort GPIOA
#define shiftKnobAPin 8

#define shiftKnobBPort GPIOB
#define shiftKnobBPin 1


#endif /* INC_SHANE_PINOUT_H_ */
