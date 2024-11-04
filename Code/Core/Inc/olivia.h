/*
 * olivia.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Olivia Cunningham
 */

#ifndef INC_OLIVIA_H_
#define INC_OLIVIA_H_
#include "main.h"

//circular queue that can fill up to its total length
class signalShifter{
	public:
    	signalShifter();
    	void shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint8_t shiftAmt);
	private:
    	uint32_t buffer[waveFormRes]; //the buffer of messages
    	uint8_t head = 0;
    	uint8_t tail = 0;
    	bool full = false;
    	void rollingMath(uint8_t *position); //does the math to handle rollovers
    	bool enqueue(uint32_t msg);
    	bool dequeue(uint32_t* msg);
};

class Waves{
public:
	Waves();
	signalInfo getSinePlot();
	signalInfo getSquarePlot();
	signalInfo getPulsePlot();
	signalInfo getDelay(signalInfo toShift, uint8_t amount);
	void scale(signalInfo *toScale, uint16_t newAmp);
private:
	signalInfo sinePlot;
	signalInfo squarePlot;
	signalInfo pulsePlot;
	void setSine();
	void setSquare();
	void setPulse();
	uint16_t sineWaveTable[waveFormRes] = {2047, 2097, 2147, 2198, 2248, 2298, 2348, 2398, 2447, 2497, 2546, 2595, 2643, 2691, 2739, 2786, 2833, 2879, 2925, 2970, 3015, 3059, 3103, 3145, 3188, 3229, 3270, 3310, 3349, 3388, 3426, 3462, 3498, 3534, 3568, 3601, 3633, 3665, 3695, 3725, 3753, 3780, 3807, 3832, 3856, 3879, 3901, 3922, 3941, 3960, 3977, 3993, 4008, 4022, 4035, 4046, 4056, 4065, 4073, 4079, 4085, 4089, 4092, 4093, 4093, 4093, 4090, 4087, 4082, 4076, 4069, 4061, 4051, 4041, 4029, 4015, 4001, 3985, 3969, 3951, 3932, 3911, 3890, 3868, 3844, 3819, 3793, 3767, 3739, 3710, 3680, 3649, 3617, 3584, 3551, 3516, 3481, 3444, 3407, 3369, 3330, 3290, 3250, 3209, 3167, 3124, 3081, 3037, 2993, 2948, 2902, 2856, 2809, 2762, 2715, 2667, 2619, 2570, 2521, 2472, 2423, 2373, 2323, 2273, 2223, 2173, 2122, 2072, 2021, 1971, 1920, 1870, 1820, 1770, 1720, 1670, 1621, 1572, 1523, 1474, 1426, 1378, 1331, 1284, 1237, 1191, 1145, 1100, 1056, 1012, 969, 926, 884, 843, 803, 763, 724, 686, 649, 612, 577, 542, 509, 476, 444, 413, 383, 354, 326, 300, 274, 249, 225, 203, 182, 161, 142, 124, 108, 92, 78, 64, 52, 42, 32, 24, 17, 11, 6, 3, 0, 0, 0, 1, 4, 8, 14, 20, 28, 37, 47, 58, 71, 85, 100, 116, 133, 152, 171, 192, 214, 237, 261, 286, 313, 340, 368, 398, 428, 460, 492, 525, 559, 595, 631, 667, 705, 744, 783, 823, 864, 905, 948, 990, 1034, 1078, 1123, 1168, 1214, 1260, 1307, 1354, 1402, 1450, 1498, 1547, 1596, 1646, 1695, 1745, 1795, 1845, 1895, 1946, 1996};
	uint16_t squareWaveTable[waveFormRes] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint16_t pulseWaveTable[waveFormRes]=	{4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

class applicationLayer{
	public:
		applicationLayer(inputQueue *InputQueue, signalQueue *SignalQueue1, signalQueue *SignalQueue2);
    	void update();
	private:
    	inputQueue *InputQueueInstance;
    	signalQueue *SignalQueueInstance1;
    	signalQueue *SignalQueueInstance2;
    	Waves waveGen;
    	signalInfo currentWave1;
    	signalInfo currentWave2; //wave data that is not lost in echo mode
    	signalInfo currentWave2Echo; //wave data for echo mode
    	uint8_t channelToChange = 1;
    	void checkFreq(uint16_t *freq,int8_t incAmt);
    	void checkAmp(uint16_t *amp,int8_t incAmt);
    	void checkDelay(uint8_t *shift,int8_t incAmt);
    	void increaseWaveType(WaveShape *currentWave);
    	void setFrequency(signalInfo *signal, int8_t knobValue);
    	void setAmplitude(signalInfo *signal, int8_t knobValue);
    	void updateWave(signalInfo *signal);
    	void echoMode(inputValues *currentInput);
};

class Semaphore{
	bool buffer[1]; //the buffer of messages
    uint8_t head = 0; //the head of the active queue region
    uint8_t tail = 0; //the tail of the active queue region
    uint32_t activeValues = 0; //the amount of active values

public:
    bool enqueue(bool msg); //add values
    bool dequeue(bool* msg); //remove values
    void rollingMath(uint8_t *position); //does the math to handle rollovers
};

#endif /* INC_OLIVIA_H_ */
