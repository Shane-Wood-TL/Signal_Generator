/*
 * @file pinout.h
 * @brief This file contains the port and number for all pins used and other IOC setup information
 *
 *  Created on: Oct 29, 2024
 *      Author: Shane Wood
 */

#ifndef INC_SHANE_PINOUT_H_
#define INC_SHANE_PINOUT_H_
/*
 * FCLK is set to 72Mhz
 * FCLK also needs to be updated in allIncludes.h
 *
 * Dac setup
 * CH1 -> triggered on timer 2
 * CH2 -> triggered on timer 6
 * PA_4 and PA_5 need to be set up under the dac's GPIO settings in analog mode
 *
 * DMA setup
 * DMA, enabled
 * Memory to peripheral
 * size of word, circular
 * both channels enabled (3 and 4)
 * DAC global interrupts for ch3 and ch4
 *
 * Timers
 * 4 timers (2,6,7,16 are currently used)
 * global interrupts for 7,16 (semaphores)
 *
 * timer 2, 6's ARR is set in the code
 * timerPSC needs to be set for what matches timer 2 and 6 (this is only in allIncludes.h)
 * more pre-scaling might be needed if the frequency needs to go lower or the clk speed has changed
 * due to some timers only being 16 bits(notable tim6) a pre-scaling of 4 was needed to prevent overflow
 *
 *
 * the values for timers are set in the ioc file
 * timer 7 needs a period of 2ms adjusted in the ioc file (pre-scaling + arr can be used,
 * will vary based on clock speed)
 * At 72Mhz Arr = 5000, pre-scaling = 28
 * timer 16 needs a period of 1s adjusted in the ioc file (same as timer 7)
 * At 72Mhz Arr = 61000, pre-scaling = 1200
 *
 *
 * SPI Setup
 * 36Mbit/s (other speed work as well, although this is built for 36Mbit/s)
 * 8 bits, Motorola format
 * Mode: transmit only master (display provides no feedback)
 * no interrupts or DMA used for SPI
 *
 *
 * Pin Setups
 * Output
 * dc (B7), rst(B6)
 *
 * set pins as spi3 mosi
 * mosi (B5)
 *
 * set pins as spi3 sclk
 * sclk (B3)
 *
 * PA_4 needs to be set for DAC_OUT1 output
 * PA_5 needs to be set for DAC_OUT2 output
 *
 * B4 can also be set as an output pin if the TOGGLE /WRITEON / WRITEOFF macros are being used
 *
 * Other pinouts + settings below #define for the
 * display
*/

//Display
#define dcPort GPIOB
#define dcPin 7

#define rstPort GPIOB
#define rstPin 6

#define sclkPort GPIOB
#define sclkPin LL_GPIO_PIN_3

#define mosiPort GPIOB
#define mosiPin LL_GPIO_PIN_5

/*
Inputs
All set with internal pull-ups
*/

//Switch
#define channelSwitchPort GPIOA
#define channelSwitchPin 7

//Button
#define modeButtonPort GPIOB
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

/*Pins named on board
 * The pins used do not match the names on the board
 * so those are as follows:
 *
 * dc = D4
 * rst = D5
 * mosi = D11
 * sclk = D13
 *
 * channelSwitch = A6
 * modeButton = D3
 * freqKnobA = D2
 * freqKnobB = D10
 * ampKnobA = D1
 * ampKnobB = D0
 * shiftKnobA = D9
 * shiftKnobB = D6
 *
 * Dac channel 1 output = A3
 * Dac channel 2 output = A4
 *
 * Debug pin = D12
 */
#endif /* INC_SHANE_PINOUT_H_ */
