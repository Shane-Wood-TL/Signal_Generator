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
	void setReload();
	public:
		dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I, TIM_HandleTypeDef *timer1Il, signalQueue *channel1I);
		//signalInfo* getSignalInfo();
		void update();
		void enableTimer();
		uint32_t getFreq();
		uint16_t getAmp();
		uint8_t getShift();
		WaveShape getWave();
};


class display{
private:
	SPI_HandleTypeDef *hspi1;
	displayQueue *displayQueueInstance;
	uint8_t buffer[1024] = {0};
	font mainFont;
	uint8_t count = 0;
	const uint8_t letterPositions[5] = {0,15,31,47,63}; //constant positions of letters written to the screen
	const uint8_t freqList[4] = {'F', 'r','e','q'}; //ASCII for F,r,e,q
	const uint8_t ampList[3] = {'A','m','p'}; //ASCII for A,m,p
	const uint8_t shiftList[5] = {83, 104,105,102,116};//ASCII for S,h,i,f,t

	//set up the i2c display (ssd1306)
	void initDisplay();

	//send commands to the display
	void sendCommand(uint8_t command);

	//set write data to the display
	void sendData(uint8_t *data, uint16_t len);

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
	void convertFreq(const uint32_t currentFreq, const uint8_t Channel);
	void convertAmp(const uint16_t amp, const uint8_t Channel);
	void displaySignalType(const WaveShape shape, const uint8_t Channel);
	void convertShift(const uint8_t signal);
public:
	display(SPI_HandleTypeDef *hspi1I, displayQueue *displayQueueI);//dacDriver *dac0I,dacDriver *dac1I);
	//writes buffer to the display

	void getNewValues();

};


class outputDriver{
	dacDriver *DACchannel1;
	dacDriver *DACchannel2;
	displayQueue *displayInfoQ;
	struct displayInfoValues soonDisplayInfo;
public:
	outputDriver(dacDriver *DACchannel1I,dacDriver *DACchannel2I, displayQueue *displayInfoQI);
	void update();
};





#endif /* INC_SHANE_H_ */
