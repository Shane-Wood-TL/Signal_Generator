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
		Waves();
		~Waves();
    	void setChannel(WaveShape shape, uint32_t freq, uint32_t amp, bool followerMode, uint32_t delay);
    	int32_t setDelay(uint8_t k);

	private:
    	enum WaveShape{SINE, SQUARE, PULSE}shape;
    	uint32_t frequency;
    	uint32_t amplitude;
    	bool followerMode;
    	uint32_t delay;
};
class Semaphor
{
	public:
		Semaphor();
		~Semaphor();
};





#endif /* INC_OLIVIA_H_ */
