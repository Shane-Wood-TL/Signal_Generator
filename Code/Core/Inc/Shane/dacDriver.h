/**
 * @file dacDriver.h
 * @brief This file contains the definition of the dacDriver class
 * @author Shane Wood
 * @date Sep 15, 2024
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
	 * @brief Change the reload of the timer instance
	 * 
	 * @details Adjusts the timer based on the current freuqeueny based on the prescaling and clock speed. It
	 * Also resets the count to prevent cases where CNT is greater than ARR, leading to unexpected results
	 */
	void setReload();

	/**
	 * @brief enable the timer instance
	 */
	void enableTimer();
	public:
		/**
		 * @brief constructs an dacDriver object.
		 * @param hdacI a DAC_HandleTypeDef, the hardware DAC's API.
		 * @param DacChannel1I a uint32_t containing the channel name.
		 * @param timer1Il a TIM_HandleTypeDef to be used with DMA for the DAC.
		 * @param channel1I a signalQueue where signal data will be aquired to drive the DAC.
		 * 
		 * @details Sets up a dacDriver, starts DMA at 12bit resolution
		 */
		dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I, TIM_HandleTypeDef *timer1Il, signalQueue *channel1I);

		/**
		 * @brief updates the output signal if new data is available
		 * 
		 * @return A bool if new data was found
		 * @details Checks the signalQueueInstance, if there is data of a different frequency, set the new reload
		 */
		bool update();


		/**
		 * @brief Gets the current frequency.
		 * @param freq A uint16_t that will represent the frequency of the current signal.
		 */
		void getFreq(uint16_t *freq);

		/**
		* @brief Gets the current amplitude.
		* @param amp uint16_t that will represent the amplitude of the current signal.
		*/
		void getAmp(uint16_t *amp);

		/**
		 * @brief Gets the current phase shift
		 * @param shift A uint8_t that will represen the phase shift of the current signal.
		 */
		void getShift(uint16_t *shift);

		/**
		* @brief Gets the current wave shape
		* @param shape A enum of type WaveShape that will represent the type of wave for the current signal.
		*/
		void getWave(WaveShape *shape);

		/**
		 * @brief Restarts DMA
		 * 
		 * @details The DMA channels can get out of sync when changing waveforms, to resolve this signals are restarted
		 * if the output is put into echo mode or when frequencies become equal to each other when they were not before
		 */
		void restartDMA();
};


#endif /* INC_SHANE_DACDRIVER_H_ */
