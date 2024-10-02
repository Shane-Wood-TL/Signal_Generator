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
		//enum WaveShape{SINE, SQUARE, PULSE}shape;
		Waves(inputQueue *InputQueue, signalQueue *SignalQueue);
		~Waves();
    	void setSine();
    	void setSquare();
    	void setPulse();
    	void setDelay(uint8_t k);

	private:
    	inputQueue *InputQueueInstance;
    	signalQueue *SignalQueueInstance;
    	uint32_t frequency;
    	uint16_t amplitude;
    	bool followerMode;
    	uint32_t delay;
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
