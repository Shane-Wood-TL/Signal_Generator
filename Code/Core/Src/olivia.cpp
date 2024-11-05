/*
 * olivia.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: Olivia Cunningham
 */
#include "allIncludes.h"
#include <cassert>

//set the head and tail to 0
signalShifter::signalShifter() {
	head = 0;
	tail = 0;
	static_assert(waveFormRes > 0);
}
//enqueue a point
bool signalShifter::enqueue(uint32_t msg) {
	if(msg > 4095){
		return false;
	}
	assert(msg <= 4095);
	if(full){
		return false;
	}else{
		buffer[tail] = msg; //put the message in the buffer
		rollingMath(&tail);

		if(tail == head){
			full = true;
		}
		return true;
	}
}

//dequeue a point
bool signalShifter::dequeue(uint32_t *msg) {
	assert(msg != nullptr);
	if(msg == nullptr){
		return false;
	}
	if(full == false && head == tail){
		return false;
	}else{
		*msg = buffer[head]; //get the value at the head
		rollingMath(&head); //increase head by 1, to get next head
		full = false;
		return true;
	}
}

//use circular queue, to shift indices
void signalShifter::rollingMath(uint8_t *position){
	if(position == nullptr){
		return;
	}
	assert(position != nullptr);
	assert(!(*position > waveFormRes));
    //if it is at the max value go back to 0
    if((*position) >= waveFormRes-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position += 1;
    }
}

//overall shifter
void signalShifter::shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint8_t shiftAmt){
	assert(currentPositions != nullptr);
	assert(newPositions != nullptr);
	assert(shiftAmt >= 0);
	uint8_t sizeOfShift = sizeof(shiftAmt);
	if((currentPositions == nullptr) || (newPositions == nullptr) || (sizeOfShift != 1)){
		return;
	}
	//enqueue the entire waveform
    for(uint16_t i = 0; i < waveFormRes; i++) {
    	bool enqueueS = enqueue(currentPositions[i]);
    	if(!enqueueS){
    		return;
    	}
    }

    // Perform the shift by dequeuing and enqueuing the required number of times
    for(uint16_t i = 0; i < waveFormRes-shiftAmt; i++) {
    	uint32_t temp;
    	bool dequeueS;
    	bool enququeS;
        dequeueS = dequeue(&temp);  // Remove the front element
        enququeS = enqueue(temp);    // Add it back to the end
        if((!dequeueS) || (!enququeS)){
        	return;//something has went wrong, try to recover later
        }
    }

    // Extract the shifted values into the newPositions array
    for(uint16_t i = 0; i  < waveFormRes; i++) {
        dequeue(&newPositions[i]);
    }
}

Waves::Waves(){
	setSine();
	setSquare();
	setPulse();
}

void Waves::setSine(){
	sinePlot.amp = 3971;
	sinePlot.frequency = 100;
	sinePlot.shiftAmount = 0;
	sinePlot.wave = SINE;
	for (uint16_t i = 0; i < waveFormRes; i++){
		//copy the table into the struct
		sinePlot.signalLocations[i] = sineWaveTable[i];
	}
}

void Waves::setSquare(){
	squarePlot.amp = 4095;
	squarePlot.frequency = 100;
	squarePlot.shiftAmount = 0;
	squarePlot.wave = SQUARE;
	for (uint16_t i = 0; i < waveFormRes; i++){
		squarePlot.signalLocations[i] = squareWaveTable[i];
	}
}

void Waves::setPulse(){
	pulsePlot.amp = 4095;
	pulsePlot.frequency = 100;
	pulsePlot.shiftAmount = 0;
	pulsePlot.wave = PULSE;
	for (uint16_t i = 0; i < waveFormRes; i++){
		pulsePlot.signalLocations[i] = pulseWaveTable[i];
	}
}

signalInfo Waves::getSquarePlot(){
	return squarePlot;
}

signalInfo Waves::getPulsePlot(){
	return pulsePlot;
}

signalInfo Waves::getSinePlot(){
	return sinePlot;
}

signalInfo Waves::getDelay(signalInfo toShift, uint16_t amount){
	if(toShift.frequency <= 0){
		return getSinePlot();
	}else if(amount ==0){
		return toShift;
	}
	signalInfo modifiedWave;
	modifiedWave.shiftAmount = amount;
	//handle the shifting
	signalShifter shifter;
	shifter.shiftWaveform(toShift.signalLocations, modifiedWave.signalLocations, amount);
	modifiedWave.wave = ECHO; //force new wave to echo
	return modifiedWave;
}

