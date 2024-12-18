/*
 * memoryBarrir.cpp
 *
 *  Created on: Sep 15, 2024
 *      Author: Shane Wood
 */


#include "allIncludes.h"


memoryChecker::memoryChecker(uint32_t *memoryBarrierI, uint8_t barrierSizeV){
	if((memoryBarrierI == nullptr) || (barrierSizeV <= 0)){
		NVIC_SystemReset();
	}
	assert(memoryBarrierI != nullptr);
	assert(barrierSizeV > 0);
    memoryBarrier = memoryBarrierI;
    barrierSize = barrierSizeV;
	assert((barrierSize % 4) == 0);
};

void memoryChecker::checkMemory(){
    bool memorySafe = true;
        for(uint16_t i = 0; i<barrierSize;i+=4){ //check 0, 4, 8,...
              if(memoryBarrier[i]!= 1){//check 0,4,8...
                 memorySafe = false;
                 break;
              }
              if(memoryBarrier[i+1]!= 11){//check 1,5,9...
                 memorySafe = false;
                 break;
              }
              if(memoryBarrier[i+2]!= 111){ //check 2,6,10,...
                 memorySafe = false;
                 break;
              }
              if(memoryBarrier[i+3]!= 1111){//check 3,7,11,...
                 memorySafe = false;
                 break;
              }
       }
       if(memorySafe == false){
            	NVIC_SystemReset();
      }
};


overallMemoryChecker::overallMemoryChecker(memoryChecker *smallBarrierAI,memoryChecker *smallBarrierBI,memoryChecker *smallBarrierCI,memoryChecker *smallBarrierDI,memoryChecker *largeBarrierI, Semaphore *memorySemaphoreI){
	if((smallBarrierAI == nullptr) || (smallBarrierBI == nullptr) || (smallBarrierCI == nullptr) ||
			(smallBarrierDI == nullptr) || (largeBarrierI == nullptr) || (memorySemaphoreI == nullptr)){
		NVIC_SystemReset();
	}
	assert((smallBarrierAI != nullptr) && (smallBarrierBI != nullptr) && (smallBarrierCI != nullptr)
			&& (smallBarrierDI != nullptr) && (largeBarrierI != nullptr) && (memorySemaphoreI != nullptr));
	smallBarrierA = smallBarrierAI;
	smallBarrierB = smallBarrierBI;
	smallBarrierC = smallBarrierCI;
	smallBarrierD = smallBarrierDI;
	largeBarrier = largeBarrierI;
	memorySemaphore = memorySemaphoreI;
}

void overallMemoryChecker::checkMemory(){
	//check each barrier one at a time
	static uint8_t state;
	bool msg = false;
	bool semaphoreState = memorySemaphore->dequeue(&msg);
	if((semaphoreState && msg)){
		switch(state){
		case(0):{
			smallBarrierA->checkMemory();
			state=1;
			break;
		}
		case(1):{
			smallBarrierB->checkMemory();
			state=2;
			break;
		}
		case(2):{
			smallBarrierC->checkMemory();
			state = 3;
			break;
		}
		case(3):{
			smallBarrierA->checkMemory();
			state = 4;
			break;
		}
		case(4):{
			largeBarrier->checkMemory();
			state = 0;
			break;
		}
		default:{
			state = 0;
			break;
		}
		}
	}
}
