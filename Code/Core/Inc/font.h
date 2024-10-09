/*
 * font.h
 *
 *  Created on: Oct 6, 2024
 *      Author: townl
 */

#ifndef INC_FONT_H_
#define INC_FONT_H_
#include "allIncludes.h"


class font{
private:
	//all letters
	const uint16_t zero[16] = {
	0x03F0, //001111110000,
	0x03F0, //001111110000,
	0x0C0C, //110000001100,
	0x0C0C, //110000001100,
	0x0C3C, //110000111100,
	0x0C3C, //110000111100,
	0x0CCC, //110011001100,
	0x0CCC, //110011001100,
	0x0F0C, //111100001100,
	0x0F0C, //111100001100,
	0x0C0C, //110000001100,
	0x0C0C, //110000001100,
	0x03F0, //001111110000,
	0x03F0, //001111110000,
	0x0000, //000000000000,
	0x0000  //000000000000,
	};


	const uint16_t one[16] = {
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t two[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0030, //000000110000
	0x0030, //000000110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t three[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0030, //000000110000
	0x0030, //000000110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0030, //000000110000
	0x0030, //000000110000
	0x000C, //000000001100
	0x000C, //000000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t four[16] = {
	0x0030, //000000110000
	0x0030, //000000110000
	0x00F0, //000011110000
	0x00F0, //000011110000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t five[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t six[16] = {
	0x00F0, //000011110000
	0x00F0, //000011110000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t seven[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0030, //000000110000
	0x0030, //000000110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t eight[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t nine[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0030, //000000110000
	0x0030, //000000110000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t hash[16] = {
	0x0330, //001100110000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0330, //001100110000
	0x0330, //001100110000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0330, //001100110000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capA[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capB[16] = {
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capC[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capD[16] = {
	0x0FC0, //111111000000
	0x0FC0, //111111000000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0FC0, //111111000000
	0x0FC0, //111111000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capE[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capF[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capG[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0CFC, //110011111100
	0x0CFC, //110011111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capH[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capI[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capJ[16] = {
	0x00FC, //000011111100
	0x00FC, //000011111100
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capK[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0CC0, //110011000000
	0x0CC0, //110011000000
	0x0F00, //111100000000
	0x0F00, //111100000000
	0x0CC0, //110011000000
	0x0CC0, //110011000000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capL[16] = {
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capM[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0F3C, //111100111100
	0x0F3C, //111100111100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capN[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0F0C, //111100001100
	0x0F0C, //111100001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0C3C, //110000111100
	0x0C3C, //110000111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capO[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capP[16] = {
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capQ[16] = {
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x03CC, //001111001100
	0x03CC, //001111001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capR[16] = {
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0CC0, //110011000000
	0x0CC0, //110011000000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capS[16] = {
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capT[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capU[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capV[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capW[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capX[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capY[16] = {
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t capZ[16] = {
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0030, //000000110000
	0x0030, //000000110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowA[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x000C, //000000001100
	0x000C, //000000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowB[16] = {
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0CF0, //110011110000
	0x0CF0, //110011110000
	0x0F0C, //111100001100
	0x0F0C, //111100001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0000, //000000000000
	0x0000 //000000000000
	};

	const uint16_t lowC[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowD[16] = {
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x03CC, //001111001100
	0x03CC, //001111001100
	0x0C3C, //110000111100
	0x0C3C, //110000111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowE[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowF[16] = {
	0x00F0, //000011110000
	0x00F0, //000011110000
	0x030C, //001100001100
	0x030C, //001100001100
	0x0300, //001100000000
	0x0300, //001100000000
	0x0FC0, //111111000000
	0x0FC0, //111111000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowG[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x000C, //000000001100
	0x000C, //000000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowH[16] = {
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0CF0, //110011110000
	0x0CF0, //110011110000
	0x0F0C, //111100001100
	0x0F0C, //111100001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowI[16] = {
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowJ[16] = {
	0x0030, //000000110000
	0x0030, //000000110000
	0x0000, //000000000000
	0x0000, //000000000000
	0x00F0, //000011110000
	0x00F0, //000011110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0030, //000000110000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowK[16] = {
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0CC0, //110011000000
	0x0CC0, //110011000000
	0x0F00, //111100000000
	0x0F00, //111100000000
	0x0CC0, //110011000000
	0x0CC0, //110011000000
	0x0C30, //110000110000
	0x0C30, //110000110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowL[16] = {
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowM[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0F30, //111100110000
	0x0F30, //111100110000
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowN[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0CF0, //110011110000
	0x0CF0, //110011110000
	0x0F0C, //111100001100
	0x0F0C, //111100001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowO[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowP[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowQ[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03CC, //001111001100
	0x03CC, //001111001100
	0x0C3C, //110000111100
	0x0C3C, //110000111100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x000C, //000000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowR[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0CF0, //110011110000
	0x0CF0, //110011110000
	0x0F0C, //111100001100
	0x0F0C, //111100001100
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowS[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0C00, //110000000000
	0x0C00, //110000000000
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x000C, //000000001100
	0x000C, //000000001100
	0x0FF0, //111111110000
	0x0FF0, //111111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowT[16] = {
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0FC0, //111111000000
	0x0FC0, //111111000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x030C, //001100001100
	0x030C, //001100001100
	0x00F0, //000011110000
	0x00F0, //000011110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowU[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C3C, //110000111100
	0x0C3C, //110000111100
	0x03CC, //001111001100
	0x03CC, //001111001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowV[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowW[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0CCC, //110011001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowX[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0330, //001100110000
	0x0330, //001100110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0330, //001100110000
	0x0330, //001100110000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowY[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x0C0C, //110000001100
	0x03FC, //001111111100
	0x03FC, //001111111100
	0x000C, //000000001100
	0x000C, //000000001100
	0x03F0, //001111110000
	0x03F0, //001111110000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t lowZ[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0030, //000000110000
	0x0030, //000000110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0FFC, //111111111100
	0x0FFC, //111111111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t Dash[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0FFE, //111111111110
	0x0FFE, //111111111110
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t Decimal[16] = {
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x0000, //000000000000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x03C0, //001111000000
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t percent[16] = {
	0x0F00, //111100000000
	0x0F0C, //111100001100
	0x0F0C, //111100001100
	0x0F30, //111100110000
	0x0030, //000000110000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0300, //001100000000
	0x0300, //001100000000
	0x0C00, //110000000000
	0x0C3C, //110000111100
	0x003C, //000000111100
	0x003C, //000000111100
	0x003C, //000000111100
	0x0000, //000000000000
	0x0000  //000000000000
	};

	const uint16_t verticalBar[16] = {
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x00C0, //000011000000
	0x0000, //000000000000
	0x0000  //000000000000
	};


	uint32_t squareWaveVis[14] = {
	0xFFC01, //11111111110000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x80401, //10000000010000000001
	0x807FF, //10000000011111111111
	};


	uint32_t pulseWaveVis[14] = {
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0x0600, //00000000011000000000
	0xFFFFF, //11111111111111111111
	};

	uint32_t sineWaveVis[14] = {
	0x0000, //00000000000000000000
	0xE000, //00001110000000000000
	0x1F000, //00011111000000000000
	0x31800, //00110001100000000000
	0x31800, //00110001100000000000
	0x60C00, //01100000110000000000
	0x60C01, //01100000110000000001
	0xC0603, //11000000011000000011
	0x80306, //10000000001100000110
	0x0106, //00000000000100000110
	0x018C, //00000000000110001100
	0x00F8, //00000000000011111000
	0x0070, //00000000000001110000
	0x0000, //00000000000000000000
	};

	const uint16_t *fontMap[128] = {0}; //ASCII table
	void initializeFontMap();
public:
	font();
	const uint16_t* getLetter(uint8_t letter);
	const uint32_t* getSineVis();
	const uint32_t* getSquareVis();
	const uint32_t* getPulseVis();
};

#endif /* INC_FONT_H_ */
