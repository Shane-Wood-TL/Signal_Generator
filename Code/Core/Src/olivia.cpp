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
	channelSelect = values.Switch;//0= ch 1, 1 = ch 2
	amplitude1 = values.AmpKnob1;
	amplitude2 = values.AmpKnob2;
	frequency1 = values.FreqKnob1;
	frequency2 = values.FreqKnob2;
	delay = values.DelayKnob2;
	waveSelect = values.isButtonPressed;

	if(waveType1 == SINE and waveSelect == false and channelSelect == 0){
		waveType1 = SINE;
	}else if(waveType1 == SQUARE and waveSelect == false and channelSelect == 0){
		waveType1 =SQUARE;
	}else if(waveType1 == PULSE and waveSelect == false and channelSelect == 0){
		waveType1 = PULSE;
	}else if(waveType1 == SINE and waveSelect == true and channelSelect == 0){
		waveType1 = SQUARE;
	}else if(waveType1 == SQUARE and waveSelect == true and channelSelect == 0){
		waveType1 = PULSE;
	}else{//(waveType1 == PULSE and waveSelect == true)
		waveType1 = SINE;
	}

	if(waveType2 == SINE and waveSelect == false and channelSelect == 1){
		waveType2 = SINE;
	}else if(waveType2 == SQUARE and waveSelect == false and channelSelect == 1){
		waveType2 = SQUARE;
	}else if(waveType2 == PULSE and waveSelect == false and channelSelect == 1){
		waveType2 = PULSE;
	}else if(waveType2 == ECHO and waveSelect == false and channelSelect == 1){
		waveType2 = ECHO;
	}else if(waveType2 == SINE and waveSelect == true and channelSelect == 1){
		waveType2 = SQUARE;
	}else if(waveType2 == SQUARE and waveSelect == true and channelSelect == 1){
		waveType2 = PULSE;
	}else if(waveType2 == PULSE and waveSelect == true and channelSelect == 1){
		waveType2 = ECHO;
	}else{//(waveType2 == PULSE and waveSelect == true)
		waveType2 = SINE;
	}
}

void Waves::setSine()
{
	signalInfo sample1;
	signalInfo sample2;
	//enum WaveShape waveType1 = SINE;
	//enum WaveShape waveType2 = SINE;

	update();
	sample2.shiftAmount = setDelay(delay);

	//Channel 1 Sine Wave
	if(waveType1 == SINE)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
		    // Calculate the sine value and scale by amplitude
		    sample1.signalLocations[i] = (amplitude1 * std::sin(2 * M_PI * frequency1 * ((double)i / waveFormRes)));
		}
	}
	//Channel 2 Sine Wave
	if(waveType2 == SINE)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
		    // Calculate the sine value and scale by amplitude
		    sample2.signalLocations[i] = (amplitude2 * std::sin(2 * M_PI * frequency2 * ((double)i / waveFormRes))+sample2.shiftAmount);
		}
	}
}
void Waves::setSquare()
{
	signalInfo sample1;
	signalInfo sample2;
	update();
	sample2.shiftAmount = setDelay(delay);
	if(waveType1 == SQUARE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(waveFormRes*0.5)){
				sample1.signalLocations[i] = amplitude1;
			}else{
				sample1.signalLocations[i] = 0;
			}
		}
	}
	if(waveType2 == SQUARE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(waveFormRes*0.5)){
				sample2.signalLocations[i] = amplitude2;
			}else{
				sample2.signalLocations[i] = 0;
			}
		}
	}
}

void Waves::setPulse()
{
	signalInfo sample1;
	signalInfo sample2;
	update();
	sample2.shiftAmount = setDelay(delay);
	if(waveType1 == PULSE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(waveFormRes*0.1)){
				sample1.signalLocations[i] = amplitude1;
			}else{
				sample1.signalLocations[i] = 0;
			}
		}
	}
	if(waveType2 == PULSE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(waveFormRes*0.1)){
				sample2.signalLocations[i] = amplitude2;
			}else{
				sample2.signalLocations[i] = 0;
			}
		}
	}
}

uint16_t Waves::setDelay(uint8_t k)
{
	uint16_t shift;
	if(waveType1 == SINE and waveType2 == ECHO){
		waveType2 = SINE;
		shift = k/8;
	}else if(waveType1 == SQUARE and waveType2 == ECHO){
		waveType2 = SQUARE;
		shift = k/8;
	}else if(waveType1 == PULSE and waveType2 == ECHO){
		waveType2 = PULSE;
		shift = k/8;
	}else{
		shift = 0;
	}
	return shift;
}

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

