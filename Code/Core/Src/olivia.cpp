/*
 * olivia.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */
#include "allIncludes.h"

//Waves Class (Application Class 1)
Waves::Waves(inputQueue *InputQueue, signalQueue *SignalQueue){}

Waves::~Waves(){}

void Waves::setSine(){}

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



