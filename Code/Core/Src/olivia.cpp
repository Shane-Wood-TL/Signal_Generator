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

void Waves::setSine()
{
	std::vector<double> wave;
	uint32_t sampleRate = 200;
	wave.clear();  // Clear previous data
	for (uint32_t i = 0; i < sampleRate; i++)
	{
		// Calculate the angle in radians
	    double angle = 2 * M_PI * frequency * static_cast<double>(i) / sampleRate;
	    // Calculate the sine value and scale by amplitude
	    double sample = (amplitude * std::sin(angle));
	    wave.push_back(sample);  // Store the sample in the vector
	 }
}

void Waves::setSquare(){}

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



