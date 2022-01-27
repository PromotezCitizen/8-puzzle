#define _CRT_SECURE_NO_WARNINIGS

#include "puzzle8.h"
#include "NPuzzle.h"

#include <iostream>
#include <stdlib.h>
#include <random>

typedef unsigned char BYTE;
using namespace std;

void SwapVal(BYTE *val1, BYTE *val2) {
	BYTE temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

void PrintMap(BYTE* map, BYTE tiles) {
	for (BYTE row = 0; row < tiles; row++) {
		for (BYTE col = 0; col < tiles; col++) printf("%2d ", map[row * tiles + col]);
		printf("\n");
	}
	printf("\n");
}

void PrintVector(vector<BYTE> freq) {
	for (auto it = freq.begin(); it != freq.end(); it++) printf("%d ", *it);
	printf("\n");
}

vector<BYTE> MakeFreqVector(vector<BYTE> freq, BYTE direction, BYTE *map, struct Position pos, struct Position temppos, int tiles);
vector<BYTE> Shuffle(vector<BYTE> movefreq, BYTE* map, struct Position *pos, int tiles) {
	random_device rd;
	mt19937 gen(rd()); // rd는 srand에서 초기화하는 역할
	uniform_int_distribution<> dis(0, 3); // 0부터 3까지의 값 중 하나를 생성함.
	char direction = 0;

	struct Position temppos = { 0,0 };

	for (UINT cnt = 0; cnt < 100; cnt++) {
		direction = dis(gen);
		temppos = *pos;
		switch (direction) {
		case UP:
			if (--(pos->_row) < 0)	++(pos->_row);
			else				movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
			break;
		case LEFT:
			if (--(pos->_col) < 0) ++(pos->_col);
			else				movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
			break;
		case DOWN:
			if (++(pos->_row) > tiles - 1) --(pos->_row);
			else						movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
			break;
		case RIGHT:
			if (++(pos->_col) > tiles - 1) --(pos->_col);
			else						movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
			break;
		}
	}

	return movefreq;
}

BYTE *CreateMap(int tiles) {
	BYTE *map = new BYTE[tiles * tiles];
	fill_n(map, tiles * tiles, 0);
	for (BYTE idx = 1; idx < tiles * tiles; idx++) map[idx] = idx;

	return map;
}

vector<BYTE> MakeFreqVector(vector<BYTE> freq, BYTE direction, BYTE* map, struct Position pos, struct Position temppos, int tiles) {
	BYTE direct = ((direction % 2) == 0 ? ((direction / 2) == 0 ? DOWN : UP) : ((direction / 2) == 0 ? RIGHT : LEFT));

	SwapVal(map + (pos._row * tiles + pos._col), map + (temppos._row * tiles + temppos._col));
	if (freq.size() < 1)					freq.push_back(direction);
	else if (*(freq.end() - 1) == direct)	freq.pop_back();
	else									freq.push_back(direction);

	return freq;
}

int main() {

	CNPuzzle npuzzle;

	npuzzle.SetMapSize();
	npuzzle.Run();
	//int tiles;
	//ignore = scanf_s("%d", &tiles);

	//BYTE *map = CreateMap(tiles);

	//struct Position pos = { 0,0 };
	//
	//vector<BYTE> movefreq = Shuffle(movefreq, map, &pos, tiles);
	//printf("\n");

	//PrintMap(map, tiles);

	//PrintVector(movefreq);

	//printf("%d %d\n", pos._row, pos._col);

	//delete[] map;
	//map = nullptr;
}