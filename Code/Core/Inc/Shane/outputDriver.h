/*
 * outputDriver.h
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */

#ifndef INC_SHANE_OUTPUTDRIVER_H_
#define INC_SHANE_OUTPUTDRIVER_H_
#include "allIncludes.h"

class outputDriver{
	dacDriver *DACchannel1;
	dacDriver *DACchannel2;
	displayQueue *displayInfoQ;
	struct displayInfoValues soonDisplayInfo;
public:
	outputDriver(dacDriver *DACchannel1I,dacDriver *DACchannel2I, displayQueue *displayInfoQI);
	void update();
};



#endif /* INC_SHANE_OUTPUTDRIVER_H_ */
