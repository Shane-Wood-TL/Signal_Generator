/*
 * shane.h
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
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
};


class display{
private:
	const uint16_t *fontMap[128] = {0}; //ASCII table
	I2C_HandleTypeDef *hi2c1;
	displayQueue *displayQueueInstance;
	uint8_t buffer[1024] = {0};
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
	void drawPixel(uint8_t x, uint8_t y,bool color);

	//write a letter to the display buffer
	void writeLetter(uint8_t letter, uint8_t xPos, uint8_t yPos);


	//empties buffer so that new data can be put into it
	void clearBuffer();

public:
	display(I2C_HandleTypeDef *hi2c1I, displayQueue *displayQueueI);//dacDriver *dac0I,dacDriver *dac1I);
	//writes buffer to the display
	void writeBuffer();
	void drawWords();
	void getNewValues();

};


class outputDriver{
	dacSetup *DACChannel1Setup;
	dacSetup *DACChannel2Setup;
	dacDriver *DACchannel1;
	dacDriver *DACchannel2;
	displayQueue *displayInfoQ;
public:
	outputDriver(dacDriver *DACchannel1I,dacDriver *DACchannel2I, dacSetup *DACchannel1SetupI, dacSetup *DACchannel2SetupI, displayQueue *displayInfoQI);
	void update();
};

#endif /* INC_SHANE_H_ */