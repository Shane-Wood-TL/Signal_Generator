/*
 * olivia.h
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#ifndef INC_OLIVIA_H_
#define INC_OLIVIA_H_
#include "main.h"

#define Q_SIZE 3

class Waves
{
	public:
		enum WaveShape{SINE, SQUARE, PULSE}shape;
		Waves();
		~Waves();
    	void setChannel(WaveShape shape, uint32_t freq, uint32_t amp, bool followerMode, uint32_t delay);
    	uint32_t setDelay(uint8_t k);

	private:

    	uint32_t frequency;
    	uint32_t amplitude;
    	bool followerMode;
    	uint32_t delay;
};

class signalQueue
{
	public:
		signalQueue();
		~signalQueue();
    	bool signalEnqueue(int32_t msg);
    	bool signalDequeue(int32_t *msg);

	private:
    	int32_t head;
    	int32_t tail;
    	int32_t buffer[Q_SIZE];

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
