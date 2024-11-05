/*
 * display.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */
#include "allIncludes.h"


void display::initDisplay() {
	LL_SPI_Enable(hspi1->Instance); //make sure that SPI is on
    //set = not in reset mode
    rstPortV->ODR |= (1<<rstPinV);
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

	drawWordsNorm(0);
	writeBuffer();
	drawWordsNorm(1);
	return;
}


//send commands to the display
void display::sendCommand(uint8_t command) {
	uint8_t commandSize = sizeof(command);
	if(commandSize!= 1 or command < 0){
		return;
	}
	assert(commandSize == 1);
	dcPort->ODR &= ~(1<<dcPinV);
	LL_SPI_TransmitData8(hspi1->Instance, command); // Send the command
	while (!LL_SPI_IsActiveFlag_TXE(hspi1->Instance));
        //max time for while loop
        //Need to find bits / s based on SPI speed
        // 10 Mbits / s, Data size = 8 bits
        // 10,000,000 / 8 = 1,250,000 messages per second
        //8 x 10^-7 s
        // 0.8 uS max time per message / while loop
}

//set write data to the display
void display::sendData(uint8_t *data, uint16_t len) {
	if(len == 0 || data == nullptr){
		return;
	}
	assert(data != nullptr);
	assert(len >= 1);

    dcPort->ODR |= (1<<dcPinV);
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
void display::drawPixel(const uint8_t x, const uint8_t y) {
	if ((x > SSD1306HorizontalRes) || (y > SSD1306VerticalRes)) {
			return;  //drawing a pixel out of range
	}
	if(x < 0 || y < 0){
		return;
	}

	assert (x < SSD1306HorizontalRes && y < SSD1306VerticalRes);
	assert (x >= 0 && y >=0);

	uint8_t pixelInPage = (1 << (y % 8)); //limit the pixel from 0 to 7 with a 1 in the position 0000_0001, 0000_0010, etc

	//buffer is indexed as such
	// x straight across 0-127
	//each one of these is 8 pixels bits tall, or 1 page
	//repeat for pages 0-8
	//leading to a total size of 128*8 = 1024 page "strips" each containing the data for 8 pixels
	uint16_t bufferIndex = uint16_t(x + (y / 8) * SSD1306HorizontalRes);
//	if(bufferIndex > 1023){
//		return;
//	}
	//assert(bufferIndex < 1024);
	buffer[bufferIndex] |= pixelInPage;
	return;
}

//write a letter to the display buffer
void display::writeLetter(const uint8_t letter, const uint8_t xPos, const uint8_t yPos) {
	const uint16_t *matrix = mainFont.getLetter(letter);
	if (matrix != nullptr) { //ensure that font exists before writing
		assert(matrix !=nullptr);
		for (uint8_t i = 0; i < 16; i++) { //16 tall
			for (uint8_t j = 0; j < 12; j++) { // 12 wide
				if ((matrix[i]) & (1 << (12 - j))) {
					drawPixel(xPos + j, yPos + i);
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
	if ((xPos > SSD1306HorizontalRes) || (yPos > SSD1306VerticalRes)) {
				return;
		}
		if(xPos < 0 || yPos < 0){
			return;
		}
	for (uint8_t i = 0; i < 14; i++) { //14 tall
		for (uint8_t j = 0; j < 20; j++) { // 20 wide
			if ((symbol[i]) & (1 << (20 - j))) {
				drawPixel(xPos + j, yPos + i);
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
display::display(SPI_HandleTypeDef *hspi1I, displayQueue *displayQueueI, ssd1306Setup *setup){
	if(hspi1I == nullptr || displayQueueI== nullptr || setup == nullptr){
		NVIC_SystemReset();
	}else if(setup->dcPinI < 0 || setup->rstPinI < 0){
		NVIC_SystemReset();
	}
	assert(hspi1I != nullptr || displayQueueI!= nullptr || setup->dcPortI != nullptr || setup->rstPortI != nullptr);
	hspi1 = hspi1I;
	displayQueueInstance = displayQueueI;
	dcPortV = setup->dcPortI;
	dcPinV = setup->dcPinI;
	rstPortV =setup->rstPortI;
	rstPinV = setup->rstPinI;
	horizontalRes = setup->SSD1306HorizontalR;
	verticalRes = setup->SSD1306VerticalR;
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

void display::writeValues(uint8_t page, bool echo){
	if(echo != true && echo != false){
		return;
	}else if(page > 8 || page < 0){
		return;
	}
	assert((page >= 0) and (page < 8));
	assert(echo == true || echo == false);
    sendCommand(0x22);
    sendCommand(page);
    sendCommand(page);

    sendCommand(0x21);

    if(echo && (page == 4 || page == 5)){ //shift
        sendCommand(0x58);
        sendCommand(0x7F);
        sendData(&buffer[128 * page + 87], 39);
    }else if((page == 0 || page == 1 || page == 4 || page ==5)){ //freq
    	sendCommand(0x43);
    	sendCommand(0x7F);
    	sendData(&buffer[128 * page + 67], 60);
    }else{ //amp + wave
    	sendCommand(0x2F);
    	sendCommand(0x7F);
    	sendData(&buffer[128 * page + 47], 80);
    }
}

void display::drawWordsNorm(uint8_t row) {
	if(!(row == 0 || row==1)){
			return;
	}
	assert((row == 0 || row==1));
	//Write Freq, and Amp to the display
		for(uint8_t j = 0; j < 4;j++){
			writeLetter(freqList[j],letterPositions[j],letterPositions[row*2]);
		}
		for(uint8_t k = 0; k < 3;k++){
			writeLetter(ampList[k],letterPositions[k],letterPositions[(row*2)+1]);
		}
		if(row==1){
			writeSection(4, 0x00, 0x60);
			sendData(&buffer[(128 * 4)], 96);
			writeSection(5, 0x00, 0x60);
			sendData(&buffer[(128 * 5)], 96);
			writeSection(6, 0x00, 0x60);
			sendData(&buffer[(128 * 6)], 96);
			writeSection(7, 0x00, 0x60);
		    sendData(&buffer[(128 * 7)], 96);
			normalWriting = true;
		}

}
void display::writeSection(uint8_t page, uint8_t columnStart, uint8_t columnStop){
	if(page > 8 || page < 0){
			return;
	}else if(columnStart > SSD1306HorizontalRes || columnStop > SSD1306HorizontalRes){
		return;
	}
	assert(page >= 0 && page < 8);
	sendCommand(0x22);
	sendCommand(page);
	sendCommand(page);
	sendCommand(0x21);
	sendCommand(columnStart);
	sendCommand(columnStop);
	return;
}
void display::drawWordsShift() {
		for(uint8_t i = 0; i < 5;i++){
			writeLetter(shiftList[i],letterPositions[i],letterPositions[2]);
		}
		writeSection(4, 0x00, 0x60);
		sendData(&buffer[(128 * 4)], 96);
		writeSection(5, 0x00, 0x60);
		sendData(&buffer[(128 * 5)], 96);
		writeSection(6, 0x00, 0x60);
		sendData(&buffer[(128 * 6)], 96);
		writeSection(7, 0x00, 0x60);
	    sendData(&buffer[(128 * 7)], 96);
	    normalWriting = false;
}

void display::convertAmp(const uint16_t amp, const uint8_t Channel) {
	if(amp > 4096){
		return;
	}
	uint8_t row;
	if (Channel == 0) {
		row = 16;
	}else if(Channel == 1){
		row = 48;
	}else{
		return; //Channel is not valid
	}
	assert(row == 16 || row==48);
	assert(amp < 4096);

	uint16_t place0 = uint16_t(amp * 3300 / 4095);
	uint8_t place1 = (uint8_t) (place0 / 1000);
	uint8_t place2 = (uint8_t) ((place0 - place1 * 1000) / 100);

	writeLetter('0' + (place1), 59, row);
	writeLetter('.', 71, row);
	writeLetter('0' + (place2), 83, row);
}

void display::convertFreq(const uint32_t currentFreq, const uint8_t Channel) {
	uint8_t row;
	if(currentFreq < 1){
		return;
	}
	if (Channel == 0) { //handle ch1 and ch2 frequencies
		row = 0;
	} else if(Channel == 1){
		row = 32;
	}else{
		return;
	}
	assert(row == 0 || row==32);
	assert(currentFreq >= 1);
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
	const uint8_t freqNumberPositions[] = { 67, 79, 91, 103, 115};
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

void display::convertShift(const uint16_t signal){
		if(signal > 256 || signal < 0){
			return;
		}
		assert(signal >= 0 && signal <= 256);
		//attempting to keep as much resolution as possible
		//180 * 360 < 2^16 -1 therefore the uint16_t will not be fully used
		//but it will also allow for slightly more resolution than just whole numbers
		//uint16_t currentShift = (uint16_t)(((signal*360.0)/(double)(waveFormRes)));
		//const uint16_t angleList[9] = {0, 45, 90, 135, 180, 225, 270, 315, 360};
		//uint16_t currentShift = angleList[(uint8_t)((signal+1) / 32)];
		uint16_t currentShift =(uint16_t)(45*signal/32.0);
		if(currentShift > 360){
			return;
		}
		uint8_t finalValues[3];
		finalValues[0] = (uint8_t)(currentShift/100);
		finalValues[1] = (uint8_t)((currentShift-finalValues[0]*100) / 10);
		finalValues[2] = (uint8_t)(currentShift-finalValues[0]*100-finalValues[1]*10);
		uint8_t firstPlace = 2;
		const uint8_t shiftNumberPositions[] = {91, 103, 115};
		for (uint8_t i = 0; i < 3; i++) {
			if (finalValues[i] != 0) {
				firstPlace = i;
				break;
			}
		}
		for (uint8_t i = firstPlace; i < 3; i++) {
			writeLetter('0' + finalValues[i], shiftNumberPositions[i], 32);
		}
}
void display::displaySignalType(const WaveShape shape, const uint8_t Channel) {
	if(shape !=SINE && shape != SQUARE && shape!= PULSE && shape !=ECHO){
		return;
	}else if(Channel != 0 && Channel != 1){
		return;
	}
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
	static uint8_t currentState = 0; //state 0 = update buffer, state 1 = write top half, state 2 = write bottom half
	static displayInfoValues displayedInfo;
	static bool echo = false;
	switch(currentState){
	case(0):{
		bool newData =displayQueueInstance->dequeue(&displayedInfo);
		if (newData == true) {
			clearBuffer();
			currentState = 1;
			if(displayedInfo.Bwave==ECHO){
				echo = true;
			}else{
				echo = false;
			}
		}
		break;
	}case(1):{
		convertFreq(displayedInfo.Afrequency, 0);
		convertAmp(displayedInfo.Aamp, 0);
		displaySignalType(displayedInfo.Awave, 0);
		currentState = 2;
		break;
	}case(2):{
		if (!echo) {
			convertFreq(displayedInfo.Bfrequency, 1);
			convertAmp(displayedInfo.Bamp, 1);
			displaySignalType(displayedInfo.Bwave, 1);
		}else{
			convertShift(displayedInfo.BshiftAmount);
			assert(
					displayedInfo.Aamp
					== displayedInfo.Bamp);
			assert(
					displayedInfo.Afrequency
					== displayedInfo.Bfrequency);
		}
		currentState = 3;
		break;
	}case(3):{
		if (!echo) {
			if(normalWriting !=true){
				drawWordsNorm(1);
			}
		}else{
			if(normalWriting != false){
				drawWordsShift();
			}
		}
		currentState = 4;
		break;
	}case(4):{
		writeValues(0, echo);
		writeValues(1, echo);
		writeValues(2, echo);
		writeValues(3,echo);
		writeValues(4,echo);
		writeValues(5,echo);
		writeValues(6,echo);
		writeValues(7,echo);
		currentState = 0;
		break;
	}default:{
		currentState = 0;
	}
	}
	return;
}

