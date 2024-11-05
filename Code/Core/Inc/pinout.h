/*
 * @file pinout.h
 * @brief This file contains the port and number for all pins used
 *
 *  Created on: Oct 29, 2024
 *      Author: Shane Wood
 */

#ifndef INC_SHANE_PINOUT_H_
#define INC_SHANE_PINOUT_H_

//Other needs
//DMA, enabled, Memory to peripheral, size of word, circular, both channels enabled
//DAC global interrupts for ch3 and ch4
//4 timers (2,6,7,16 are currently used)
//global interrupts for 7,16
//SPI, 36Mbit/s
//FCLK also needs to be updated in allIncludes.h

//timer 2, 6 are set in the code
//timer 7 needs a period of 2ms adjusted in the ioc file
//timer 16 needs a period of 1s adjusted in the ioc file
//timerPSC needs to be set for what matches timer 2 and 6
//the inital values for timers are set in the ioc file
//more prescaling might be needed if the frequency needs to go lower or the clk speed has changed
//due to some timers only being 16 bits a prescaling of 4 was needed to prevent overflow

//set pins as outputs
//dc (B7), rst(B6)

//set pins as spi3 mosi
//mosi (B5)

//set pins as spi3 sclk
//sclk (B3)

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

//Inputs, all set with internal pullups
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
