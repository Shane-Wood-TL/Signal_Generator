/**
 * @file display.h
 * @brief This file contains the definition of the display class
 * @author Shane Wood
 * @date Sep 15, 2024
 */

#ifndef INC_SHANE_DISPLAY_H_
#define INC_SHANE_DISPLAY_H_

#include "allIncludes.h"

//SSD1306 setup
#define SSD1306VerticalRes 64           //64 pixels tall
#define SSD1306HorizontalRes 128    //128 pixels across


/**
 * @class display
 * @brief Driver for the SSD1306 display.
 * 
 * @details This class can set up and draw to the display using a buffer and phased execution.
 */
class display{
private:
	SPI_HandleTypeDef *hspi1; ///< SPI Instance 
	displayQueue *displayQueueInstance; ///< display queue instance
	uint8_t buffer[1024] = {0}; ///< display buffer
	font mainFont; ///< font class instance
	const uint8_t letterPositions[5] = {0,16,32,48,64}; ///< constant positions of letters written to the screen
	const uint8_t freqList[4] = {'F', 'r','e','q'}; ///< Letter list for F,r,e,q
	const uint8_t ampList[3] = {'A','m','p'}; ///< Letter list for A,m,p
	const uint8_t shiftList[5] = {'S', 'h','i','f','t'};///< Letter list for S,h,i,f,t
	 GPIO_TypeDef *dcPortV; ///< Port for the D/C pin
	 uint8_t dcPinV;///< pin number for the D/C pin
	 GPIO_TypeDef *rstPortV; ///< Port for the reset pin
	 uint8_t rstPinV; ///< pin for the reset pin
	 bool normalWriting = true; ///< detect if shift or freq + amp is written for ch2
	 uint8_t horizontalRes; ///< horizontal res of the screen
	 uint8_t verticalRes; ///< vertical res of the screen
	/**
	 *@brief set up the i2c display (ssd1306)
	*/
	void initDisplay();

	/**
	 * @brief Send commands to the display
	 *
	 * @param command a uint8_t that is the command that will be written to the SPI bus
	 */
	void sendCommand(uint8_t command);

	/**
	 * @brief Write data to the display
	 * 
	 * @param data a uint8_t that is data that will be written to the display using SPI
	 * @param len a uint16_t that is the len of the data being written
	 */
	void sendData(uint8_t *data, uint16_t len);

	/**
	 * @brief Draw pixel to the display buffer
	 * 
	 * @param x a const uint8_t that is the horizontal position of the pixel
	 * @param y a const uint8_t that is the vertical position of the pixel
	 * @param color a const bool that chooses to add or remove a pixel from the buffer
	 */
	void drawPixel(const uint8_t x, const uint8_t y);

	/**
	 * @brief Write a letter to the display buffer
	 * 
	 * @param letter a const uint8_t that is the ascii value for a letter
	 * @param xPos a const uint8_t that is the starting horizontal position for the letter
	 * @param yPos a const uint8_t that is the starting vertical position for the letter
	 */
	void writeLetter(const uint8_t letter, const uint8_t xPos, const uint8_t yPos);


	/**
	 * @brief Write a symbol to the display buffer
	 * 
	 * @param symbol a const uint32_t that is the pixel data for a symbol
	 * @param xPos a const uint8_t that is the starting horizontal position for the letter
	 * @param yPos a const uint8_t that is the starting vertical position for the letter
	 */
	void writeSymbol(const uint32_t *symbol, const uint8_t xPos, const uint8_t yPos);


	/**
	 * @brief Clears the display buffer so that new data can be put into it
	 */
	void clearBuffer();

	/**
	 * @brief Write the entire buffer to the display
	 */
	void writeBuffer();

	/**
	 * @brief Write the specified page to the display
	 *
	 * @parma page a uint8_t for the page to be written 0-7
	 */
	void writeValues(uint8_t page, bool echo);


	/**
	 * @brief Draw freq, shift for ch1 and ch2 to the display
	 */
	void drawWordsNorm(uint8_t row);

	/**
	 * @brief Draw freq, shift for ch1 and shift for ch2 to the display
	 */
	void drawWordsShift();

	/**
	 * @brief Convert the value for freq to ASCII values and write them to the buffer.
	 * 
	 * @param currentFreq A const uint32_t that is the current frequency as a number.
	 * @param Channel A const uint8_t that specifics if the frequency is being converted for channel 1 or 2.
	 */
	void convertFreq(const uint32_t currentFreq, const uint8_t Channel);

	/**
	 * @brief Convert the value for Amplitude to ASCII values and write them to the buffer.
	 * 
	 * @param amp A const uint16_t that is the current amplitude as a number (0-4095).
	 * @param Channel A const uint8_t that specifics if the amplitude is being converted for channel 1 or 2
	 */
	void convertAmp(const uint16_t amp, const uint8_t Channel);

	/**
	 * @brief Draw the waveshape to the display
	 * 
	 * @param shape A constant WaveShape that will have it's symbol added to the display buffer
	 * @param Channel A const uint8_t that specifics if the amplitude is being converted for channel 1 or 2
	 */
	void displaySignalType(const WaveShape shape, const uint8_t Channel);

	/**
	 * @brief Convert the 0-255 for shift to degrees display
	 * 
	 * @param signal A const uint8_t that is the current shift in steps
	 */
	void convertShift(const uint16_t signal);

	/**
	 * @brief Write only a section to the display
	 *
	 * @param page a uint8_t The page [0-7] that will have data written to it
	 * @param columnStart a uint8_t the column where data will start being written [0-127]
	 * @param columnStart a uint8_t the column where data will stop being written [0-127]
	 */
	void writeSection(uint8_t page, uint8_t columnStart, uint8_t columnStop);
public:
	/**
	 * @brief Constructs a display object.
	 *
	 * @param hspi11I a SPI_HandleTypeDef, the spi bus that the display is using
	 * @param displayQueueI a displayQueue, the location where the display will get data to write to the screen
	 * @param dcPortI a GPIO_Typedef, the port where the Data/command pin is located
	 * @param dcPinI a uint32_t bit mask for the pin number for D/C
	 * @param rstPortI a GPIO_Typedef, the port where the reset pin is located
	 * @param rstPinI a uint32_t bit mask for the pin number for rst
	 */
	display(SPI_HandleTypeDef *hspi1I, displayQueue *displayQueueI, ssd1306Setup *setup);


	/**
	 * @brief Updates the display from the queue
	 * 
	 * @details uses phased execution to update the buffer, then write the top half of the display,
	 * then the bottom half of the display. This process repeats as long as there is new data from the queue
	 */
	void getNewValues();

};

#endif /*INC_SHANE_DISPLAY_H_ */
