/*
 * shane.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: Shane Wood
 *
 */

#include "allIncludes.h"

void display::initDisplay() {
	//LL_I2C_GenerateStartCondition(I2C1);
	sendCommand(0xAE);
	sendCommand(0xA8);  //Set MUX ratio
	sendCommand(0x3F);  //Set MUX ratio, 0x1F for 128x32 and 0x3F for 128x64
	sendCommand(0xD3);  //Set Display Offset
	sendCommand(0x00);  //Set Display Offset
	sendCommand(0x40);  //Set Display Start Line
	sendCommand(0x20);  //Set Display Mode to Horizontal
	sendCommand(0x00);  //Set Display Mode to Horizontal
	sendCommand(0xA1);  //Set Segment Re-map
	sendCommand(0xC8);  //Set COM Output Scan Direction
	sendCommand(0xDA);  //Set COM Pins hardware configuration
	sendCommand(0x12); //Set COM Pins hardware configuration, 0x02 for 128x32 and 0x12 for 128x64
	sendCommand(0x81);  //Set Contrast Control
	sendCommand(0x9F); //Set Contrast Control Value from 0x00 to 0xFF minimum to maximum
	sendCommand(0xA4);  //Disable Entire Display
	sendCommand(0xA6);  //Set Normal Display
	sendCommand(0xD5);  //Set Oscillation Frequency
	sendCommand(0x80);  //Set Oscillation Frequency
	sendCommand(0x8D);  //Enable Charge Pump Regulator
	sendCommand(0x14);  //Enable Charge Pump Regulator
	sendCommand(0xAF);  //Turn Display On
	return;
}

//send commands to the display
void display::sendCommand(uint8_t command) {
	HAL_StatusTypeDef writing = HAL_I2C_Mem_Write(hi2c1, SSD1306Address, 0x00, 1, &command, 1,
			HAL_MAX_DELAY);
	switch(writing){
	case HAL_ERROR:{
		NVIC_SystemReset();
		break;
	}
	default:{
		return;
		break;
	}
	}
}

//set write data to the display
void display::sendData(uint8_t *data, size_t len) {
	HAL_StatusTypeDef writing = HAL_I2C_Mem_Write(hi2c1, SSD1306Address, 0x40, 1, data, len, HAL_MAX_DELAY);
	switch(writing){
	case HAL_ERROR:{
		NVIC_SystemReset();
		break;
	}
	default:{
		return;
		break;
	}
	}
}

//draw a pixel to the display buffer
void display::drawPixel(const uint8_t x, const uint8_t y, const bool color) {
	if (x >= SSD1306HorizontalRes or y >= SSD1306VerticalRes) {
		return;  //drawing a pixel out of range
	}

	if (color) {
		buffer[x + (y / 8) * SSD1306HorizontalRes] |= (1 << (y % 8));
	} else {
		buffer[x + (y / 8) * SSD1306HorizontalRes] &= ~(1 << (y % 8));
	}
	return;
}

//write a letter to the display buffer
void display::writeLetter(const uint8_t letter, const uint8_t xPos, const uint8_t yPos) {
	const uint16_t *matrix = mainFont.getLetter(letter);
	if (matrix != nullptr) { //ensure that font exists before writing
		for (int i = 0; i < 16; i++) { //16 tall
			for (int j = 0; j < 12; j++) { // 12 wide
				if ((matrix[i]) & (1 << (12 - j))) {
					drawPixel(xPos + j, yPos + i, true);
				}
			}
		}
	}
	return;
}

void display::writeSymbol(const uint32_t *symbol, const uint8_t xPos, const uint8_t yPos) {
	for (int i = 0; i < 14; i++) { //14 tall
		for (int j = 0; j < 20; j++) { // 20 wide
			if ((symbol[i]) & (1 << (20 - j))) {
				drawPixel(xPos + j, yPos + i, true);
			}
		}
	}
	return;
}

//empties buffer so that new data can be put into it
void display::clearBuffer() {
	for (uint16_t i = 0; i < 1024; i++) {
		buffer[i] = 0;
	}
	return;
}

//set up the display
display::display(I2C_HandleTypeDef *hi2c1I,displayQueue *displayQueueI) {
	hi2c1 = hi2c1I;
	displayQueueInstance = displayQueueI;
	initDisplay();
}

