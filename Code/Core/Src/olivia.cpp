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

	values.Switch = 0;
	values.AmpKnob1 = 0;
	values.AmpKnob2 = 0;
	values.FreqKnob1 = 0;
	values.FreqKnob2 = 0;
	values.DelayKnob2 = 0;
	values.isButtonPressed = false;
	followerMode = values.Switch;//-1 = no change, 0 = false(independent), 1 = true(follow)
	amplitude1 = values.AmpKnob1;
	amplitude2 = values.AmpKnob2;
	frequency1 = values.FreqKnob1;
	frequency2 = values.FreqKnob2;
	delay = values.DelayKnob2;
	waveSelect = values.isButtonPressed;
	if(waveType1 == SINE and waveSelect == false)
	{
		waveType1 = SINE;
	}
	else if(waveType1 == SQUARE and waveSelect == false)
	{
		waveType1 =SQUARE;
	}
	else if(waveType1 == PULSE and waveSelect == false)
	{
		waveType1 = PULSE;
	}
	else if(waveType1 == SINE and waveSelect == true)
	{
		waveType1 = SQUARE;
	}
	else if(waveType1 == SQUARE and waveSelect == true)
	{
		waveType1 = PULSE;
	}
	else//(waveType1 == PULSE and waveSelect == true)
	{
		waveType1 = SINE;
	}

	if(waveType2 == SINE and waveSelect == false)
	{
		waveType2 = SINE;
	}
	else if(waveType2 == SQUARE and waveSelect == false)
	{
		waveType2 =SQUARE;
	}
	else if(waveType2 == PULSE and waveSelect == false)
	{
		waveType2 = PULSE;
	}
	else if(waveType2 == SINE and waveSelect == true)
	{
		waveType2 = SQUARE;
	}
	else if(waveType2 == SQUARE and waveSelect == true)
	{
		waveType2 = PULSE;
	}
	else//(waveType2 == PULSE and waveSelect == true)
	{
		waveType2 = SINE;
	}
}

void Waves::setSine()
{
	signalInfo sample;
	//enum WaveShape waveType1 = SINE;
	//enum WaveShape waveType2 = SINE;

	update();

	//Channel 1 Sine Wave
	if(waveType1 == SINE and followerMode == 0)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
		    // Calculate the sine value and scale by amplitude
		    sample.signalLocations[i] = (amplitude1 * std::sin(2 * M_PI * frequency1 * ((double)i / waveFormRes)));
		}
	}
	//Channel 2 Sine Wave
	if(waveType2 == SINE and followerMode == 0)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
		    // Calculate the sine value and scale by amplitude
		    sample.signalLocations[i] = (amplitude2 * std::sin(2 * M_PI * frequency2 * ((double)i / waveFormRes)));
		}
	}
}
void Waves::setSquare()
{
	signalInfo sample;
	update();
	if(waveType1 == SQUARE and followerMode == 0)
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

	if(waveType2 == SQUARE and followerMode == 0)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
			if(i<=(waveFormRes/2))
			{
				sample.signalLocations[i] = amplitude2;
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
	signalInfo sample;
	update();
	if(waveType1 == PULSE and followerMode == 0)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
			if(i<=(waveFormRes*0.1))
			{
				sample.signalLocations[i] = amplitude1;
			}
			else
			{
				sample.signalLocations[i] = 0;
			}
		}
	}

	if(waveType2 == PULSE and followerMode == 0)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
			if(i<=(waveFormRes*0.1))
			{
				sample.signalLocations[i] = amplitude2;
			}
			else
			{
				sample.signalLocations[i] = 0;
			}
		}
	}
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

