/*
 * shane.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: Shane Wood
 *
 */

#include "allIncludes.h"
//D/C D4 PB_7
// RST D5 PB_6

#define dcPort GPIOB
#define dcPin LL_GPIO_PIN_7

#define rstPort GPIOB
#define rstPin LL_GPIO_PIN_6
void display::initDisplay() {
	LL_SPI_Enable(hspi1->Instance); //make sure that SPI is on
    LL_GPIO_SetOutputPin(rstPort, rstPin); //set = not in reset mode

    //list of init commands
	sendCommand(0xAE);	//Turn Display off
	sendCommand(0xA8);  //Set MUX ratio
	sendCommand(0x3F);  //Set MUX ratio,0x3F for 128x64
	sendCommand(0xD3);  //Set Display Offset
	sendCommand(0x00);  //Set Display Offset
	sendCommand(0x40);  //Set Display Start Line
	sendCommand(0x20);  //Set Display Mode to Horizontal
	sendCommand(0x00);  //Set Display Mode to Horizontal
	sendCommand(0xA1);  //Set Segment Re-map
	sendCommand(0xC8);  //Set COM Output Scan Direction
	sendCommand(0xDA);  //Set COM Pins hardware configuration
	sendCommand(0x12); //Set COM Pins hardware configuration, 0x12 for 128x64
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
	LL_GPIO_ResetOutputPin(dcPort, dcPin);
	if(count != 1){
		LL_SPI_TransmitData8(hspi1->Instance, command); // Send the command
		while (!LL_SPI_IsActiveFlag_TXE(hspi1->Instance));
        //max time for while loop
        //Need to find bits / s based on SPI speed
        // 10 Mbits / s, Data size = 8 bits
        // 10,000,000 / 8 = 1,250,000 messages per second
        //8 x 10^-7 s
        // 0.8 uS max time per message / while loop
	}else{
		HAL_SPI_Transmit(hspi1, &command, 1, HAL_MAX_DELAY); //let HAL set up the SPI port for the first time
		count=1;
	}
}

//set write data to the display
void display::sendData(uint8_t *data, uint16_t len) {
	assert(len >= 1);
    LL_GPIO_SetOutputPin(dcPort, dcPin);

    for (uint16_t i = 0; i < len; i++) {
        LL_SPI_TransmitData8(hspi1->Instance, data[i]); // Send each byte
        while (!LL_SPI_IsActiveFlag_TXE(hspi1->Instance));
        //max time for while loop
        //Need to find bits / s based on SPI speed
        // 10 Mbits / s, Data size = 8 bits
        // 10,000,000 / 8 = 1,250,000 messages per second
        //8 x 10^-7 s
        // 0.8 uS max time per message / while loop

    }
}


//draw a pixel to the display buffer
void display::drawPixel(const uint8_t x, const uint8_t y, const bool color) {
	if (x >= SSD1306HorizontalRes or y >= SSD1306VerticalRes) {
			return;  //drawing a pixel out of range
	}

	assert (x < SSD1306HorizontalRes && y < SSD1306VerticalRes);

	uint8_t pixelInPage = (1 << (y % 8)); //limit the pixel from 0 to 7 with a 1 in the position 0000_0001, 0000_0010, etc

	//buffer is indexed as such
	// x straight across 0-127
	//each one of these is 8 pixels bits tall, or 1 page
	//repeat for pages 0-8
	//leading to a total size of 128*8 = 1024 page "strips" each containing the data for 8 pixels
	uint16_t bufferIndex = uint16_t(x + (y / 8) * SSD1306HorizontalRes);
	if (color) {
		buffer[bufferIndex] |= pixelInPage;
	} else {
		buffer[bufferIndex] &= ~pixelInPage;
	}
	return;
}

//write a letter to the display buffer
void display::writeLetter(const uint8_t letter, const uint8_t xPos, const uint8_t yPos) {

	const uint16_t *matrix = mainFont.getLetter(letter);
	if (matrix != nullptr) { //ensure that font exists before writing
		assert(matrix !=nullptr);
		for (int i = 0; i < 16; i++) { //16 tall
			for (int j = 0; j < 12; j++) { // 12 wide
				if ((matrix[i]) & (1 << (12 - j))) {
					drawPixel(xPos + j, yPos + i, true);
				}
			}
		}
	}else{
		return;
	}
	return;
}

void display::writeSymbol(const uint32_t *symbol, const uint8_t xPos, const uint8_t yPos) {
	assert(symbol != nullptr);

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
	assert(buffer[1023]==0);
	return;
}