//writes buffer to the display
void display::writeBuffer() {
	for (uint8_t i = 0; i < 8; i++) {  // Send each page
		sendCommand(0xB0 + i);  // Set page start address
		sendCommand(0x00);      // Set lower column address
		sendCommand(0x10);      // Set higher column address

		sendData(&buffer[128 * i], 128);
	}
	return;
}

void display::drawWordsNorm() {
	writeLetter('F', 0, 0);
	writeLetter('r', 15, 0);
	writeLetter('e', 31, 0);
	writeLetter('q', 47, 0);

	writeLetter('A', 0, 15);
	writeLetter('m', 15, 15);
	writeLetter('p', 31, 15);

	writeLetter('F', 0, 31);
	writeLetter('r', 15, 31);
	writeLetter('e', 31, 31);
	writeLetter('q', 47, 31);

	writeLetter('A', 0, 47);
	writeLetter('m', 15, 47);
	writeLetter('p', 31, 47);
}

void display::drawWordsShift() {
	writeLetter('F', 0, 0);
	writeLetter('r', 15, 0);
	writeLetter('e', 31, 0);
	writeLetter('q', 47, 0);

	writeLetter('A', 0, 15);
	writeLetter('m', 15, 15);
	writeLetter('p', 31, 15);

	writeLetter('S', 0, 31);
	writeLetter('h', 15, 31);
	writeLetter('i', 31, 31);
	writeLetter('f', 47, 31);
	writeLetter('t', 63, 31);
}

void display::convertAmp(const signalInfo *signal, const uint8_t Channel) {
	uint8_t row;
	if (Channel == 0) {
		row = 0;
	} else {
		row = 31;
	}
	uint16_t place0 = uint16_t(signal->amp * 3300 / 4095);
	uint8_t place1 = (uint8_t) (place0 / 1000);
	uint8_t place2 = (uint8_t) ((place0 - place1 * 1000) / 100);
	uint8_t place3 = (uint8_t) ((place0 - place1 * 1000 - place2 * 100) / 10);

	writeLetter('0' + (place1), 47, row + 16);
	writeLetter('.', 59, row + 16);
	writeLetter('0' + (place2), 71, row + 16);
	writeLetter('0' + (place3), 83, row + 16);
}

void display::convertFreq(const signalInfo *signal, const uint8_t Channel) {
	uint8_t row;
	if (Channel == 0) { //handle ch1 and ch2 frequencies
		row = 0;
	} else {
		row = 31;
	}

	const uint32_t currentFreq = signal->frequency;
	uint32_t tempSums[4];
	uint8_t finalValues[5];

	finalValues[0] = uint8_t(currentFreq / 10000);
	tempSums[0] = finalValues[0] * 10000;

	finalValues[1] = uint8_t((currentFreq - tempSums[0]) / 1000);
	tempSums[1] = tempSums[0] + finalValues[1] * 1000;
	finalValues[2] = uint8_t((currentFreq - tempSums[1]) / 100);
	tempSums[2] = tempSums[1] + finalValues[2] * 100;
	finalValues[3] = uint8_t((currentFreq - tempSums[2]) / 10);
	tempSums[3] = tempSums[2] + finalValues[3] * 10;
	finalValues[4] = uint8_t((currentFreq - tempSums[3]));

	uint8_t firstPlace = 4;
	const uint8_t freqNumberPositions[] = { 67, 79, 91, 103, 115 };
	for (uint8_t i = 0; i < 5; i++) {
		if (finalValues[i] != 0) {
			firstPlace = i;
			break;
		}
	}
	for (uint8_t i = firstPlace; i < 5; i++) {
		writeLetter('0' + finalValues[i], freqNumberPositions[i], row);
	}
	return;
}

