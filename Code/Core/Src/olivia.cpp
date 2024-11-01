/*
 * olivia.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: Olivia Cunningham
 */
#include "allIncludes.h"
#include <cmath>
#include <cassert>

//Waves Class (Application Class 1)
Waves::Waves(inputQueue *InputQueue, signalQueue *SignalQueue1, signalQueue *SignalQueue2)
{
	InputQueueInstance = InputQueue;
	SignalQueueInstance1 = SignalQueue1;
	SignalQueueInstance2 = SignalQueue2;
}

Waves::~Waves(){}
/*
void Waves::update()
{
	inputValues values;
	signalInfo sample1;
	signalInfo sample2;
	uint16_t shiftVal = 0;
	double shift = 0;

	//rushes to return if no change
	if(InputQueueInstance->dequeue(&values)){
			channelSelect = values.Switch;//0= ch 1, 1 = ch 2
			amplitude1 = values.AmpKnob1;
			amplitude2 = values.AmpKnob2;
			frequency1 = values.FreqKnob1;
			frequency2 = values.FreqKnob2;
			delay = values.DelayKnob2;
			waveSelect = values.isButtonPressed;
	}else{
		return;
	}

	setAmplitude();
	setFrequency();
	//waveType1 = SQUARE;
	//waveType2 = PULSE;

	//Channel 1 wave type select
	//Button is false don't change the wave type
	if(waveType1 == SINE and waveSelect == false and channelSelect == 0){
		waveType1 = SINE;
	}else if(waveType1 == SQUARE and waveSelect == false and channelSelect == 0){
		waveType1 =SQUARE;
	}else if(waveType1 == PULSE and waveSelect == false and channelSelect == 0){
		waveType1 = PULSE;

	//Button is true clock through the wave types
	}else if(waveType1 == SINE and waveSelect == true and channelSelect == 0){
		waveType1 = SQUARE;
	}else if(waveType1 == SQUARE and waveSelect == true and channelSelect == 0){
		waveType1 = PULSE;
	}else if(waveType1 == SQUARE and waveSelect == true and channelSelect == 0){
		waveType1 = SINE;
	}
	else{
		waveType1 = SINE;
	}
	//Channel 2 wave type select
	//Button is false don't change the wave type
	if(waveType2 == SINE and waveSelect == false and channelSelect == 1){
		waveType2 = SINE;
	}else if(waveType2 == SQUARE and waveSelect == false and channelSelect == 1){
		waveType2 = SQUARE;
	}else if(waveType2 == PULSE and waveSelect == false and channelSelect == 1){
		waveType2 = PULSE;
	}else if(waveType2 == ECHO and waveSelect == false and channelSelect == 1){
		waveType2 = ECHO;

	//Button is true clock through the wave types
	}else if(waveType2 == SINE and waveSelect == true and channelSelect == 1){
		waveType2 = SQUARE;
	}else if(waveType2 == SQUARE and waveSelect == true and channelSelect == 1){
		waveType2 = PULSE;
	}else if(waveType2 == PULSE and waveSelect == true and channelSelect == 1){
		waveType2 = ECHO;
	}else if(waveType2 == ECHO and waveSelect == true and channelSelect == 1){
		waveType2 = SINE;
	}
	else{
		waveType2 = SINE;
	}

	sample1.frequency = freqValue1;
	sample2.frequency = freqValue2;
	sample1.amp = ampValue1;
	sample2.amp = ampValue2;

	setDelay();
	shift = delayValue/8.0;
	shiftVal = waveFormRes*shift;//2*M_PI*freqValue1;//32

	//change channel 2 wave type and add the delay
	if(waveType1 == SINE and waveType2 == ECHO){
		waveType2 = SINE;
		sample2.frequency = sample1.frequency;
		sample2.amp = sample2.amp;

	}else if(waveType1 == SQUARE and waveType2 == ECHO){
		waveType2 = SQUARE;
		sample2.frequency = sample1.frequency;
		sample2.amp = sample1.amp;
		//shift = (delayValue/8)*2*M_PI*freqValue1;
	}else if(waveType1 == PULSE and waveType2 == ECHO){
		waveType2 = PULSE;
		sample2.frequency = sample1.frequency;
		sample2.amp = sample2.amp;
		//shift = (delayValue/8)*2*M_PI*freqValue1;
	}
	sample1.wave = waveType1;
	sample2.wave = waveType2;

	sample1.shiftAmount = 0;
	sample2.shiftAmount = shiftVal;
	setSine();
	setSquare();
	setPulse();
	for(uint16_t i = 0; i<waveFormRes; i++){
		sample1.signalLocations[i] = waveValues1[i];
		sample2.signalLocations[i] = waveValues2[i];
	}

	//Update the signalInfo struct
	SignalQueueInstance1->enqueue(sample1);
	SignalQueueInstance2->enqueue(sample2);
}
void Waves::setAmplitude()
{
    uint16_t count1 = 0;
    uint16_t count2 = 0;
    //int32_t rotation = 0;
    //Set channel 1 Amplitude based on knob values
	if(amplitude1 == 1 && ampValue1 <= 4095){
		count1+=1;
	}else if(amplitude1 == -1 && ampValue1 >= 0){
		count1-=1;
	}else{
	    count1+=0;
	}

	//Set channel 2 Amplitude based on knob values
	if(amplitude2 == 1 && ampValue2 <= 4095){
		count2+=1;
	}else if(amplitude2 == -1 &&  ampValue2 >= 0){
		count2-=1;
	}else{
	    count2+=0;
	}

	//Update the amplitude values
	//rotation = (count/3);
	ampValue1 = ampValue1+count1;
	ampValue2 = ampValue2+count2;
}

void Waves::setFrequency()
{
    int16_t count1 = 0;
    int16_t count2 = 0;
    //int32_t rotation = 0;

    //Set channel 1 Frequency based on knob values
	if(frequency1 == 1 && freqValue1 <= 990){
        count1+=10;
	}else if(frequency1 == -1 && freqValue1 >= 0){
	    count1-=10;
	}else{
	    count1+=0;
	}

	//Set channel 2 Frequency based on knob values
	if(frequency2 == 1 && freqValue2 <= 990){
		count2+=10;
	}else if(frequency2 == -1 && freqValue2 >= 0){
		count2-=10;
	}else{
	    count2+=0;
	}

	//Update the frequency values
	//rotation = (count/3);
	freqValue1 = freqValue1+count1;
	freqValue2 = freqValue2+count2;
}

void Waves::setSine()
{
	double invWaveRes = 1.0/waveFormRes;

	//Channel 1 Sine Wave
	if(waveType1 == SINE)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
		    waveValues1[i] = (ampValue1 * std::sin(invWaveRes*2*M_PI*freqValue1*i)+ampValue1);

		    //assertion to ensure signal values remain within expected range
		    assert(waveValues1[i] >= 0 && waveValues1[i] <= 2 * ampValue1);
		}
	}

	//Channel 2 Sine Wave
	if(waveType2 == SINE)
	{
		for (uint32_t i = 0; i < waveFormRes; i++)
		{
		    waveValues2[i] = (ampValue2 * std::sin((invWaveRes*2*M_PI*freqValue2*i)+delayValue)+ampValue2);

		    //assertion to ensure signal values remain within expected range
		    assert(waveValues1[i] >= 0 && waveValues2[i] <= 2 * ampValue2);
		}
	}
}

void Waves::setSquare()
{
	uint16_t delaySquareVal = 0;
	delaySquareVal = (waveFormRes*0.5)-delayValue;

	//Channel 1 Square wave
	if(waveType1 == SQUARE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(waveFormRes*0.5)){
				waveValues1[i] = ampValue1;
			}else{
				waveValues1[i] = 0;
			}
			//assertion to ensure generated signal is valid
			assert(waveValues1[i] >= 0 && waveValues2[i] <= 4095);
		}
	}

	//Channel 2 Square wave
	if(waveType2 == SQUARE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(delaySquareVal)){
				waveValues2[i] = ampValue2;
			}else{
				waveValues2[i] = 0;
			}
            //assertion to ensure generated signal is valid
            assert(waveValues2[i] >= 0 && waveValues2[i] <= 4095);
		}
	}
}

void Waves::setPulse()
{
	uint16_t delayPulseVal = 0;
	delayPulseVal = (waveFormRes*0.1)-delayValue;
	//Channel 1 Pulse wave
	if(waveType1 == PULSE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(waveFormRes*0.1)){
				waveValues1[i] = ampValue1;
			}else{
				waveValues1[i] = 0;
			}
		}
	}

	//Channel 2 Pulse wave
	if(waveType2 == PULSE){
		for (uint32_t i = 0; i < waveFormRes; i++){
			if(i<=(delayPulseVal)){
				waveValues2[i] = ampValue2;
			}else{
				waveValues2[i] = 0;
			}
		}
	}
}
*/
void Waves::setDelay()
{
    uint16_t count = 0;

    //Set the delay based on knob values
    if(delay == 1 && delayValue < 8){
	    count+=1;
    }else if(delay == -1 && delayValue >= 0){
	    count-=1;
    }else{
        count+=0;
    }

    //Update the delay value
	delayValue = delayValue+count;
}


//Semaphore Class
//Semaphore::Semaphore(){}

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
/*bool Semaphore::enqueue(bool msg)
{
	bool ok = false;
    if (tail == QUEUE_BUFFER_SIZE) {
        ok = false;
    }
    else{
        buffer[tail] = msg;
        tail = tail + 1;
        ok = true;
    }
    return ok;
}

bool Semaphore::dequeue(bool* msg)
{
	bool ok = false;
    if (tail == 0) {
        ok = false;
    }
    else{
        *msg = buffer[head];
        tail = tail - 1;
        ok = true;
    }
    return ok;
}*/



