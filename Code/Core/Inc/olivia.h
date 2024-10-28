/*
 * olivia.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Olivia Cunningham
 */

#ifndef INC_OLIVIA_H_
#define INC_OLIVIA_H_
#include "main.h"

class Waves
{
	public:
		Waves(inputQueue *InputQueue, signalQueue *SignalQueue1, signalQueue *SignalQueue2);
		~Waves();
    	void setSine();
    	void setSquare();
    	void setPulse();
    	void setAmplitude();
    	void setFrequency();
    	void setDelay();
    	void update();

	private:
    	inputQueue *InputQueueInstance;
    	signalQueue *SignalQueueInstance1;
    	signalQueue *SignalQueueInstance2;
    	int8_t frequency1 = 0;
    	int8_t amplitude1 = 0;
    	int8_t frequency2 = 0;
    	int8_t amplitude2 = 0;
    	uint16_t ampValue1 = 0;
    	uint16_t ampValue2 = 0;
       	uint16_t freqValue1 = 0;
       	uint16_t freqValue2 = 0;
       	uint16_t delayValue = 0;
    	int8_t channelSelect;//switch
    	uint32_t waveValues1[waveFormRes] = {};
    	uint32_t waveValues2[waveFormRes] = {};
    	bool waveSelect;//button
    	int8_t delay = 0;
    	enum WaveShape waveType1;
    	enum WaveShape waveType2;
};


class Semaphore{
	bool buffer[1]; //the buffer of messages
    uint8_t head = 0; //the head of the active queue region
    uint8_t tail = 0; //the tail of the active queue region
    uint32_t activeValues = 0; //the amount of active values

public:
    Semaphore(); //constructor
    bool enqueue(bool msg); //add values
    bool dequeue(bool* msg); //remove values
    void rollingMath(uint8_t *position); //does the math to handle rollovers
};

#endif /* INC_OLIVIA_H_ */