void display::convertShift(const signalInfo *signal){
	if(signal->wave == ECHO){
		//attempting to keep as much resolution as possible
		//180 * 360 < 2^16 -1 therefore the uint16_t will not be fully used
		//but it will also allow for slightly more resolution than just whole numbers
		uint16_t currentShift = (uint16_t)((signal->shiftAmount)*(360.0/waveFormRes));
		if(currentShift > 360){
			return;
		}
		uint8_t finalValues[3];
		finalValues[0] = (uint8_t)(currentShift/100);
		finalValues[1] = (uint8_t)((currentShift-finalValues[0]*100) / 10);
		finalValues[2] = (uint8_t)(currentShift-finalValues[0]*100-finalValues[1]*10);
		uint8_t firstPlace = 2;
		const uint8_t shiftNumberPositions[] = {75, 87, 99};
		for (uint8_t i = 0; i < 3; i++) {
			if (finalValues[i] != 0) {
				firstPlace = i;
				break;
			}
		}
		for (uint8_t i = firstPlace; i < 3; i++) {
			writeLetter('0' + finalValues[i], shiftNumberPositions[i], 31);
		}
	}else{
		return;
	}
}
void display::displaySignalType(const signalInfo *signal, const uint8_t Channel) {
	uint8_t row = 16;
	if (Channel == 1) {
		row = 48;
	}
	const uint32_t *symbolToWrite = nullptr;
	if (signal->wave == SINE) {
		symbolToWrite = mainFont.getSineVis();
	} else if (signal->wave == SQUARE) {
		symbolToWrite = mainFont.getSquareVis();
	} else if (signal->wave == PULSE) {
		symbolToWrite = mainFont.getPulseVis();
	} else {
		//wave not valild, display nothing
		return;
	}
	if(symbolToWrite != nullptr){
		writeSymbol(symbolToWrite, 102, row);
	}
	return;
}

void display::getNewValues() {
	displayInfo displayedInfo;
	if (displayQueueInstance->dequeue(&displayedInfo)) {
		convertFreq(displayedInfo.ChannelAInfo, 0);
		convertAmp(displayedInfo.ChannelAInfo, 0);
		displaySignalType(displayedInfo.ChannelAInfo, 0);
		if (displayedInfo.ChannelBInfo->wave != ECHO) {
			convertFreq(displayedInfo.ChannelBInfo, 1);
			convertAmp(displayedInfo.ChannelBInfo, 1);
			displaySignalType(displayedInfo.ChannelBInfo, 1);
			drawWordsNorm(); //temporary
		} else {
			convertShift(displayedInfo.ChannelBInfo);
			drawWordsShift();
			assert(
					displayedInfo.ChannelAInfo->amp
							== displayedInfo.ChannelBInfo->amp);
			assert(
					displayedInfo.ChannelAInfo->frequency
							== displayedInfo.ChannelBInfo->frequency);
		}
		writeBuffer();
		return;
	} else {
		return;
	}
}

dacDriver::dacDriver(dacSetup *dacValues) {
	hdac = dacValues->hdacI;
	DacChannel = dacValues->DacChannel1I;
	timerInstance = dacValues->timer1I;
	signalQueueInstance = dacValues->channel1I;

	//ensure that something is in current signal
	HAL_StatusTypeDef DMA =  HAL_DAC_Start_DMA(hdac, DacChannel, currentSignal.signalLocations,
			waveFormRes, DAC_ALIGN_12B_R);
	switch(DMA){
	case HAL_ERROR:{
		//DMA failed to start, not recoverable
		NVIC_SystemReset();
		break;
	}
	default:{
		return;
		break;
	}
	}
}

void dacDriver::checkQueue() {
	if (signalQueueInstance->dequeue(&currentSignal)) {
		setReload(); //set new period
	}
	return;
}

void dacDriver::setReload() {
	currentReloadValue = (uint32_t) FCLK
			/ ((timerPSC + 1) * (currentSignal.frequency) * waveFormRes);

	//hal method
	//__HAL_TIM_SET_AUTORELOAD(timerInstance, currentReloadValue);

	//no hal method
	timerInstance->Instance->ARR = currentReloadValue;
}

signalInfo* dacDriver::getSignalInfo() {
	return &currentSignal; //returns signal that is currently being displayed
}

void dacDriver::update() {
	checkQueue();
	//ensure that something is in current signal
}

