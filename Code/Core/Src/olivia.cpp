/*
 * olivia.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */
#include "allIncludes.h"
#include <vector>
#include <cmath>

//Waves Class (Application Class 1)
Waves::Waves(inputQueue *InputQueue, signalQueue *SignalQueue){}

Waves::~Waves(){}

void Waves::update()
{
	inputValues values;
	followerMode = values.ChannelSel;
	//figure out modeSel(enum WaveShape
	//enum WaveShape waveType1;
	//waveType1 = values.ModeSel;
	amplitude1 = values.AmpValue1;
	amplitude2 = values.AmpValue2;
	frequency1 = values.FreqValue1;
	frequency2 = values.FreqValue2;
	delay = values.DelayValue2;
}

void Waves::setSine()
{
	signalInfo sample;
	//enum WaveShape waveType1 = SINE;
	//enum WaveShape waveType2 = SINE;
	double angle1;
	double angle2;

	update();

	//Channel 1 Sine Wave
	if(waveType1 == SINE and followerMode == false)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
			// Calculate the angle in radians
		    angle1 = 2 * M_PI * frequency1 * static_cast<double>(i) / waveFormRes;
		    // Calculate the sine value and scale by amplitude
		    sample.signalLocations[i] = (amplitude1 * std::sin(angle1));
		}
	}
	//Channel 2 Sine Wave
	if(waveType2 == SINE and followerMode == false)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
			// Calculate the angle in radians
		    angle2 = 2 * M_PI * frequency2 * static_cast<double>(i) / waveFormRes;
		    // Calculate the sine value and scale by amplitude
		    sample.signalLocations[i] = (amplitude2 * std::sin(angle2));
		}
	}
}
void Waves::setSquare()
{
	double period;
	double halfPeriod;
	period = 1/frequency1;
	halfPeriod = period/2;
}

void Waves::setPulse(){}

void Waves::setDelay(uint8_t k){}

//Semaphore Class
bool Semaphore::enqueue(bool msg) {
	bool ok = false;
	uint8_t nextTail = tail;
	rollingMath(&nextTail);
	if(nextTail != head) { //act as normal
		buffer[tail] = msg; //put the message in the buffer
		rollingMath(&tail); //increment the tail
		ok = true; //value added successfully
	} else {
		ok = false; //queue is full / if increased tail = head and dequeue wont know
		//if it is empty or full (Max values enqueued at one point is QUEUE_BUFFER_SIZE-1)
	}
	return ok;
}


bool Semaphore::dequeue(bool *msg) {
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

void Semaphore::rollingMath(uint8_t *position){
    //if it is at the max value go back to 0
    if((*position) >= QUEUE_BUFFER_SIZE-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position+=1;
    }
}