void Waves::scale(signalInfo *toScale, uint16_t newAmp){
	if((toScale == nullptr) || (newAmp >= 4096)){
		return;
	}
	//get a new copy of the wave, and adjust it's amplitude
	assert(toScale != nullptr);
	signalInfo tempWave;
	if(toScale->wave == SINE){
		tempWave = getSinePlot();
	}else if(toScale->wave == SQUARE){
		tempWave = getSquarePlot();
	}else{
		tempWave = getPulsePlot();
	}

	for(uint16_t i = 0; i < waveFormRes; i++){
		if(toScale->wave != SINE){
			toScale->signalLocations[i] = (uint32_t)(tempWave.signalLocations[i]*newAmp/4096);
		}else{
			if(newAmp >= 3971){
				newAmp = 3971;
			}
			toScale->signalLocations[i] = (uint32_t)(tempWave.signalLocations[i]*newAmp/3971);
		}
	}
	toScale->amp = newAmp;
}

void applicationLayer::checkFreq(uint16_t *freq, int8_t incAmt){
	if((freq == nullptr) || (incAmt==0)){
		return;
	}
	assert(freq != nullptr);
	assert(incAmt != 0);
    uint32_t newFreq = (*freq)+ incAmt;
    if (incAmt > 0) {
        if (newFreq > maxFreq) {
            *freq = maxFreq;
        } else {
            *freq = newFreq;
        }
    } else {
        if (newFreq < minFreq) {
            *freq = minFreq;
        } else {
            *freq = newFreq;
        }
    }
}

//safely increase /decrease the amplitude
void applicationLayer::checkAmp(uint16_t *amp, int8_t incAmt){
	if((amp == nullptr) || (incAmt == 0)){
		return;
	}
	assert(amp != nullptr);
	assert(incAmt != 0);
	uint16_t newAmp = (*amp)+ incAmt;
	    if (incAmt > 0){
	        if(newAmp < *amp || newAmp > 4095){
	            *amp = 4095;
	            return;
	        }
	    }else{
	        if(newAmp > *amp){
	            *amp = 0;
	            return;
	        }
	    }
	    *amp = newAmp;
}

//safely increase / decrease the amplitude
void applicationLayer::checkDelay(uint16_t *shift, int8_t incAmt){
	if((shift == nullptr) || (incAmt == 0)){
		return;
	}
	assert(shift != nullptr);
	assert(incAmt != 0);
	uint16_t newShift = (*shift) + incAmt;
	if (incAmt > 0){
		if(newShift < *shift || newShift > 256){
			*shift = 256;
			return;
		}
	}else{
		if(newShift > *shift){
			*shift = 0;
			return;
		}
	}
	*shift = newShift;
}

//constructor ....
applicationLayer::applicationLayer(inputQueue *InputQueue, signalQueue *SignalQueue1, signalQueue *SignalQueue2){
	if((InputQueue == nullptr) || (SignalQueue1 == nullptr) || (SignalQueue2 == nullptr)){
		NVIC_SystemReset();
	}
	assert(InputQueue != nullptr);
	assert(SignalQueue1 != nullptr);
	assert(SignalQueue2 != nullptr);
	InputQueueInstance = InputQueue;
	SignalQueueInstance1 = SignalQueue1;
	SignalQueueInstance2 = SignalQueue2;

	currentWave1 = waveGen.getSinePlot();
	currentWave2 = waveGen.getSinePlot();
	SignalQueue1->enqueue(currentWave1);
	SignalQueue2->enqueue(currentWave2);
}

//go to the next wave type
void applicationLayer::increaseWaveType(WaveShape *currentWave){
	if(currentWave == nullptr){
		return;
	}
	assert(currentWave != nullptr);
	switch (*currentWave){
	case(SINE):{
		*currentWave = SQUARE;
		break;
	}
	case(SQUARE):{
		*currentWave = PULSE;
		break;
	}
	case(PULSE):{
		if(channelToChange == 1){
			*currentWave = SINE;
			break;
		}else{;
			*currentWave = ECHO; //only channel 2 has echo
			break;
		}
		break;
	}
	case(ECHO):{
		*currentWave = SINE;
		break;
	}
	default:
		*currentWave = SINE;
		break;
	}
	return;
}

//update the freq based on the knob
void applicationLayer::setFrequency(signalInfo *signal, int8_t knobValue){
	if(signal == nullptr){
		return;
	}
	assert(signal != nullptr);
	int8_t amtToChangeBy = 0;
	if(knobValue == 0){
		return;
	}else if(knobValue == 1){ //use stepped increments; 0,1,2,3,...10,20,30,....,100,200,300
		if(signal->frequency < 10){
			amtToChangeBy = 1;
		}else if(signal->frequency < 100){
			amtToChangeBy = 10;
		}else{
			amtToChangeBy = 100;
		}
	}else if (knobValue == -1){
		if(signal->frequency > 100){
			amtToChangeBy = -100;
		}else if(signal->frequency > 10){
			amtToChangeBy = -10;
		}else{
			amtToChangeBy = -1;
		}
	}
	checkFreq(&signal->frequency, amtToChangeBy); //ensure that freq stays a legal value
}

