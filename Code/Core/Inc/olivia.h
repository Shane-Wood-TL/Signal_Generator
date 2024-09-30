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
		enum WaveShape{SINE, SQUARE, PULSE}shape;
		Waves();
		~Waves();
    	void setSine();
    	void setSquare();
    	void setPulse();
    	void setDelay(uint8_t k);

	private:

    	uint32_t frequency;
    	uint16_t amplitude;
    	bool followerMode;
    	uint32_t delay;
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
