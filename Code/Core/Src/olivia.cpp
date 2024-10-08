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
	values.Switch = false;
	values.AmpKnob1 = 0;
	values.AmpKnob2 = 0;
	values.FreqKnob1 = 0;
	values.FreqKnob2 = 0;
	values.DelayKnob2 = 0;
	followerMode = values.Switch;
	//figure out modeSel(enum WaveShape
	//enum WaveShape waveType1;
	//waveType1 = values.ModeSel;
	amplitude1 = values.AmpKnob1;
	amplitude2 = values.AmpKnob2;
	frequency1 = values.FreqKnob1;
	frequency2 = values.FreqKnob2;
	delay = values.DelayKnob2;
	//switch{waveShape}
	//case SINE:
		//default

}

void Waves::setSine()
{
	signalInfo sample;
	//enum WaveShape waveType1 = SINE;
	//enum WaveShape waveType2 = SINE;
	uint32_t angle1;
	uint32_t angle2;

	update();

	//Channel 1 Sine Wave
	if(waveType1 == SINE and followerMode == false)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
			// Calculate the angle in radians
		    angle1 = 2 * M_PI * frequency1 * (i/waveFormRes);//static_cast<double>(i) / waveFormRes;
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
		    angle2 = 2 * M_PI * frequency2 * (i/waveFormRes);//static_cast<double>(i) / waveFormRes;
		    // Calculate the sine value and scale by amplitude
		    sample.signalLocations[i] = (amplitude2 * std::sin(angle2));
		}
	}
}
void Waves::setSquare()
{
	signalInfo sample;
	/*double period;
	double halfPeriod;
	period = 1/frequency1;
	halfPeriod = period/2;*/
	//don't use period or frequency only use amplitude to control height
	//only goes down to zero
	//pass frequency to shane
	if(waveType1 == SQUARE and followerMode == false)
		{
			for (uint32_t i = 0; i < waveFormRes; i++)
			{
				if(i<=(waveFormRes/2))
				{
					sample.signalLocations[i] = amplitude1;
				}
				else
				{
					sample.signalLocations[i] = 0;
				}
			}
		}
}

void Waves::setPulse()
{
	//waveFormRes*.1 = amplitude1;
}

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

