//https://www.electro-tech-online.com/attachments/font-viewer-5x7-png.113104/
//https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
#ifndef fontFile
#define fontFile
#include "allIncludes.h"


const uint16_t  zero[] = {
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


const uint16_t one[] = {
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

const uint16_t two[] = {
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

const uint16_t three[] = {
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

const uint16_t four[] = {
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

const uint16_t five[] = {
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

const uint16_t six[] = {
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

const uint16_t seven[] = {
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

const uint16_t eight[] = {
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

const uint16_t nine[] = {
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

const uint16_t hash[] = {
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

const uint16_t capA[] = {
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

const uint16_t capB[] = {
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

const uint16_t capC[] = {
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

const uint16_t capD[] = {
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

const uint16_t capE[] = {
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

const uint16_t capF[] = {
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

const uint16_t capG[] = {
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

const uint16_t capH[] = {
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

const uint16_t capI[] = {
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

const uint16_t capJ[] = {
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

const uint16_t capK[] = {
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

const uint16_t capL[] = {
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

const uint16_t capM[] = {
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

const uint16_t capN[] = {
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

const uint16_t capO[] = {
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

const uint16_t capP[] = {
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

const uint16_t capQ[] = {
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

const uint16_t capR[] = {
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

const uint16_t capS[] = {
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

const uint16_t capT[] = {
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

const uint16_t capU[] = {
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

const uint16_t capV[] = {
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

const uint16_t capW[] = {
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

const uint16_t capX[] = {
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

const uint16_t capY[] = {
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

const uint16_t capZ[] = {
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

const uint16_t lowA[] = {
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

const uint16_t lowB[] = {
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

const uint16_t lowC[] = {
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

const uint16_t lowD[] = {
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

const uint16_t lowE[] = {
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

const uint16_t lowF[] = {
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

const uint16_t lowG[] = {
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

const uint16_t lowH[] = {
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

const uint16_t lowI[] = {
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

const uint16_t lowJ[] = {
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

const uint16_t lowK[] = {
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

const uint16_t lowL[] = {
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

const uint16_t lowM[] = {
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

const uint16_t lowN[] = {
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

const uint16_t lowO[] = {
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

const uint16_t lowP[] = {
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

const uint16_t lowQ[] = {
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

const uint16_t lowR[] = {
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

const uint16_t lowS[] = {
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

const uint16_t lowT[] = {
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

const uint16_t lowU[] = {
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

const uint16_t lowV[] = {
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

const uint16_t lowW[] = {
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

const uint16_t lowX[] = {
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

const uint16_t lowY[] = {
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

const uint16_t lowZ[] = {
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

const uint16_t Dash[] = {
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

const uint16_t Decimal[] = {
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

const uint16_t percent[] = {
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

const uint16_t verticalBar[] = {
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





#endif