//update amp based on the knob
void applicationLayer::setAmplitude(signalInfo *signal, int8_t knobValue){
	if(signal == nullptr){
		return;
	}
	assert(signal != nullptr);
	if(knobValue == 0){
		return;
	}
	else if(knobValue == 1){
		checkAmp(&signal->amp, 124); //step by 0.1V
	}else if(knobValue == -1){
		checkAmp(&signal->amp, -124);//ensure that amp stays a legal value
	}else{
		return;
	}
	waveGen.scale(signal, signal->amp); //apply the scaling
	return;
}

void applicationLayer::updateWave(signalInfo *signal){ //get a fresh copy of the wave to modify
	if(signal == nullptr){
		return;
	}
	assert(signal != nullptr);
	signalInfo newWave;
	newWave.amp = signal->amp;
	newWave.frequency = signal->frequency;
	increaseWaveType(&signal->wave);

	switch (signal->wave) {
		case SINE:
			*signal = waveGen.getSinePlot();
			break;
		case SQUARE:
			*signal = waveGen.getSquarePlot();
			break;
		case PULSE:
			*signal = waveGen.getPulsePlot();
			break;
		case ECHO:
			break;
		default:
			*signal = waveGen.getSinePlot();
			break;
		}

		waveGen.scale(signal, newWave.amp); //reapply the amplitude
		signal->frequency = newWave.frequency; //reapply the frequency
}

void applicationLayer::echoMode(inputValues *currentInput){
	if(currentInput==nullptr){
		return;
	}
	assert(currentInput != nullptr);
	if(currentInput->DelayKnob == 1) {//increase delay by 45 deg
		checkDelay(&currentWave2Echo.shiftAmount, 32);
		} else if(currentInput->DelayKnob == -1) {
		    checkDelay(&currentWave2Echo.shiftAmount, -32);
		}

	if(currentWave2Echo.shiftAmount != 0) {
		currentWave2Echo = waveGen.getDelay(currentWave1, currentWave2Echo.shiftAmount); //if there is shifting to be done; do it
	}else{
	// Copy signal locations
		for(uint16_t i = 0; i < waveFormRes; i++) {
			currentWave2Echo.signalLocations[i] = currentWave1.signalLocations[i];
		}
	}

	// Ensure frequency and amplitude of currentWave2 are consistent with currentWave1
	currentWave2Echo.frequency = currentWave1.frequency;
	currentWave2Echo.amp = currentWave1.amp;
	currentWave2Echo.wave = ECHO;
}

void applicationLayer::update(){
	static inputValues values;
	//see if there is data + know what switch to use
	bool newData = InputQueueInstance->dequeue(&values);
	if(newData){
		if(values.Switch == 0){
				channelToChange = 1;
			}else{
				channelToChange = 2;
			}
	}else{
		return;
	}

	//only change info for frequency, not the table
	if(channelToChange == 1){
		if(values.isButtonPressed){
			updateWave(&currentWave1);
		}
		setFrequency(&currentWave1, values.FreqKnob);
		setAmplitude(&currentWave1, values.AmpKnob);
	}else if(channelToChange == 2){
		if(values.isButtonPressed){
			updateWave(&currentWave2);
		}
		if(currentWave2.wave != ECHO){
		setFrequency(&currentWave2, values.FreqKnob); //prevent changing of values in echo
		setAmplitude(&currentWave2, values.AmpKnob);
		}else if(currentWave2.wave == ECHO){
			channelToChange = 1; //ensure that both ch1 and ch2 get enqueued
			setFrequency(&currentWave1, values.FreqKnob); //allow the changing of ch1 in echo (even if ch2 is selected)
			setAmplitude(&currentWave1, values.AmpKnob);
		}
	}

	//handle enqueuing to the output / dac driver
	bool enqueued1 = true;
	bool enqueued2 = true;
	if(currentWave2.wave == ECHO) {
		echoMode(&values);
	}
	if(channelToChange == 1){
		enqueued1 = SignalQueueInstance1->enqueue(currentWave1);
		if(currentWave2.wave == ECHO){
			enqueued2 = SignalQueueInstance2->enqueue(currentWave2Echo);
		}
	}else if(channelToChange == 2){
		if(currentWave2.wave != ECHO){
			enqueued2 = SignalQueueInstance2->enqueue(currentWave2);
		}else{
			enqueued2 = SignalQueueInstance2->enqueue(currentWave2Echo);
		}
	}
	if((!enqueued1) || (!enqueued2)){
		return; //queues are full, do not reset
	}
}

//Semaphore Class
bool Semaphore::enqueue(bool msg) {
	if(msg != true && msg !=false){
		return false;
	}
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
	if(msg==nullptr){
		return false;
	}
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
	if(position == nullptr){
		return;
	}
    //if it is at the max value go back to 0
    if((*position) >= QUEUE_BUFFER_SIZE-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position+=1;
    }
}




