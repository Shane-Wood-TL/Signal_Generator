/*
 * olivia.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Olivia Cunningham
 */

#ifndef INC_OLIVIA_H_
#define INC_OLIVIA_H_
#include "main.h"

/**
 * @class signalShifter
 * @brief signalShifter creates a circular queue that can fill up to its total length
 */
class signalShifter{
	public:

		/**
		* @brief sets the head and tail to 0
		*/
    	signalShifter();

    	/**
    	* @brief performs the overall shift based on current and new positions and the amount to shift the waveform by
    	*
    	* @param currentPositions an unsigned integer which is a specific value in an array
    	*
    	* @param newPositions an unsigned integer which is a specific value in an array based on a shifted version of the currentPositions array
    	*
    	* @param shiftAmt is an unsigned integer that dictates the amount of values that are removed from the front of the currentPositions array and
    	* moved to the back of the array to create the newPositions array
    	*/
    	void shiftWaveform(uint32_t *currentPositions, uint32_t *newPositions, uint8_t shiftAmt);
	private:
    	uint32_t buffer[waveFormRes];
    	uint8_t head = 0;
    	uint8_t tail = 0;
    	bool full = false;

    	/**
    	* @brief Perform rolling math so the queue is circular
    	*
    	* @param position A unsigned integer that will be changed to be the next position
    	*/
    	void rollingMath(uint8_t *position);

    	/**
    	* @brief Enqueue a value to the queue
    	*
    	* @param msg an unsigned integer in a waveform
    	*
    	* @return If the value was successfully enqueued
    	*/
    	bool enqueue(uint32_t msg);

    	/**
    	* @brief Dequeue a value from the queue
    	*
    	* @param msg an unsigned integer in a waveform
    	*
    	* @return If there was a value to dequeue
    	*/
    	bool dequeue(uint32_t* msg);
};

/**
 * @class Waves
 *
 * @brief Waves creates a base wave for sine, square, and pulse
 */
class Waves{
public:

	/**
	 * @brief Waves generates a sine, square, and pulse plot
	 */
	Waves();

	/**
	* @brief returns the struct of sinePlot so it can be accessed and modified
	*
	* @return a struct signalInfo instance called sinePlot
	*/
	signalInfo getSinePlot();

	/**
	* @brief returns the struct of squarePlot so it can be accessed and modified
	*
	* @return a struct signalInfo instance called squarePlot
	*/
	signalInfo getSquarePlot();

	/**
	* @brief returns the struct of pulsePlot so it can be accessed and modified
	*
	* @return a struct signalInfo instance called pulsePlot
	*/
	signalInfo getPulsePlot();

	/**
	* @brief Shifts the original wave by a certain amount in echo mode
	*
	* @param toShift a struct signalInfo toShift an array of values that is going to be modified
	* @param amount an unsigned integer amount which dictates the amount to shift the toShift wave
	*
	* @return a struct signalInfo instance called modifiedWave based on the toShift wave
	*/
	signalInfo getDelay(signalInfo toShift, uint16_t amount);

	/**
	* @brief makes a new copy of the wave and adjusts the amplitude
	*
	* @param toScale a struct signalInfo toScale an array of values that is going to be modified
	* @param newAmp unsigned integer newAmp
	*/
	void scale(signalInfo *toScale, uint16_t newAmp);
private:
	signalInfo sinePlot;
	signalInfo squarePlot;
	signalInfo pulsePlot;

	/**
	* @brief copies the sineWaveTable into sinePlot struct
	*/
	void setSine();

	/**
	* @brief copies the squareWaveTable into squarePlot struct
	*/
	void setSquare();

	/**
	* @brief copies the pulseWaveTable into pulsePlot struct
	*/
	void setPulse();

	uint16_t sineWaveTable[waveFormRes] = {2047, 2095, 2144, 2193, 2241, 2289, 2338, 2386, 2434, 2481, 2529, 2576, 2623, 2669, 2715, 2761, 2806, 2851, 2895, 2939, 2982, 3025, 3067, 3108, 3149, 3189, 3229, 3268, 3306, 3343, 3380, 3415, 3450, 3484, 3517, 3550, 3581, 3611, 3641, 3669, 3697, 3724, 3749, 3774, 3797, 3820, 3841, 3861, 3880, 3898, 3915, 3931, 3946, 3960, 3972, 3983, 3993, 4002, 4010, 4017, 4022, 4026, 4029, 4031, 4032, 4031, 4029, 4026, 4022, 4017, 4010, 4002, 3993, 3983, 3972, 3960, 3946, 3931, 3915, 3898, 3880, 3861, 3841, 3820, 3797, 3774, 3749, 3724, 3697, 3669, 3641, 3611, 3581, 3550, 3517, 3484, 3450, 3415, 3380, 3343, 3306, 3268, 3229, 3189, 3149, 3108, 3067, 3025, 2982, 2939, 2895, 2851, 2806, 2761, 2715, 2669, 2623, 2576, 2529, 2481, 2434, 2386, 2338, 2289, 2241, 2193, 2144, 2095, 2046, 1998, 1949, 1900, 1852, 1804, 1755, 1707, 1659, 1612, 1564, 1517, 1470, 1424, 1378, 1332, 1287, 1242, 1198, 1154, 1111, 1068, 1026, 985, 944, 904, 864, 825, 787, 750, 713, 678, 643, 609, 576, 543, 512, 482, 452, 424, 396, 369, 344, 319, 296, 273, 252, 232, 213, 195, 178, 162, 147, 133, 121, 110, 100, 91, 83, 76, 71, 67, 64, 62, 62, 62, 64, 67, 71, 76, 83, 91, 100, 110, 121, 133, 147, 162, 178, 195, 213, 232, 252, 273, 296, 319, 344, 369, 396, 424, 452, 482, 512, 543, 576, 609, 643, 678, 713, 750, 787, 825, 864, 904, 944, 985, 1026, 1068, 1111, 1154, 1198, 1242, 1287, 1332, 1378, 1424, 1470, 1517, 1564, 1612, 1659, 1707, 1755, 1804, 1852, 1900, 1949, 1998};
	uint16_t squareWaveTable[waveFormRes] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint16_t pulseWaveTable[waveFormRes] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

/**
 * @class apllicationLayer
 *
 * @brief Waves creates and updates the changes needed to output the correct results
 */
class applicationLayer{
	public:

		/**
		 * @brief constructs a applicationLayer object
		 * @param InputQueue struct of inputQueue instance InputQueueInstance allows input values to be read
		 * @param SignalQueue1 struct of signalQueue instance called SignalQueueInstance1 allows signal values to be written
		 * @param SignalQueue2 struct of signalQueue instance called SignalQueueInstance2 allows signal values to be written
		 */
		applicationLayer(inputQueue *InputQueue, signalQueue *SignalQueue1, signalQueue *SignalQueue2);

		/**
		* @brief updates all of the possible wave values for all modes
	    */
    	void update();
	private:
    	inputQueue *InputQueueInstance;
    	signalQueue *SignalQueueInstance1;
    	signalQueue *SignalQueueInstance2;
    	Waves waveGen;
    	signalInfo currentWave1;
    	signalInfo currentWave2; //wave data that is not lost in echo mode
    	signalInfo currentWave2Echo; //wave data for echo mode
    	uint8_t channelToChange = 1;

    	/**
    	* @brief checks if the frequency is within the min and max so it can increase and decrease safely
    	* @param freq is an unsigned integer that tracks the current value of the frequency
    	* @param incAmt is an unsigned integer it is the amount to increase or decrease the current frequency by
    	*/
    	void checkFreq(uint16_t *freq,int8_t incAmt);

    	/**
    	* @brief checks if the amplitude is within the min and max so it can increase and decrease safely
       	* @param amp is an unsigned integer that tracks the current value of the amplitude
    	* @param incAmt is an unsigned integer it is the amount to increase or decrease the current amplitude by
       	*/
    	void checkAmp(uint16_t *amp,int8_t incAmt);

    	/**
    	* @brief checks if the delay is within the min and max so it can increase and decrease safely
    	* @param shift is an unsigned integer that tracks the current value of the shift
    	* @param incAmt is an unsigned integer the amount to increase or decrease the current shift by
    	*/
    	void checkDelay(uint16_t *shift,int8_t incAmt);

    	/**
    	* @brief changes the wave type based on the current wave
    	*
    	* @param currentWave is an enum value it stores what the current wave is
    	*/
    	void increaseWaveType(WaveShape *currentWave);

    	/**
    	* @brief checks the knob frequency values and changes the frequency by 1, 10, or 100
    	*
    	* @param signal is a struct signalInfo that tracks the current value of the frequency
        * @param knobValue is a signed integer that dictates if the frequency can increase, decrease, or stay the same
    	*/
    	void setFrequency(signalInfo *signal, int8_t knobValue);

    	/**
    	* @brief checks the knob amplitude values and changes the amplitude by a .1V step
    	*
    	* @param signal is a struct signalInfo that tracks the current value of the amplitude
    	* @param knobValue is a signed integer that dictates if the amplitude can increase, decrease, or stay the same
    	*/
    	void setAmplitude(signalInfo *signal, int8_t knobValue);

    	/**
    	* @brief changes and updates the wave values and checks which wave function to run
    	*
    	* @param signal is a struct signalInfo that tracks the current value of the frequency, amplitude, and wave type
    	*/
    	void updateWave(signalInfo *signal);

    	/**
    	* @brief checks the knob delay values and changes the wave if it is in echo mode
    	*
    	* @param currentInput is a struct inputValues that tracks the current value of the delay knob
    	*/
    	void echoMode(inputValues *currentInput);
};

/**
 * @class Semaphore
 * @brief Semaphore for the ISR to check for input driver updates
 */
class Semaphore{
	bool buffer[1];
    uint8_t head = 0;
    uint8_t tail = 0;
    //uint32_t activeValues = 0;

public:

	/**
	 * @brief Enqueue a value to the queue
	 * @param msg a boolean value
	 * @return If the value was successfully enqueued
	 */
    bool enqueue(bool msg);

	/**
	 * @brief Dequeue a value from the queue
	 * @param msg a boolean value
	 * @return If there was a value to dequeue
	 */
    bool dequeue(bool* msg);

	/**
	 * @brief Perform rolling math so the queue is circular
	 *
	 * @param position A uint8_t that will be changed to be the next position
	 */
    void rollingMath(uint8_t *position);
};

#endif /* INC_OLIVIA_H_ */
