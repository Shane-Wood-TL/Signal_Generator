/*
 * mainCpp.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */
#include "allIncludes.h"

//circular queue that can fill up to its total length
class signalShifter{
	uint32_t buffer[waveFormRes]; //the buffer of messages
	uint16_t head = 0; //the head of the active queue region
	uint16_t tail = 0; //the tail of the active queue region
	bool full = false;
    void rollingMath(uint16_t *position); //does the math to handle rollovers
	bool enqueue(uint32_t msg); //add values
	bool dequeue(uint32_t* msg); //remove values
public:
    signalShifter(); //constructor
	void shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint16_t shiftAmt);
};

//set the head and tail to 0
signalShifter::signalShifter() {
	//set all values to 0
	head = 0;
	tail = 0;
	static_assert(waveFormRes > 0);
}

//enqueue a point
bool signalShifter::enqueue(uint32_t msg) {
	if(full){
		return false;
	}else{
		buffer[tail] = msg; //put the message in the buffer
		rollingMath(&tail);

		if(tail==head){
			full = true;
		}
		return true;
	}
}

//dequeue a point
bool signalShifter::dequeue(uint32_t *msg) {
	assert(msg != nullptr);
	if(full == false && head == tail){
		return false;
	}else{
		*msg = buffer[head]; //get the value at the head
		rollingMath(&head); //increase head by 1, to get next head
		full = false;
		return true;
	}
}

//use circular queue, to shift indecies
void signalShifter::rollingMath(uint16_t *position){
	assert(position != nullptr);
	assert(!(*position > waveFormRes));
    //if it is at the max value go back to 0
    if((*position) >= waveFormRes-1){ //fail safe it position somehow gets larger
        *position = 0;
    }else{
        //if not at max increase like normal
        *position+=1;
    }
}

