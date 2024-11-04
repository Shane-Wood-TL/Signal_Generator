/*
 * @file dacDriver.h
 * @brief This file contains the definition of the dacDriver class
 *  Created on: Oct 29, 2024
 *      Author: Shane Wood
 */

#ifndef INC_SHANE_DACDRIVER_H_
#define INC_SHANE_DACDRIVER_H_

#include "allIncludes.h"
//https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Projects/NUCLEO-L432KC/Examples/DAC/DAC_SignalsGeneration/readme.txt
//https://deepbluembedded.com/stm32-dac-sine-wave-generation-stm32-dac-dma-timer-example/

/**
 * @class dacDriver
 * @brief Driver for the DAC
 *
 * @details This class takes data from a signelQueue and processes to output
 * signals from the DAC.
 */
class dacDriver{
	DAC_HandleTypeDef *hdac; ///< DAC instance
	uint32_t DacChannel; ///< DAC channel
	TIM_HandleTypeDef *timerInstance; ///< Timer Instance
	signalQueue *signalQueueInstance; ///< Signal Queue Instance
	signalInfo currentSignal; ///< Data for the current signal
	uint32_t currentReloadValue = 0; ///< Current reload value for the timer

	/**
	 * @ brief Change the reload of the timer instance
	 */
	void setReload();
	public:
		/**
		 * @brief constructs an dacDriver object.
		 * @param hdacI a DAC_HandleTypeDef, the hardware DAC's API.
		 * @param DacChannel1I a uint32_t containing the channel name.
		 * @param timer1Il a TIM_HandleTypeDef to be used with DMA for the DAC.
		 * @param channel1I a signalQueue where signal data will be aquired to drive the DAC.
		 */
		dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I, TIM_HandleTypeDef *timer1Il, signalQueue *channel1I);

		/**
		 * @brief updates the output signal if new data is available
		 */
		bool update();

		/**
		 * @brief enable the timer instance
		 */
		void enableTimer();

		/**
		 * @brief Gets the current frequency.
		 * @return A 16 bit value representing the frequency of the current signal.
		 */
		uint16_t getFreq();

		/**
		* @brief Gets the current amplitude.
		* @return A 16 bit value representing the amplitude of the current signal.
		*/
		uint16_t getAmp();

		/**
		 * @brief Gets the current phase shift
		 * @return An 8 bit value representing the phase shift of the current signal.
		 */
		uint8_t getShift();

		/**
		* @brief Gets the current wave shape
		* @return An enum of type WaveShape representing the type of wave for the current signal.
		*/
		WaveShape getWave();

		/**
		 * @brief Restarts DMA
		 */
		void restartDMA();
};


#endif /* INC_SHANE_DACDRIVER_H_ */
