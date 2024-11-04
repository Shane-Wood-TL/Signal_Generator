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
	uint8_t head = 0; //the head of the active queue region
	uint8_t tail = 0; //the tail of the active queue region
	bool full = false;
    void rollingMath(uint8_t *position); //does the math to handle rollovers
	bool enqueue(uint32_t msg); //add values
	bool dequeue(uint32_t* msg); //remove values
public:
    signalShifter(); //constructor
	void shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint8_t shiftAmt);
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
	assert(msg >=0 && msg <= 4095);
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
void signalShifter::rollingMath(uint8_t *position){
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
void signalShifter::shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint8_t shiftAmt){
	assert(currentPositions != nullptr);
	assert(newPositions != nullptr);
	assert(shiftAmt >= 0);
	//enqueue the entire waveform
    for(uint8_t i = 0; i < waveFormRes; i++) {
    	bool enqueueS = enqueue(currentPositions[i]);
    	if(!enqueueS){
    		return;
    	}
    }

    // Perform the shift by dequeuing and enqueuing the required number of times
    for(uint16_t i = 0; i < 255-shiftAmt; i++) {
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
    for(uint8_t i = 0; i  < waveFormRes; i++) {
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
	//uint16_t sineWaveTable[waveFormRes] = {2047, 2097, 2147, 2198, 2248, 2298, 2348, 2398, 2447, 2497, 2546, 2595, 2643, 2691, 2739, 2786, 2833, 2879, 2925, 2970, 3015, 3059, 3103, 3145, 3188, 3229, 3270, 3310, 3349, 3388, 3426, 3462, 3498, 3534, 3568, 3601, 3633, 3665, 3695, 3725, 3753, 3780, 3807, 3832, 3856, 3879, 3901, 3922, 3941, 3960, 3977, 3993, 4008, 4022, 4035, 4046, 4056, 4065, 4073, 4079, 4085, 4089, 4092, 4093, 4093, 4093, 4090, 4087, 4082, 4076, 4069, 4061, 4051, 4041, 4029, 4015, 4001, 3985, 3969, 3951, 3932, 3911, 3890, 3868, 3844, 3819, 3793, 3767, 3739, 3710, 3680, 3649, 3617, 3584, 3551, 3516, 3481, 3444, 3407, 3369, 3330, 3290, 3250, 3209, 3167, 3124, 3081, 3037, 2993, 2948, 2902, 2856, 2809, 2762, 2715, 2667, 2619, 2570, 2521, 2472, 2423, 2373, 2323, 2273, 2223, 2173, 2122, 2072, 2021, 1971, 1920, 1870, 1820, 1770, 1720, 1670, 1621, 1572, 1523, 1474, 1426, 1378, 1331, 1284, 1237, 1191, 1145, 1100, 1056, 1012, 969, 926, 884, 843, 803, 763, 724, 686, 649, 612, 577, 542, 509, 476, 444, 413, 383, 354, 326, 300, 274, 249, 225, 203, 182, 161, 142, 124, 108, 92, 78, 64, 52, 42, 32, 24, 17, 11, 6, 3, 0, 0, 0, 1, 4, 8, 14, 20, 28, 37, 47, 58, 71, 85, 100, 116, 133, 152, 171, 192, 214, 237, 261, 286, 313, 340, 368, 398, 428, 460, 492, 525, 559, 595, 631, 667, 705, 744, 783, 823, 864, 905, 948, 990, 1034, 1078, 1123, 1168, 1214, 1260, 1307, 1354, 1402, 1450, 1498, 1547, 1596, 1646, 1695, 1745, 1795, 1845, 1895, 1946, 1996};
	uint16_t sineWaveTable[waveFormRes]= {2047, 2096, 2145, 2194, 2242, 2291, 2339, 2388, 2436, 2484, 2531, 2579, 2626, 2672, 2718, 2764, 2810, 2855, 2899, 2943, 2986, 3029, 3071, 3113, 3154, 3194, 3234, 3273, 3311, 3348, 3385, 3420, 3455, 3489, 3523, 3555, 3586, 3617, 3646, 3675, 3702, 3729, 3754, 3779, 3802, 3824, 3846, 3866, 3885, 3903, 3920, 3935, 3950, 3963, 3975, 3987, 3996, 4005, 4013, 4019, 4024, 4028, 4031, 4032, 4032, 4032, 4029, 4026, 4022, 4016, 4009, 4001, 3992, 3981, 3970, 3957, 3943, 3928, 3911, 3894, 3875, 3856, 3835, 3813, 3790, 3766, 3742, 3716, 3688, 3660, 3631, 3602, 3571, 3539, 3506, 3472, 3438, 3403, 3366, 3329, 3292, 3253, 3214, 3174, 3134, 3092, 3050, 3008, 2965, 2921, 2877, 2832, 2787, 2741, 2695, 2649, 2602, 2555, 2508, 2460, 2412, 2364, 2315, 2267, 2218, 2169, 2120, 2071, 2023, 1974, 1925, 1876, 1827, 1779, 1730, 1682, 1634, 1586, 1539, 1492, 1445, 1399, 1353, 1307, 1262, 1217, 1173, 1129, 1086, 1044, 1002, 960, 920, 880, 841, 802, 765, 728, 691, 656, 622, 588, 555, 523, 492, 463, 434, 406, 378, 352, 328, 304, 281, 259, 238, 219, 200, 183, 166, 151, 137, 124, 113, 102, 93, 85, 78, 72, 68, 65, 62, 62, 62, 63, 66, 70, 75, 81, 89, 98, 107, 119, 131, 144, 159, 174, 191, 209, 228, 248, 270, 292, 315, 340, 365, 392, 419, 448, 477, 508, 539, 571, 605, 639, 674, 709, 746, 783, 821, 860, 900, 940, 981, 1023, 1065, 1108, 1151, 1195, 1239, 1284, 1330, 1376, 1422, 1468, 1515, 1563, 1610, 1658, 1706, 1755, 1803, 1852, 1900, 1949, 1998};
	uint16_t squareWaveTable[waveFormRes] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint16_t pulseWaveTable[waveFormRes]=	{4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
public:
	baseWaves();
	signalInfo getSinePlot();
	signalInfo getSquarePlot();
	signalInfo getPulsePlot();

	signalInfo shift(signalInfo toShift, uint8_t amount);
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
	for (uint8_t i =0; i < waveFormRes; i++){
		//copy the table into the struct
		sinePlot.signalLocations[i] = sineWaveTable[i];
	}
}




void baseWaves::generateSquarePlot(){
	squarePlot.amp = 4095;
	squarePlot.frequency = 100;
	squarePlot.shiftAmount = 0;
	squarePlot.wave = SQUARE;
	for (uint8_t i =0; i < waveFormRes; i++){
			squarePlot.signalLocations[i] = squareWaveTable[i];
	}
}

void baseWaves::generatePulsePlot(){
	pulsePlot.amp = 4095;
	pulsePlot.frequency = 100;
	pulsePlot.shiftAmount = 0;
	pulsePlot.wave = PULSE;
	for (uint8_t i =0; i < waveFormRes; i++){
			pulsePlot.signalLocations[i] = pulseWaveTable[i];
		}
}




signalInfo baseWaves::getSquarePlot(){
	return squarePlot;
}

signalInfo baseWaves::getPulsePlot(){
	return pulsePlot;
}

signalInfo baseWaves::shift(signalInfo toShift, uint8_t amount){
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
	signalInfo tempWave;
	if(toScale->wave == SINE){
		tempWave = getSinePlot();
	}else if(toScale->wave == SQUARE){
		tempWave = getSquarePlot();
	}else{
		tempWave = getPulsePlot();
	}

	for(uint8_t i = 0; i < waveFormRes; i++){
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
	void checkShift(uint8_t *shift,int8_t incAmt);
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
void applicationLayer::checkShift(uint8_t *shift, int8_t incAmt){
	assert(shift != nullptr);
	assert(incAmt != 0);
	uint8_t newShift = (*shift)+ incAmt;
	if (incAmt > 0){
		if(newShift < *shift || newShift > 255){
			*shift = 255;
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
		    			    for(uint8_t i = 0; i < waveFormRes; i++) {
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
		if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE)){// != RESET) {
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


	//start spi + setup display
	display mainDisplay(&hspi3, &displayQueueInstance,dcPort,dcPin,rstPort,rstPin);
	//draw freq + amp to the display
	mainDisplay.getNewValues();

	//simple memory barrier to catch memory issues (indexing past where another objects were allocated to)
	uint32_t memoryBarrier[32] = {1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111, 1,11,111,1111,1,11,111,1111};
	memoryChecker largerMemoryChecker(memoryBarrier,32);

	overallMemoryChecker overallMemoryCheckerInstance(&miniMemBarrierA, &miniMemBarrierB, &miniMemBarrierC, &miniMemBarrierD, &largerMemoryChecker, &memoryCheckerSemaphore);
	while(1){
		//TOGGLE
		input.checkForUpdates(); //updates all input, needs semaphores
		mainHandler.update();
		outputDriverI.update();
		//WRITEON
		mainDisplay.getNewValues();
		//WRITEOFF


		//WRITEON

		//WRITEOFF
		overallMemoryCheckerInstance.checkMemory();


	}
}
