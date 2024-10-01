/*
 * queue.h
 *
 *  Created on: Sep 26, 2024
 *      Author: townl
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_


#include "allIncludes.h"

//Title: Circular Queue in C++
//Name:  Shane Wood
//Class: ECE 373 Embedded Systems
//Date:  9/19/2024




class signalQueue{
	signalInfo buffer[QUEUE_BUFFER_SIZE]; //the buffer of messages
    uint8_t head = 0; //the head of the active queue region
    uint8_t tail = 0; //the tail of the active queue region
    uint32_t activeValues = 0; //the amount of active values

public:
    signalQueue(); //constructor
    bool enqueue(signalInfo msg); //add values
    bool dequeue(signalInfo* msg); //remove values
    void rollingMath(uint8_t *position); //does the math to handle rollovers
};


class displayQueue{
	displayInfo buffer[QUEUE_BUFFER_SIZE]; //the buffer of messages
    uint8_t head = 0; //the head of the active queue region
    uint8_t tail = 0; //the tail of the active queue region
    uint32_t activeValues = 0; //the amount of active values

public:
    displayQueue(); //constructor
    bool enqueue(displayInfo msg); //add values
    bool dequeue(displayInfo* msg); //remove values
    void rollingMath(uint8_t *position); //does the math to handle rollovers
};

class inputQueue{
	inputValues buffer[QUEUE_BUFFER_SIZE]; //the buffer of messages
    uint8_t head = 0; //the head of the active queue region
    uint8_t tail = 0; //the tail of the active queue region
    uint32_t activeValues = 0; //the amount of active values

public:
    inputQueue(); //constructor
    bool enqueue(inputValues msg); //add values
    bool dequeue(inputValues* msg); //remove values
    void rollingMath(uint8_t *position); //does the math to handle rollovers
};

#endif /* INC_QUEUE_H_ */
