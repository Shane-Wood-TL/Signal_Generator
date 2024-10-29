/*
 * font.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: townl
 */


#include "allIncludes.h"


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
