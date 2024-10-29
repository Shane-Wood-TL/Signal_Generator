/*
 * memoryBarrier.h
 *
 *  Created on: Sep 15, 2024
 *      Author: Shane Wood
 */

#ifndef SRC_MEMORYBARRIER_H_
#define SRC_MEMORYBARRIER_H_

#define memoryBarrierSize 32

class memoryChecker{
    private:
        uint32_t *memoryBarrier;

    public:
    memoryChecker(uint32_t *memoryBarrierI);
    void checkMemory();

};



#endif /* SRC_MEMORYBARRIER_H_ */
