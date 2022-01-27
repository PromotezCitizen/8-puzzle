#pragma once
#define _CRT_SECURE_NO_WARNINIGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <random>
#include <Windows.h >

typedef unsigned char BYTE;
typedef unsigned int UINT;

using namespace std;

#ifndef __POSITION
#define __POSITION
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

struct Position {
	int _row = 0;
	int _col = 0;
};
#endif