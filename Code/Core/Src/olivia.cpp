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
Semaphore::Semaphore(){}

Semaphore::~Semaphore(){}

int32_t Semaphore::wait()
{
	return count;
}

int32_t Semaphore::post()
{
	return count;
}



