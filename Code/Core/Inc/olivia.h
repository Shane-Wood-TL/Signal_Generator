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
    	int8_t followerMode;//switch
    	bool waveSelect;//button
    	uint32_t delay;
    	enum WaveShape waveType1;
    	enum WaveShape waveType2;
};


class Semaphore{
	bool buffer[1]; //the buffer of messages
    uint8_t head = 0; //the head of the active queue region
    uint8_t tail = 0; //the tail of the active queue region
    uint32_t activeValues = 0; //the amount of active values

public:
    Semaphore(); //constructor
    bool enqueue(bool msg); //add values
    bool dequeue(bool* msg); //remove values
    void rollingMath(uint8_t *position); //does the math to handle rollovers
};

#endif /* INC_OLIVIA_H_ */
