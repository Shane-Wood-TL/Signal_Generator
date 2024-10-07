/*
 * olivia.h
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#ifndef INC_OLIVIA_H_
#define INC_OLIVIA_H_
#include "main.h"

class Waves
{
	public:
		Waves(inputQueue *InputQueue, signalQueue *SignalQueue);
		~Waves();
    	void setSine();
    	void setSquare();
    	void setPulse();
    	void setDelay(uint8_t k);
    	void update();

	private:
    	inputQueue *InputQueueInstance;
    	signalQueue *SignalQueueInstance;
    	uint32_t frequency1;
    	uint16_t amplitude1;
    	uint16_t frequency2;
    	uint16_t amplitude2;
    	bool followerMode;
    	uint32_t delay;
    	enum WaveShape waveType1;
    	enum WaveShape waveType2;
};

class Semaphore
{
	public:
		Semaphore();
		~Semaphore();
		int32_t wait();
		int32_t post();
	private:
		int32_t count;
};

#endif /* INC_OLIVIA_H_ */
