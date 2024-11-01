/*
 * queue.h
 *
 *  Created on: Sep 26, 2024
 *      Author: Shane Wood
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_


#include "allIncludes.h"

#define DISPLAY_QUEUE_SIZE 3
#define INPUT_QUEUE_SIZE 3
#define SIGNAL_QUEUE_SIZE 3
#define QUEUE_BUFFER_SIZE 2 //currently only the semaphore is using this


class signalQueue {
	struct signalInfo buffer[SIGNAL_QUEUE_SIZE]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    signalQueue(); //constructor
	bool enqueue(struct signalInfo msg); //add values
	bool dequeue(struct signalInfo* msg); //remove values
};



class displayQueue {
	struct displayInfoValues buffer[DISPLAY_QUEUE_SIZE]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    displayQueue(); //constructor
	bool enqueue(struct displayInfoValues msg); //add values
	bool dequeue(struct displayInfoValues* msg); //remove values
};



class inputQueue {
	struct inputValues buffer[INPUT_QUEUE_SIZE]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    inputQueue(); //constructor
	bool enqueue(struct inputValues msg); //add values
	bool dequeue(struct inputValues* msg); //remove values
};

#endif /* INC_QUEUE_H_ */
