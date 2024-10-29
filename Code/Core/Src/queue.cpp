/*
 * queue.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: Shane Wood
 */

#include "allIncludes.h"



signalQueue::signalQueue() {
	//set all values to 0
	head = 0;
	tail = 0;
}

bool signalQueue::enqueue(struct signalInfo msg) {
	bool ok = false;
	uint8_t nextTail = tail;
	rollingMath(&nextTail);
	if(nextTail != head) { //act as normal
		buffer[tail] = msg; //put the message in the buffer
		tail = nextTail; //increment the tail
		ok = true; //value added successfully
	} else {
		ok = false; //queue is full / if increased tail = head and dequeue wont know
		//if it is empty or full (Max values enqueued at one point is QUEUE_BUFFER_SIZE-1)
	}
	return ok;
}


bool signalQueue::dequeue(struct signalInfo *msg) {
	bool ok = false;
	if(head==tail) {
		ok = false; //no values in queue
	} else {
		*msg = buffer[head]; //get the value at the head
		rollingMath(&head); //increase head by 1, to get next head
		ok = true;
	}
	return ok;
}

void signalQueue::rollingMath(uint8_t *position){
    //if it is at the max value go back to 0
    if((*position) >= SIGNAL_QUEUE_SIZE-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position+=1;
    }
}




displayQueue::displayQueue() {
	//set all values to 0
	head = 0;
	tail = 0;
}

bool displayQueue::enqueue(struct displayInfoValues msg) {
	bool ok = false;
	uint8_t nextTail = tail;
	rollingMath(&nextTail);
	if(nextTail != head) { //act as normal
		buffer[tail] = msg; //put the message in the buffer
		tail  = nextTail; //increment the tail
		ok = true; //value added successfully
	} else {
		ok = false; //queue is full / if increased tail = head and dequeue wont know
		//if it is empty or full (Max values enqueued at one point is QUEUE_BUFFER_SIZE-1)
	}
	return ok;
}


bool displayQueue::dequeue(struct displayInfoValues *msg) {
	bool ok = false;
	if(head==tail) {
		ok = false; //no values in queue
	} else {
		*msg = buffer[head]; //get the value at the head
		rollingMath(&head); //increase head by 1, to get next head
		ok = true;
	}
	return ok;
}

void displayQueue::rollingMath(uint8_t *position){
    //if it is at the max value go back to 0
    if((*position) >= DISPLAY_QUEUE_SIZE-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position+=1;
    }
}





inputQueue::inputQueue() {
	//set all values to 0
	head = 0;
	tail = 0;
}

bool inputQueue::enqueue(inputValues msg) {
	bool ok = false;
	uint8_t nextTail = tail;
	rollingMath(&nextTail);
	if(nextTail != head) { //act as normal
		buffer[tail] = msg; //put the message in the buffer
		tail= nextTail; //increment the tail
		ok = true; //value added successfully
	} else {
		ok = false; //queue is full / if increased tail = head and dequeue wont know
		//if it is empty or full (Max values enqueued at one point is QUEUE_BUFFER_SIZE-1)
	}
	return ok;
}


bool inputQueue::dequeue(inputValues *msg) {
	bool ok = false;
	if(head==tail) {
		ok = false; //no values in queue
	} else {
		*msg = buffer[head]; //get the value at the head
		rollingMath(&head); //increase head by 1, to get next head
		ok = true;
	}
	return ok;
}

void inputQueue::rollingMath(uint8_t *position){
    //if it is at the max value go back to 0
    if((*position) >= INPUT_QUEUE_SIZE-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position+=1;
    }
}
