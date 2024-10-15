/*
 * queue.h
 *
 *  Created on: Sep 26, 2024
 *      Author: Shane Wood
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_


#include "allIncludes.h"




class signalQueue {
	signalInfo buffer[SIGNAL_QUEUE_SIZE]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    signalQueue(); //constructor
	bool enqueue(signalInfo msg); //add values
	bool dequeue(signalInfo* msg); //remove values
};



class displayQueue {
	displayInfo buffer[DISPLAY_QUEUE_SIZE]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    displayQueue(); //constructor
	bool enqueue(displayInfo msg); //add values
	bool dequeue(displayInfo* msg); //remove values
};



class inputQueue {
	inputValues buffer[INPUT_QUEUE_SIZE]; //the buffer of messages
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
    inputQueue(); //constructor
	bool enqueue(inputValues msg); //add values
	bool dequeue(inputValues* msg); //remove values
};

#endif /* INC_QUEUE_H_ */
