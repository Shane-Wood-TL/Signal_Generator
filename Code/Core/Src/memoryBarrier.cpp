/*
 * memoryBarrir.cpp
 *
 *  Created on: Sep 15, 2024
 *      Author: Shane Wood
 */


#include "allIncludes.h"


memoryChecker::memoryChecker(uint32_t *memoryBarrierI){
    memoryBarrier = memoryBarrierI;
};

void memoryChecker::checkMemory(){
    bool memorySafe = true;
        for(uint16_t i = 0; i<memoryBarrierSize;i+=4){
              if(memoryBarrier[i]!= 1){
                 memorySafe = false;
                 break;
              }
              if(memoryBarrier[i+1]!= 11){
                 memorySafe = false;
                 break;
              }
              if(memoryBarrier[i+2]!= 111){
                 memorySafe = false;
                 break;
              }
              if(memoryBarrier[i+3]!= 1111){
                 memorySafe = false;
                 break;
              }
       }
       if(memorySafe == false){
            	NVIC_SystemReset();
      }
};