//set up the display
display::display(SPI_HandleTypeDef *hspi1I,displayQueue *displayQueueI) {
	hspi1 = hspi1I;
	displayQueueInstance = displayQueueI;
	initDisplay();
}

//writes buffer to the display
void display::writeBuffer() {
	for (uint8_t i = 0; i < 8; i++) { //send each page
		sendCommand(0xB0 + i);  //page address
		sendCommand(0x00);      //bottom of page
		sendCommand(0x10);      //top of page
		sendData(&buffer[128 * i], 128); //send an entire row
	}
	return;
}

void display::drawWordsNorm() {
	//Write Freq, and Amp to the display
	for(uint8_t i = 0; i < 2; i++){
		for(uint8_t j = 0; j < 4;j++){
			writeLetter(freqList[j],letterPositions[j],letterPositions[i*2]);
		}
		for(uint8_t k = 0; k < 3;k++){
			writeLetter(ampList[k],letterPositions[k],letterPositions[(i*2)+1]);
		}
	}
}

void display::drawWordsShift() {
	//Write Freq, and Amp to the display
		for(uint8_t i = 0; i < 4;i++){
			writeLetter(freqList[i],letterPositions[i],letterPositions[0]);
		}
		for(uint8_t i = 0; i < 3;i++){
			writeLetter(ampList[i],letterPositions[i],letterPositions[1]);
		}
		for(uint8_t i = 0; i < 5;i++){
			writeLetter(shiftList[i],letterPositions[i],letterPositions[2]);
		}
}

void display::convertAmp(const uint16_t amp, const uint8_t Channel) {
	uint8_t row;
	if (Channel == 0) {
		row = 15;
	}else if(Channel == 1){
		row = 47;
	}else{
		return; //Channel is not valid
	}
	assert(row == 15 || row==47);

	uint16_t place0 = uint16_t(amp * 3300 / 4095);
	uint8_t place1 = (uint8_t) (place0 / 1000);
	uint8_t place2 = (uint8_t) ((place0 - place1 * 1000) / 100);
	uint8_t place3 = (uint8_t) ((place0 - place1 * 1000 - place2 * 100) / 10);

	writeLetter('0' + (place1), 47, row);
	writeLetter('.', 59, row);
	writeLetter('0' + (place2), 71, row);
	writeLetter('0' + (place3), 83, row);
}