//overall shifter
void signalShifter::shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint16_t shiftAmt){
	assert(currentPositions != nullptr);
	assert(newPositions != nullptr);
	assert(shiftAmt >= 0);
	//enqueue the entire waveform
    for(uint16_t i = 0; i < waveFormRes; i++) {
    	bool enqueueS = enqueue(currentPositions[i]);
    	if(!enqueueS){
    		return;
    	}
    }

    // Perform the shift by dequeuing and enqueuing the required number of times
    for(uint16_t i = 0; i < 256-shiftAmt; i++) {
        uint32_t temp;
        bool dequeueS;
        bool enququeS;
        dequeueS =dequeue(&temp);  // Remove the front element
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

class baseWaves{
	signalInfo sinePlot;
	signalInfo squarePlot;
	signalInfo pulsePlot;
	void generateSinePlot();
	void generateSquarePlot();
	void generatePulsePlot();
	uint16_t sineWaveTable[waveFormRes]=    {2047, 2095, 2144, 2193, 2241, 2289, 2338, 2386, 2434, 2481, 2529, 2576, 2623, 2669, 2715, 2761, 2806, 2851, 2895, 2939, 2982, 3025, 3067, 3108, 3149, 3189, 3229, 3268, 3306, 3343, 3380, 3415, 3450, 3484, 3517, 3550, 3581, 3611, 3641, 3669, 3697, 3724, 3749, 3774, 3797, 3820, 3841, 3861, 3880, 3898, 3915, 3931, 3946, 3960, 3972, 3983, 3993, 4002, 4010, 4017, 4022, 4026, 4029, 4031, 4032, 4031, 4029, 4026, 4022, 4017, 4010, 4002, 3993, 3983, 3972, 3960, 3946, 3931, 3915, 3898, 3880, 3861, 3841, 3820, 3797, 3774, 3749, 3724, 3697, 3669, 3641, 3611, 3581, 3550, 3517, 3484, 3450, 3415, 3380, 3343, 3306, 3268, 3229, 3189, 3149, 3108, 3067, 3025, 2982, 2939, 2895, 2851, 2806, 2761, 2715, 2669, 2623, 2576, 2529, 2481, 2434, 2386, 2338, 2289, 2241, 2193, 2144, 2095, 2046, 1998, 1949, 1900, 1852, 1804, 1755, 1707, 1659, 1612, 1564, 1517, 1470, 1424, 1378, 1332, 1287, 1242, 1198, 1154, 1111, 1068, 1026, 985, 944, 904, 864, 825, 787, 750, 713, 678, 643, 609, 576, 543, 512, 482, 452, 424, 396, 369, 344, 319, 296, 273, 252, 232, 213, 195, 178, 162, 147, 133, 121, 110, 100, 91, 83, 76, 71, 67, 64, 62, 62, 62, 64, 67, 71, 76, 83, 91, 100, 110, 121, 133, 147, 162, 178, 195, 213, 232, 252, 273, 296, 319, 344, 369, 396, 424, 452, 482, 512, 543, 576, 609, 643, 678, 713, 750, 787, 825, 864, 904, 944, 985, 1026, 1068, 1111, 1154, 1198, 1242, 1287, 1332, 1378, 1424, 1470, 1517, 1564, 1612, 1659, 1707, 1755, 1804, 1852, 1900, 1949, 1998};
	uint16_t squareWaveTable[waveFormRes] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint16_t pulseWaveTable[waveFormRes]=	{4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
public:
	baseWaves();
	signalInfo getSinePlot();
	signalInfo getSquarePlot();
	signalInfo getPulsePlot();

	signalInfo shift(signalInfo toShift, uint16_t amount);
	void scale(signalInfo *toScale, uint16_t newAmp);

};

signalInfo baseWaves::getSinePlot(){
	return sinePlot;
}

baseWaves::baseWaves(){
	generateSinePlot();
	generateSquarePlot();
	generatePulsePlot();
};

void baseWaves::generateSinePlot(){
	sinePlot.amp = 3971;
	sinePlot.frequency = 100;
	sinePlot.shiftAmount = 0;
	sinePlot.wave = SINE;
	for (uint16_t i =0; i < waveFormRes; i++){
		//copy the table into the struct
		sinePlot.signalLocations[i] = sineWaveTable[i];
	}
}




void baseWaves::generateSquarePlot(){
	squarePlot.amp = 4095;
	squarePlot.frequency = 100;
	squarePlot.shiftAmount = 0;
	squarePlot.wave = SQUARE;
	for (uint16_t i =0; i < waveFormRes; i++){
			squarePlot.signalLocations[i] = squareWaveTable[i];
	}
}

void baseWaves::generatePulsePlot(){
	pulsePlot.amp = 4095;
	pulsePlot.frequency = 100;
	pulsePlot.shiftAmount = 0;
	pulsePlot.wave = PULSE;
	for (uint16_t i =0; i < waveFormRes; i++){
			pulsePlot.signalLocations[i] = pulseWaveTable[i];
		}
}




signalInfo baseWaves::getSquarePlot(){
	return squarePlot;
}

signalInfo baseWaves::getPulsePlot(){
	return pulsePlot;
}

signalInfo baseWaves::shift(signalInfo toShift, uint16_t amount){
	signalInfo modifiedWave;
	modifiedWave.shiftAmount = amount;
	//handle the shifting
	signalShifter shifter;
	shifter.shiftWaveform(toShift.signalLocations, modifiedWave.signalLocations, amount);
	modifiedWave.wave=ECHO; //force new wave to echo
	return modifiedWave;
}

void baseWaves::scale(signalInfo *toScale, uint16_t newAmp){
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




class applicationLayer{
	inputQueue *inputQueueI;
	signalQueue *channel1I;
	signalQueue *channel2I;
	baseWaves waveGen;
	signalInfo currentWave1;
	signalInfo currentWave2; //wave data that is not lost in echo mode
	signalInfo currentWave2Echo; //wave data for echo mode
	uint8_t channelToChange = 1;
	void checkFreq(uint16_t *freq,int8_t incAmt);
	void checkAmp(uint16_t *amp,int8_t incAmt);
	void checkShift(uint16_t *shift,int8_t incAmt);
	void increaseWaveType(WaveShape *currentWave);
	void updateFreq(signalInfo *signal, int8_t knobValue);
	void updateAmp(signalInfo *signal, int8_t knobValue);
	void updateWave(signalInfo *signal);
	void echoMode(inputValues *currentInput);
public:
	applicationLayer(inputQueue *inputQueue,signalQueue *channel1, signalQueue *channel2);
	void update();
};

//safely increase / decrease the frequency
void applicationLayer::checkFreq(uint16_t *freq, int8_t incAmt){
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
	assert(amp != nullptr);
	assert(incAmt != 0);
	uint16_t newAmp = (*amp)+ incAmt;
	    if (incAmt > 0){
	        if(newAmp < *amp || newAmp>4095){
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
void applicationLayer::checkShift(uint16_t *shift, int8_t incAmt){
	assert(shift != nullptr);
	assert(incAmt != 0);
	uint16_t newShift = (*shift)+ incAmt;
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

//contstructor ....
applicationLayer::applicationLayer(inputQueue *inputQueue,signalQueue *channel1, signalQueue *channel2){
	assert(inputQueue != nullptr);
	assert(channel1 != nullptr);
	assert(channel2 != nullptr);
	inputQueueI = inputQueue;
	channel1I = channel1;
	channel2I = channel2;

	currentWave1=waveGen.getSinePlot();
	currentWave2=waveGen.getSinePlot();
	channel1->enqueue(currentWave1);
	channel2->enqueue(currentWave2);
}

//go to the next wave type
void applicationLayer::increaseWaveType(WaveShape *currentWave){
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
void applicationLayer::updateFreq(signalInfo *signal, int8_t knobValue){
	assert(signal != nullptr);

	int8_t amtToChangeBy=0;
	if(knobValue==0){
			return;
	}else if(knobValue == 1){ //use stepped increments; 0,1,2,3,...10,20,30,....,100,200,300
		if(signal->frequency < 10){
			amtToChangeBy = 1;
		}else if(signal->frequency < 100){
			amtToChangeBy= 10;
		}else{
			amtToChangeBy= 100;
		}
	}else if (knobValue == -1){
				if(signal->frequency > 100){
					amtToChangeBy= -100;
				}else if(signal->frequency > 10){
					amtToChangeBy= -10;
				}else{
					amtToChangeBy= -1;
				}
			}
	checkFreq(&signal->frequency, amtToChangeBy); //ensure that freq stays a legal value
}

//update amp based on the knob
void applicationLayer::updateAmp(signalInfo *signal, int8_t knobValue){
	assert(signal != nullptr);
	if(knobValue==0){
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
	assert(currentInput != nullptr);
	if(currentInput->DelayKnob == 1) {//increase delay by 45 deg
		        checkShift(&currentWave2Echo.shiftAmount, 32);
		    } else if(currentInput->DelayKnob == -1) {
		        checkShift(&currentWave2Echo.shiftAmount, -32);
		    }

		    if(currentWave2Echo.shiftAmount != 0) {
		    	currentWave2Echo = waveGen.shift(currentWave1, currentWave2Echo.shiftAmount); //if there is shifting to be done; do it
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
	static inputValues currentInput;
	//see if there is data + know what switch to use
		if(inputQueueI->dequeue(&currentInput)){
			if(currentInput.Switch == 0){
					channelToChange= 1;
				}else{
					channelToChange = 2;
				}
		}
		//	//only change info for frequency, not the table
			if(channelToChange == 1){
				if(currentInput.isButtonPressed){
					updateWave(&currentWave1);
				}
				updateFreq(&currentWave1, currentInput.FreqKnob);
				updateAmp(&currentWave1, currentInput.AmpKnob);

			}else if(channelToChange == 2){
				if(currentInput.isButtonPressed){
							updateWave(&currentWave2);
				}
				if(currentWave2.wave != ECHO){
				updateFreq(&currentWave2, currentInput.FreqKnob); //prevent changing of values in echo
				updateAmp(&currentWave2, currentInput.AmpKnob);
				}else if(currentWave2.wave == ECHO){
					channelToChange = 1; //ensure that both ch1 and ch2 get enqueued
					updateFreq(&currentWave1, currentInput.FreqKnob); //allow the changing of ch1 in echo (even if ch2 is selected)
					updateAmp(&currentWave1, currentInput.AmpKnob);
				}
			}
		//handle enqueuing to the output / dac driver
		bool enqueued1 = true;
		bool enqueued2 = true;
		if(currentWave2.wave == ECHO) {
			echoMode(&currentInput);
		}
		if(channelToChange==1){
				enqueued1 = channel1I->enqueue(currentWave1);
				if(currentWave2.wave==ECHO)
					{
					enqueued2 = channel2I->enqueue(currentWave2Echo);
					}
			}else if(channelToChange==2){
				if(currentWave2.wave!=ECHO){
					enqueued2 = channel2I->enqueue(currentWave2);
				}else{
					enqueued2 = channel2I->enqueue(currentWave2Echo);
				}

		}
		if((!enqueued1) || (!enqueued2)){
			NVIC_SystemReset(); //queues are full, something is wrong
		}
}

extern "C" void cpp_main(void);
extern SPI_HandleTypeDef hspi3;
extern DAC_HandleTypeDef hdac1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;
static Semaphore button;
static Semaphore knobs;
static Semaphore switches;
static Semaphore memoryCheckerSemaphore;

extern "C" void myTIM7_IRQHandler(void) {
	if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE)){
		if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE)){
			__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE); // Clear the interrupt flag
			button.enqueue(1);
			knobs.enqueue(1);
			switches.enqueue(1);
	    }
	}
}

extern "C" void myTIM16_IRQHandler(void) {
	if(__HAL_TIM_GET_FLAG(&htim16, TIM_FLAG_UPDATE)){
		if(__HAL_TIM_GET_IT_SOURCE(&htim16, TIM_IT_UPDATE)){// != RESET) {
			__HAL_TIM_CLEAR_IT(&htim16, TIM_IT_UPDATE); // Clear the interrupt flag
			memoryCheckerSemaphore.enqueue(1);
	    }
	}
}

void cpp_main(void){
	static_assert(sizeof(uint32_t) ==4);
	static_assert(sizeof(uint16_t) ==2);
	static_assert(sizeof(uint8_t) ==1);
	static_assert(waveFormRes > 0);
	//start the semaphore timer
	htim7.Instance->CR1 |= TIM_CR1_CEN;
	htim16.Instance->CR1 |= TIM_CR1_CEN;

	//set up the queues
	inputQueue inputQueueInstance;
	uint32_t barrierA[8] = {1,11,111,1111,1,11,111,1111};

	memoryChecker miniMemBarrierA(barrierA,8);

	signalQueue channel1;
	uint32_t barrierB[8] = {1,11,111,1111,1,11,111,1111};
	memoryChecker miniMemBarrierB(barrierB,8);

	signalQueue channel2;
	uint32_t barrierC[8] = {1,11,111,1111,1,11,111,1111};
	memoryChecker miniMemBarrierC(barrierC,8);

	displayQueue displayQueueInstance;
	uint32_t barrierD[8] = {1,11,111,1111,1,11,111,1111};
	memoryChecker miniMemBarrierD(barrierD,8);

	applicationLayer mainHandler(&inputQueueInstance, &channel1, &channel2);

	dacDriver DriverCh1(&hdac1,DAC_CHANNEL_1,&htim2,&channel1);
	dacDriver DriverCh2(&hdac1,DAC_CHANNEL_2,&htim6,&channel2);
	outputDriver outputDriverI(&DriverCh1, &DriverCh2, &displayQueueInstance);



	SwitchDriver channel(channelSwitchPort, channelSwitchPin, &switches); //fill nullptr with semaphore switch
	ButtonDriver mode(modeButtonPort, modeButtonPin, &button); //fill nullptr with semaphore button

	KnobDriver freq(freqKnobAPort, freqKnobAPin, freqKnobBPort, freqKnobBPin);
	KnobDriver amp(ampKnobAPort, ampKnobAPin, ampKnobBPort, ampKnobBPin);
	KnobDriver shift(shiftKnobAPort, shiftKnobAPin, shiftKnobBPort, shiftKnobBPin);

	InputDriver input(&amp, &freq, &shift, &channel, &mode, &inputQueueInstance, &knobs); //fill nullptr with semaphore knob

	struct ssd1306Setup displaySetup ={SSD1306VerticalRes,SSD1306HorizontalRes,dcPort,dcPin,rstPort,rstPin};
	//start spi + setup display
	display mainDisplay(&hspi3, &displayQueueInstance,&displaySetup);
	//draw freq + amp to the display
	mainDisplay.getNewValues();

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
	memoryChecker largerMemoryChecker(memoryBarrier,32);

	overallMemoryChecker overallMemoryCheckerInstance(&miniMemBarrierA, &miniMemBarrierB, &miniMemBarrierC, &miniMemBarrierD, &largerMemoryChecker, &memoryCheckerSemaphore);
	while(1){
		TOGGLE
		//WRITEON
		//WRITEOFF
		input.checkForUpdates(); //updates all input, needs semaphores
		mainHandler.update();
		outputDriverI.update();
		//WRITEON
		mainDisplay.getNewValues();
		overallMemoryCheckerInstance.checkMemory();
	}
}
