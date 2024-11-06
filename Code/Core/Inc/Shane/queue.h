/**
 * @file queue.h
 * @brief This file contains the definitions for the signalQueue, displayQueue, and inputQueue
 * @author Shane Wood
 * @date Sep 15, 2024
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_


#include "allIncludes.h"

/**
 * @class signalQueue
 * @brief Queue for the application layer to the dacDrivers
 *
 * @details A FIFO circular queue with size determined by the macro SIGNAL_QUEUE_SIZE
 */
class signalQueue {
	struct signalInfo buffer[SIGNAL_QUEUE_SIZE]; ///< the buffer of messages
	uint8_t head = 0; ///< the head of the active queue region
	uint8_t tail = 0; ///< the tail of the active queue region

	/**
	 * @brief Perform rolling math so the queue is circular
	 * 
	 * @param position A uint8_t that will be changed to be the next position
	 */
    void rollingMath(uint8_t *position);
public:
	/**
	 * @brief constructs a signalQueue object.
	 */
    signalQueue();

	/**
	 * @brief Enqueue a value to the queue
	 * @param msg a signalInfo Instance
	 * @return If the value was successfully enqueued 
	 */
	bool enqueue(struct signalInfo msg);

	/**
	 * @brief Dequeue a value from the queue
	 * @param msg a signalInfo Instance
	 * @return If there was a value to dequeue
	 */
	bool dequeue(struct signalInfo* msg); //remove values
};


/**
 * @class displayQueue
 * @brief Queue for the outputDriver to the display
 *
 * @details A FIFO circular queue with size determined by the macro DISPLAY_QUEUE_SIZE
 */
class displayQueue {
	struct displayInfoValues buffer[DISPLAY_QUEUE_SIZE];///< the buffer of messages
	uint8_t head = 0;///< the head of the active queue region
	uint8_t tail = 0;///< the tail of the active queue region

	/**
	 * @brief Perform rolling math so the queue is circular
	 * 
	 * @param position A uint8_t that will be changed to be the next position
	 */
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
	/**
	 * @brief constructs a displayQueue object.
	 */
    displayQueue(); //constructor

	/**
	 * @brief Enqueue a value to the queue
	 * @param msg a displayInfoValues Instance
	 * @return If the value was successfully enqueued 
	 */
	bool enqueue(struct displayInfoValues msg); //add values

	/**
	 * @brief Dequeue a value from the queue
	 * @param msg a displayInfoValues Instance
	 * @return If there was a value to dequeue
	 */
	bool dequeue(struct displayInfoValues* msg); //remove values
};


/**
 * @class inputQueue
 * @brief Queue for the outputDriver to the display
 *
 * @details A FIFO circular queue with size determined by the macro INPUT_QUEUE_SIZE
 */
class inputQueue {
	struct inputValues buffer[INPUT_QUEUE_SIZE];///< the buffer of messages
	uint8_t head = 0; ///< the head of the active queue region
	uint8_t tail = 0; ///< the tail of the active queue region

	/**
	 * @brief Perform rolling math so the queue is circular
	 * 
	 * @param position A uint8_t that will be changed to be the next position
	 */
    void rollingMath(uint8_t *position); //does the math to handle rollovers
public:
	/**
	 * @brief constructs a inputQueue object.
	 */
    inputQueue(); //constructor

	/**
	 * @brief Enqueue a value to the queue
	 * @param msg a inputValues Instance
	 * @return If the value was successfully enqueued 
	 */
	bool enqueue(struct inputValues msg); //add values

	/**
	 * @brief Dequeue a value from the queue
	 * @param msg a inputValues Instance
	 * @return If there was a value to dequeue
	 */
	bool dequeue(struct inputValues* msg); //remove values
};

#endif /* INC_QUEUE_H_ */
