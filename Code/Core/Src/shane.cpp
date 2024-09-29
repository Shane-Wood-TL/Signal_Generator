/*
 * shane.cpp
 *
 *  Created on: Sep 24, 2024
 *      Author: townl
 */

#include "allIncludes.h"






void display::initDisplay(){

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
	sendCommand(0x12);  //Set COM Pins hardware configuration, 0x02 for 128x32 and 0x12 for 128x64
	sendCommand(0x81);  //Set Contrast Control
	sendCommand(0x9F);  //Set Contrast Control Value from 0x00 to 0xFF minimum to maximum
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
void display::sendCommand(uint8_t command){
	HAL_I2C_Mem_Write(hi2c1,SSD1306Address,0x00,1,&command,1,HAL_MAX_DELAY);

}

//set write data to the display
void display::sendData(uint8_t *data, size_t len){
	HAL_I2C_Mem_Write(hi2c1,SSD1306Address,0x40,1,data,len,HAL_MAX_DELAY);
}

//draw a pixel to the display buffer
void display::drawPixel(uint8_t x, uint8_t y,bool color){
    if (x >= SSD1306HorizontalRes or y >= SSD1306VerticalRes){
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
void display::writeLetter(uint8_t letter, uint8_t xPos, uint8_t yPos){
	    const uint16_t* matrix = getLetter(letter);
	    for (int i = 0; i < 16; i++) { //16 tall
	        for (int j = 0; j < 12; j++) { // 12 wide
	            if ((matrix[i]) & (1 << (12 - j))) {
	                drawPixel(xPos+j,yPos+i,true);
	            }
	        }
	    }
	return;
}

//get a letter from the font
const uint16_t* display::getLetter(uint8_t letter){
    return fontMap[(int)letter];
}

//empties buffer so that new data can be put into it
void display::clearBuffer(){
	for(uint16_t i = 0; i <1024;i++){
		buffer[i] = 0;
	}
	return;
}


//set up the display
display::display(I2C_HandleTypeDef *hi2c1I, displayQueue *displayQueueI) {
    hi2c1 = hi2c1I;
    displayQueueInstance = displayQueueI;
    initDisplay();
    initializeFontMap();
}


//writes buffer to the display
void display::writeBuffer(){
    for (uint8_t i = 0; i < 8; i++) {  // Send each page
        sendCommand(0xB0 + i);  // Set page start address
        sendCommand(0x00);      // Set lower column address
        sendCommand(0x10);      // Set higher column address

        sendData(&buffer[128 * i], 128);
    }
    return;
}



void display::drawWords(){
		writeLetter('F',0,0);
		writeLetter('r',15,0);
		writeLetter('e',31,0);
		writeLetter('q',47,0);

		writeLetter('A',0,15);
		writeLetter('m',15,15);
		writeLetter('p',31,15);

		writeLetter('F',0,31);
		writeLetter('r',15,31);
		writeLetter('e',31,31);
		writeLetter('q',47,31);

		writeLetter('A',0,47);
		writeLetter('m',15,47);
		writeLetter('p',31,47);
}

//map the letters to the consts in 16pixelFont.h
void display::initializeFontMap(){
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

void display::getNewValues(){

}

dacDriver::dacDriver(dacSetup *dacValues){
	hdac = dacValues->hdacI;
	DacChannel = dacValues->DacChannel1I;
	timerInstance = dacValues->timer1I;
	signalQueueInstance = dacValues->channel1I;

	//ensure that something is in current signal
	HAL_DAC_Start_DMA(hdac, DacChannel, (&currentSignal)->signalLocations, scopeRes, DAC_ALIGN_12B_R);
}

void dacDriver::checkQueue(){
	if(signalQueueInstance->dequeue(&currentSignal)){
			setReload(); //set new period
	}
}

void dacDriver::setReload(){
	currentReloadValue = (uint32_t) FCLK/((timerPSC+1)*(currentSignal.frequency)*scopeRes);
	//currentReloadValue = 1000;
	//timerInstance->Init.AutoReloadPreload = currentReloadValue;
	__HAL_TIM_SET_AUTORELOAD(timerInstance,currentReloadValue);
}

signalInfo* dacDriver::getSignalInfo(){
	return &currentSignal; //returns signal that is currently being displayed
}



outputDriver::outputDriver(dacDriver *DACchannel1I,dacDriver *DACchannel2I, dacSetup *DACchannel1SetupI, dacSetup *DACchannel2SetupI, displayQueue *displayInfoQI){
	DACChannel1Setup = DACchannel1SetupI;
	DACChannel2Setup = DACchannel2SetupI;
	DACchannel1=DACchannel1I;
	DACchannel2=DACchannel2I;


	update();


	HAL_TIM_Base_Start(DACChannel1Setup->timer1I);
	HAL_TIM_Base_Start(DACChannel2Setup->timer1I);
	//non hal method
//	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
//	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
//	TIM2->CR1 |= TIM_CR1_CEN;
//	TIM6->CR1 |= TIM_CR1_CEN;
}

void outputDriver::update(){
	DACchannel1->checkQueue();
	DACchannel2->checkQueue();
	//displayInfo toWrite = {DACchannel1->getSignalInfo(),DACchannel2->getSignalInfo()};
	//displayInfoQ->enqueue(toWrite);
}
