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
    	* newPositions an unsigned integer which is a specific value in an array based on a shifted version of the currentPositions array
    	*
    	* shiftAmt is an unsigned integer that dictates the amount of values that are removed from the front of the currentPositions array and
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
	* @param a struct signalInfo toShift an array of values that is going to be modified
	* an unsigned integer amount which dictates the amount to shift the toShift wave
	*
	* @return a struct signalInfo instance called modifiedWave based on the toShift wave
	*/
	signalInfo getDelay(signalInfo toShift, uint8_t amount);

	/**
	* @brief makes a new copy of the wave and adjusts the amplitude
	*
	* @param a struct signalInfo toScale an array of values that is going to be modified
	* an unsigned integer newAmp
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

	uint16_t sineWaveTable[waveFormRes] = {2047, 2097, 2147, 2198, 2248, 2298, 2348, 2398, 2447, 2497, 2546, 2595, 2643, 2691, 2739, 2786, 2833, 2879, 2925, 2970, 3015, 3059, 3103, 3145, 3188, 3229, 3270, 3310, 3349, 3388, 3426, 3462, 3498, 3534, 3568, 3601, 3633, 3665, 3695, 3725, 3753, 3780, 3807, 3832, 3856, 3879, 3901, 3922, 3941, 3960, 3977, 3993, 4008, 4022, 4035, 4046, 4056, 4065, 4073, 4079, 4085, 4089, 4092, 4093, 4093, 4093, 4090, 4087, 4082, 4076, 4069, 4061, 4051, 4041, 4029, 4015, 4001, 3985, 3969, 3951, 3932, 3911, 3890, 3868, 3844, 3819, 3793, 3767, 3739, 3710, 3680, 3649, 3617, 3584, 3551, 3516, 3481, 3444, 3407, 3369, 3330, 3290, 3250, 3209, 3167, 3124, 3081, 3037, 2993, 2948, 2902, 2856, 2809, 2762, 2715, 2667, 2619, 2570, 2521, 2472, 2423, 2373, 2323, 2273, 2223, 2173, 2122, 2072, 2021, 1971, 1920, 1870, 1820, 1770, 1720, 1670, 1621, 1572, 1523, 1474, 1426, 1378, 1331, 1284, 1237, 1191, 1145, 1100, 1056, 1012, 969, 926, 884, 843, 803, 763, 724, 686, 649, 612, 577, 542, 509, 476, 444, 413, 383, 354, 326, 300, 274, 249, 225, 203, 182, 161, 142, 124, 108, 92, 78, 64, 52, 42, 32, 24, 17, 11, 6, 3, 0, 0, 0, 1, 4, 8, 14, 20, 28, 37, 47, 58, 71, 85, 100, 116, 133, 152, 171, 192, 214, 237, 261, 286, 313, 340, 368, 398, 428, 460, 492, 525, 559, 595, 631, 667, 705, 744, 783, 823, 864, 905, 948, 990, 1034, 1078, 1123, 1168, 1214, 1260, 1307, 1354, 1402, 1450, 1498, 1547, 1596, 1646, 1695, 1745, 1795, 1845, 1895, 1946, 1996};
	uint16_t squareWaveTable[waveFormRes] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint16_t pulseWaveTable[waveFormRes]=	{4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
		 * @param struct of inputQueue instance InputQueueInstance allows input values to be read
		 * struct of signalQueue instance called SignalQueueInstance1 allows signal values to be written
		 * struct of signalQueue instance called SignalQueueInstance2 allows signal values to be written
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
    	* incAmt is an unsigned integer it is the amount to increase or decrease the current frequency by
    	*/
    	void checkFreq(uint16_t *freq,int8_t incAmt);

    	/**
    	* @brief checks if the amplitude is within the min and max so it can increase and decrease safely
       	* @param amp is an unsigned integer that tracks the current value of the amplitude
    	* incAmt is an unsigned integer it is the amount to increase or decrease the current amplitude by
       	*/
    	void checkAmp(uint16_t *amp,int8_t incAmt);

    	/**
    	* @brief checks if the delay is within the min and max so it can increase and decrease safely
    	* @param shift is an unsigned integer that tracks the current value of the shift
    	* incAmt is an unsigned integer the amount to increase or decrease the current shift by
    	*/
    	void checkDelay(uint8_t *shift,int8_t incAmt);

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
        * knobValue is a signed integer that dictates if the frequency can increase, decrease, or stay the same
    	*/
    	void setFrequency(signalInfo *signal, int8_t knobValue);

    	/**
    	* @brief checks the knob amplitude values and changes the amplitude by a .1V step
    	*
    	* @param signal is a struct signalInfo that tracks the current value of the amplitude
    	* knobValue is a signed integer that dictates if the amplitude can increase, decrease, or stay the same
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