void display::convertFreq(const uint32_t currentFreq, const uint8_t Channel) {
	uint8_t row;
	if (Channel == 0) { //handle ch1 and ch2 frequencies
		row = 0;
	} else {
		row = 31;
	}
	assert(row == 0 || row==31);

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

void display::convertShift(const uint8_t signal){
		//attempting to keep as much resolution as possible
		//180 * 360 < 2^16 -1 therefore the uint16_t will not be fully used
		//but it will also allow for slightly more resolution than just whole numbers
		uint16_t currentShift = (uint16_t)((signal)*(360.0/waveFormRes));
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
}
void display::displaySignalType(const WaveShape shape, const uint8_t Channel) {
	uint8_t row = 16;
	if (Channel == 1) {
		row = 48;
	}
	assert((row==16) ||(row==48));

	const uint32_t *symbolToWrite = nullptr;
	if (shape == SINE) {
		symbolToWrite = mainFont.getSineVis();
	} else if (shape == SQUARE) {
		symbolToWrite = mainFont.getSquareVis();
	} else if (shape == PULSE) {
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
	displayInfoValues displayedInfo;
	if (displayQueueInstance->dequeue(&displayedInfo)) {
		clearBuffer();
		convertFreq(displayedInfo.Afrequency, 0);
		convertAmp(displayedInfo.Aamp, 0);
		displaySignalType(displayedInfo.Awave, 0);
		if (displayedInfo.Bwave != ECHO) {
			convertFreq(displayedInfo.Bfrequency, 1);
			convertAmp(displayedInfo.Bamp, 1);
			displaySignalType(displayedInfo.Bwave, 1);
			drawWordsNorm(); //temporary
		} else {
			convertShift(displayedInfo.BshiftAmount);
			drawWordsShift();
			assert(
					displayedInfo.Aamp
							== displayedInfo.Bamp);
			assert(
					displayedInfo.Afrequency
							== displayedInfo.Bfrequency);
		}
		writeBuffer();
		return;
	} else {
		return;
	}
}

dacDriver::dacDriver(DAC_HandleTypeDef *hdacI, uint32_t DacChannel1I, TIM_HandleTypeDef *timer1I, signalQueue *channel1I) {
	hdac = hdacI;
	DacChannel = DacChannel1I;
	timerInstance = timer1I;
	signalQueueInstance = channel1I;

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


void dacDriver::setReload() {
	currentReloadValue = (uint32_t) FCLK
			/ ((timerPSC + 1) * (currentSignal.frequency) * waveFormRes);

	//hal method
	//__HAL_TIM_SET_AUTORELOAD(timerInstance, currentReloadValue);

	//no hal method
	timerInstance->Instance->ARR = currentReloadValue;
}


uint32_t dacDriver::getFreq(){
	return currentSignal.frequency;
}
uint16_t dacDriver::getAmp(){
	return currentSignal.amp;
}
uint8_t dacDriver::getShift(){
	return currentSignal.shiftAmount;
}
WaveShape dacDriver::getWave(){
	return currentSignal.wave;
}

void dacDriver::update() {
	if (signalQueueInstance->dequeue(&currentSignal)) {
			setReload(); //set new period
	}
	//ensure that something is in current signal
}

void dacDriver::enableTimer(){
	timerInstance->Instance->CR1 |= TIM_CR1_CEN;
}

outputDriver::outputDriver(dacDriver *DACchannel1I, dacDriver *DACchannel2I,
		displayQueue *displayInfoQI) {
	displayInfoQ = displayInfoQI;
	DACchannel1 = DACchannel1I;
	DACchannel2 = DACchannel2I;
	DACchannel1->enableTimer();
	DACchannel2->enableTimer();
	update();
}

void outputDriver::update() {
	DACchannel1->update();
	DACchannel2->update();
	displayInfoValues toWrite = {DACchannel1->getFreq(),DACchannel1->getAmp(),DACchannel1->getWave(),
			DACchannel2->getFreq(),DACchannel2->getAmp(),DACchannel2->getShift(),DACchannel2->getWave()};
	displayInfoQ->enqueue(toWrite);

	//	displayInfoValues toWrite = {DACchannel1->getFreq(),
	//			DACchannel1->getAmp(),
	//			DACchannel1->getWave(),
	//			DACchannel2->getFreq(),
	//			DACchannel2->getAmp(),
	//			DACchannel2->getShift(),
	//			DACchannel2->getWave()};

}

void font::initializeFontMap() {
	fontMap[l0] = zero;
	fontMap[l1] = one;
	fontMap[l2] = two;
	fontMap[l3] = three;
	fontMap[l4] = four;
	fontMap[l5] = five;
	fontMap[l6] = six;
	fontMap[l7] = seven;
	fontMap[l8] = eight;
	fontMap[l9] = nine;
	fontMap[A] = capA;
	fontMap[F] = capF;
	fontMap[S] = capS;
	fontMap[e] = lowE;
	fontMap[f] = lowF;
	fontMap[h] = lowH;
	fontMap[i] = lowI;
	fontMap[m] = lowM;
	fontMap[p] = lowP;
	fontMap[q] = lowQ;
	fontMap[r] = lowR;
	fontMap[t] = lowT;
	fontMap[ldecimal] = Decimal;
}

font::font() {
	initializeFontMap();
}

const uint16_t* font::getLetter(const uint8_t letter) {
	uint8_t convertLetter = 0;
	switch (letter){
	case(48): // ascii 0
		convertLetter = l0;
		break;
	case(49): // ascii 1
		convertLetter = l1;
		break;
	case(50): // ascii 2
		convertLetter = l2;
		break;
	case(51): // ascii 3
		convertLetter = l3;
		break;
	case(52): // ascii 4
		convertLetter = l4;
		break;
	case(53): // ascii 5
		convertLetter = l5;
		break;
	case(54): // ascii 6
		convertLetter = l6;
		break;
	case(55): // ascii 7
		convertLetter = l7;
		break;
	case(56): // ascii 8
		convertLetter = l8;
		break;
	case(57): // ascii 9
		convertLetter = l9;
		break;
	case(65): // ascii A
		convertLetter = A;
		break;
	case(70): // ascii F
		convertLetter = F;
		break;
	case(83): // ascii S
		convertLetter = S;
		break;
	case(101): // ascii e
		convertLetter = e;
		break;
	case(102): // ascii f
		convertLetter = f;
		break;
	case(104): // ascii h
		convertLetter = h;
		break;
	case(105): // ascii i
		convertLetter = i;
		break;
	case(109): // ascii m
		convertLetter = m;
		break;
	case(112): // ascii p
		convertLetter = p;
		break;
	case(113): // ascii q
		convertLetter = q;
		break;
	case(114): // ascii r
		convertLetter = r;
		break;
	case(116): // ascii t
		convertLetter = t;
		break;
	case(46): // ascii .
		convertLetter = ldecimal;
		break;
	default:
		convertLetter = l0;
		break;
	}
	return fontMap[convertLetter];
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

