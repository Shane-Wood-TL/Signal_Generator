/*
 * shane.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Shane Wood
 */

#ifndef INC_SHANE_H_
#define INC_SHANE_H_
#include "allIncludes.h"
//https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Projects/NUCLEO-L432KC/Examples/DAC/DAC_SignalsGeneration/readme.txt
//https://deepbluembedded.com/stm32-dac-sine-wave-generation-stm32-dac-dma-timer-example/

class dacDriver{
	DAC_HandleTypeDef *hdac;
	uint32_t DacChannel;
	TIM_HandleTypeDef *timerInstance;
	signalQueue *signalQueueInstance;
	signalInfo currentSignal;
	uint32_t currentReloadValue = 0;
	public:
		dacDriver(dacSetup *dacValues);
		void checkQueue();
		void setReload();
		signalInfo* getSignalInfo();
		void update();
};


class display{
private:
	I2C_HandleTypeDef *hi2c1;
	displayQueue *displayQueueInstance;
	uint8_t buffer[1024] = {0};
	font mainFont;
	//dacDriver *dac0;
	//dacDriver *dac1;
	void initializeFontMap();


	const uint16_t *getLetter(uint8_t letter);
	//set up the i2c display (ssd1306)
	void initDisplay();

	//send commands to the display
	void sendCommand(uint8_t command);

	//set write data to the display
	void sendData(uint8_t *data, size_t len);

	//draw a pixel to the display buffer
	void drawPixel(const uint8_t x, const uint8_t y,const bool color);

	//write a letter to the display buffer
	void writeLetter(const uint8_t letter, const uint8_t xPos, const uint8_t yPos);
	void writeSymbol(const uint32_t *symbol, const uint8_t xPos, const uint8_t yPos);


	//empties buffer so that new data can be put into it
	void clearBuffer();

	void writeBuffer();
	void drawWordsNorm();
	void drawWordsShift();
	void convertFreq(const signalInfo *signal, const uint8_t Channel);
	void convertAmp(const signalInfo *signal, const uint8_t Channel);
	void displaySignalType(const signalInfo *signal, const uint8_t Channel);
	void convertShift(const signalInfo *signal);
public:
	display(I2C_HandleTypeDef *hi2c1I, displayQueue *displayQueueI);//dacDriver *dac0I,dacDriver *dac1I);
	//writes buffer to the display

	void getNewValues();

};


class outputDriver{
	dacSetup *DACChannel1Setup;
	dacSetup *DACChannel2Setup;
	dacDriver *DACchannel1;
	dacDriver *DACchannel2;
	displayQueue *displayInfoQ;
	displayInfo soonDisplayInfo;
public:
	outputDriver(dacDriver *DACchannel1I,dacDriver *DACchannel2I, dacSetup *DACchannel1SetupI, dacSetup *DACchannel2SetupI, displayQueue *displayInfoQI);
	void update();
};





#endif /* INC_SHANE_H_ */