outputDriver::outputDriver(dacDriver *DACchannel1I, dacDriver *DACchannel2I,
		dacSetup *DACchannel1SetupI, dacSetup *DACchannel2SetupI,
		displayQueue *displayInfoQI) {
	DACChannel1Setup = DACchannel1SetupI;
	DACChannel2Setup = DACchannel2SetupI;
	DACchannel1 = DACchannel1I;
	DACchannel2 = DACchannel2I;

	update();

	//hal version
	//HAL_TIM_Base_Start(DACChannel1Setup->timer1I);
	//HAL_TIM_Base_Start(DACChannel2Setup->timer1I);

	//non hal version, TOO MANY ->
	//DACChannel1Setup->timer1I->Instance->CR1 |= TIM_CR1_CEN;
	//DACChannel2Setup->timer1I->Instance->CR1 |= TIM_CR1_CEN;


	TIM_HandleTypeDef *Channel1Timer = DACChannel1Setup->timer1I;
	TIM_HandleTypeDef *Channel2Timer = DACChannel2Setup->timer1I;
	Channel1Timer->Instance->CR1 |= TIM_CR1_CEN;
	Channel2Timer->Instance->CR1 |= TIM_CR1_CEN;



	signalInfo* channel1Info = DACchannel1->getSignalInfo();
	signalInfo* channel2Info = DACchannel2->getSignalInfo();
	if(channel1Info != nullptr and channel2Info != nullptr){
		soonDisplayInfo = { channel1Info,channel2Info};
		if (displayInfoQI->enqueue(soonDisplayInfo) == false) {
			//something is very wrong if it cannot enqueue during constructor,
			//restarting now as DMA will fail later
			NVIC_SystemReset();
		}
	}else{
		NVIC_SystemReset();
	}
}

void outputDriver::update() {
	DACchannel1->update();
	DACchannel2->update();
	//displayInfo toWrite = {DACchannel1->getSignalInfo(),DACchannel2->getSignalInfo()};
	//displayInfoQ->enqueue(toWrite);
}

void font::initializeFontMap() {
	fontMap['0'] = zero;
	fontMap['1'] = one;
	fontMap['2'] = two;
	fontMap['3'] = three;
	fontMap['4'] = four;
	fontMap['5'] = five;
	fontMap['6'] = six;
	fontMap['7'] = seven;
	fontMap['8'] = eight;
	fontMap['9'] = nine;
	fontMap['#'] = hash;
	fontMap['A'] = capA;
	fontMap['B'] = capB;
	fontMap['C'] = capC;
	fontMap['D'] = capD;
	fontMap['E'] = capE;
	fontMap['F'] = capF;
	fontMap['G'] = capG;
	fontMap['H'] = capH;
	fontMap['I'] = capI;
	fontMap['J'] = capJ;
	fontMap['K'] = capK;
	fontMap['L'] = capL;
	fontMap['M'] = capM;
	fontMap['N'] = capN;
	fontMap['O'] = capO;
	fontMap['P'] = capP;
	fontMap['Q'] = capQ;
	fontMap['R'] = capR;
	fontMap['S'] = capS;
	fontMap['T'] = capT;
	fontMap['U'] = capU;
	fontMap['V'] = capV;
	fontMap['W'] = capW;
	fontMap['X'] = capX;
	fontMap['Y'] = capY;
	fontMap['Z'] = capZ;
	fontMap['a'] = lowA;
	fontMap['b'] = lowB;
	fontMap['c'] = lowC;
	fontMap['d'] = lowD;
	fontMap['e'] = lowE;
	fontMap['f'] = lowF;
	fontMap['g'] = lowG;
	fontMap['h'] = lowH;
	fontMap['i'] = lowI;
	fontMap['j'] = lowJ;
	fontMap['k'] = lowK;
	fontMap['l'] = lowL;
	fontMap['m'] = lowM;
	fontMap['n'] = lowN;
	fontMap['o'] = lowO;
	fontMap['p'] = lowP;
	fontMap['q'] = lowQ;
	fontMap['r'] = lowR;
	fontMap['s'] = lowS;
	fontMap['t'] = lowT;
	fontMap['u'] = lowU;
	fontMap['v'] = lowV;
	fontMap['w'] = lowW;
	fontMap['x'] = lowX;
	fontMap['y'] = lowY;
	fontMap['z'] = lowZ;
	fontMap['-'] = Dash;
	fontMap['.'] = Decimal;
	fontMap['%'] = percent;
	fontMap['|'] = verticalBar;
}

font::font() {
	initializeFontMap();
}

const uint16_t* font::getLetter(const uint8_t letter) {
	return fontMap[(uint8_t) letter];
}

const uint32_t* font::getSineVis() {
	return sineWaveVis;
}
const uint32_t* font::getSquareVis() {
	return squareWaveVis;
}
const uint32_t* font::getPulseVis() {
	return pulseWaveVis;
}

