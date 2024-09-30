/*
 * olivia.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */
#include "olivia.h"

//Waves Class (Application Class 1)
Waves::Waves(){}

Waves::~Waves(){}

void Waves::setChannel(WaveShape shape, uint32_t freq, uint32_t amp, bool followerMode, uint32_t delay){}

uint32_t Waves::setDelay(uint8_t k)
{
	return delay;
}

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



