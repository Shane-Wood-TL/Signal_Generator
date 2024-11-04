/**
 * @file outputDriver.h
 * @brief This file contains the definition of the outputDriver class
 *  Created on: Oct 29, 2024
 *      Author: Shane Wood
 */

#ifndef INC_SHANE_OUTPUTDRIVER_H_
#define INC_SHANE_OUTPUTDRIVER_H_
#include "allIncludes.h"

/**
 * @class outputDriver
 * @brief Dual channel DAC driver, and enqueues data for display
 * 
 * @details Updates the dacDriver instances, calls the dequeuing. Also ensures that the signals stay in sync when changing frequiences
 */
class outputDriver{
	dacDriver *DACchannel1; ///< dacDriver for channel 1
	dacDriver *DACchannel2; ///< dacDriver for channel 2
	displayQueue *displayInfoQ; ///< display queue
	uint16_t oldFreq1; ///< frequency for ch1 from the last update
	uint16_t oldFreq2; ///< frequency for ch2 from the last update
public:
	/**
	 * @brief constructs a outputDriver instance
	 * 
	 * @param DACchannel1I The dacDriver for channel 1
	 * @param DACchannel2I The dacDriver for channel 2
	 * @param displayInfoQI The queue for passing infomation to the display
	 */
	outputDriver(dacDriver *DACchannel1I,dacDriver *DACchannel2I, displayQueue *displayInfoQI);

	/**
	 * @brief update and resync the dacDrivers
	 * 
	 * @details Waves will get out of sync when frequinces are changed. To fix this when waves are brough back to the same frequency
	 * they are resynced back together by restarting DMA. The same thing occurs for ECHO as the timing inbetween the waves needs to be exact
	 */
	void update();
};



#endif /* INC_SHANE_OUTPUTDRIVER_H_ */
