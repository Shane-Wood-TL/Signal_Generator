/**
 * @file memoryBarrier.h
 * @brief This file contains the definition of the memoryChecker and overallMemoryChecker classes
 * @author Shane Wood
 * @date Sep 15, 2024
 */

#ifndef SRC_MEMORYBARRIER_H_
#define SRC_MEMORYBARRIER_H_

#include "allIncludes.h"
/**
 * @class memeoryChecker
 * @brief Memory checker based on repeating list
 * 
 * @details Checks for 1,11,111,1111 in a list repeating for as long as barrierSize, barrierSize needs to be divisible by 4
 */
class memoryChecker{
    private:
        uint32_t *memoryBarrier; ///< Memory barrier list
        uint8_t barrierSize; ///< The length of the barrier

    public:
    /**
     * @brief Constructs a memoryBarrier object
     * 
     * @param memoryBarrierI A uint32_t containing the repeating numbers as a list.
     * @param barrierSizeV A uint8_t specifying the length of memoryBarrierI.
     */
    memoryChecker(uint32_t *memoryBarrierI, uint8_t barrierSizeV);

    /**
     * @brief Check memoryBarrier to ensure the pattern is still true
     * 
     * @note If the barrier is no longer repeating as expected; it will issue a NVIC reboot.
     */
    void checkMemory();

};
/**
 * @class overallMemoryChecker
 * @brief Class that holds all memory barriers
 */
class overallMemoryChecker{
private:
	memoryChecker *smallBarrierA; ///<first small barrier
	memoryChecker *smallBarrierB;///<second small barrier
	memoryChecker *smallBarrierC;///<third small barrier
	memoryChecker *smallBarrierD;///<fourth small barrier
	memoryChecker *largeBarrier;///<large barrier
	Semaphore *memorySemaphore; ///<semaphore letting the barrier know when to run
public:
	/**
	 * @brief Constructor for the overall memory barrier
	 *
	 * @param smallBarrierAI a memorychecker instance
	 * @param smallBarrierBI a memorychecker instance
	 * @param smallBarrierCI a memorychecker instance
	 * @param smallBarrierDI a memorychecker instance
	 * @param largerBarrierI a memorychecker instance
	 * @param memorySemaphoreI a semaphore instance
	 */
	overallMemoryChecker(memoryChecker *smallBarrierAI,memoryChecker *smallBarrierBI,memoryChecker *smallBarrierCI,memoryChecker *smallBarrierDI,memoryChecker *largeBarrierI, Semaphore *memorySemaphoreI);


	/**
	 * @brief Update check one of the memory barriers
	 *
	 * @details Cycles through one of the memory barriers if the semaphore is set,
	 *  will cycle through the next barrier during the next time the semaphore is set.
	 */
	void checkMemory();
};


#endif /* SRC_MEMORYBARRIER_H_ */
