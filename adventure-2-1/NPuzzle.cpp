#include "puzzle8.h"
#include "NPuzzle.h"

void CNPuzzle::PrintMap(BYTE *map, BYTE tiles) {
	for (BYTE row = 0; row < tiles; row++) {
		for (BYTE col = 0; col < tiles; col++) printf("%2d ", map[row * tiles + col]);
		printf("\n");
	}
	printf("\n");
}

void CNPuzzle::PrintMap(BYTE *map1, BYTE *map2, BYTE tiles) {
	for (BYTE row = 0; row < tiles; row++) {
		for (BYTE col = 0; col < tiles; col++) printf("%2d ", map1[row * tiles + col]);
		printf("\t");
		for (BYTE col = 0; col < tiles; col++) printf("%2d ", map2[row * tiles + col]);
		printf("\n");
	}
	printf("\n");
}

void CNPuzzle::PrintVector(vector<BYTE> freq) {
	for (auto it = freq.begin(); it != freq.end(); it++) printf("%d ", *it);
	printf("\n");
}

vector<BYTE> CNPuzzle::Shuffle(vector<BYTE> movefreq, BYTE *map, struct Position *pos, int tiles) {
	random_device rd;
	mt19937 gen(rd()); // rd는 srand에서 초기화하는 역할
	uniform_int_distribution<> dis(0, 3); // 0부터 3까지의 값 중 하나를 생성함.
	char direction = 0;

	struct Position temppos = { 0,0 };

	for (UINT cnt = 0; cnt < 100; cnt++) {
		movefreq = ShuffleDat(movefreq, map, pos, *pos, tiles, dis(gen));
		//direction = dis(gen);
		//temppos = *pos;
		//switch (direction) {
		//case UP:
		//	if (--(pos->_row) < 0)	++(pos->_row);
		//	else					movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		//	break;
		//case LEFT:
		//	if (--(pos->_col) < 0)	++(pos->_col);
		//	else					movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		//	break;
		//case DOWN:
		//	if (++(pos->_row) > tiles - 1)	--(pos->_row);
		//	else							movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		//	break;
		//case RIGHT:
		//	if (++(pos->_col) > tiles - 1)	--(pos->_col);
		//	else							movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		//	break;
		//}
	}

	return movefreq;
}

vector<BYTE> CNPuzzle::ShuffleDat(vector<BYTE> movefreq, BYTE *map, struct Position *pos, struct Position temppos, int tiles, char direction) {
	switch (direction) {
	case UP:
		if (--(pos->_row) < 0)	++(pos->_row);
		else					movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		break;
	case LEFT:
		if (--(pos->_col) < 0)	++(pos->_col);
		else					movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		break;
	case DOWN:
		if (++(pos->_row) > tiles - 1)	--(pos->_row);
		else							movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		break;
	case RIGHT:
		if (++(pos->_col) > tiles - 1)	--(pos->_col);
		else							movefreq = MakeFreqVector(movefreq, direction, map, *pos, temppos, tiles);
		break;
	}
	return movefreq;
}

void CNPuzzle::AutoMove(BYTE *map, struct Position *pos, int tiles, char direction) {
	struct Position temppos = *pos;
	switch (direction) {
	case UP:
		--(pos->_row);
		break;
	case LEFT:
		--(pos->_col);
		break;
	case DOWN:
		++(pos->_row);
		break;
	case RIGHT:
		++(pos->_col);
		break;
	}
	SwapVal(map + (pos->_row * tiles + pos->_col), map + (temppos._row * tiles + temppos._col));
}

BYTE *CNPuzzle::CreateMap(int tiles) {
	BYTE *map = new BYTE[tiles * tiles];
	fill_n(map, tiles * tiles, 0);
	for (BYTE idx = 1; idx < tiles * tiles; idx++) map[idx] = idx;

	return map;
}

vector<BYTE> CNPuzzle::MakeFreqVector(vector<BYTE> freq, BYTE direction, BYTE *map, struct Position pos, struct Position temppos, int tiles) {
	BYTE direct = ((direction % 2) == 0 ? ((direction / 2) == 0 ? DOWN : UP) : ((direction / 2) == 0 ? RIGHT : LEFT));

	SwapVal(map + (pos._row * tiles + pos._col), map + (temppos._row * tiles + temppos._col));
	if (freq.size() < 1)					freq.push_back(direction);
	else if (*(freq.end() - 1) == direct)	freq.pop_back();
	else									freq.push_back(direction);

	return freq;
}

void CNPuzzle::SwapVal(BYTE *val1, BYTE *val2) {
	BYTE temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

void CNPuzzle::SetMapSize() {
	printf("타일의 크기를 입력하세요(3 이상) >> ");
	ignore = scanf_s("%d",  &tiles);
}


#ifndef __FIGHT_FLAG
#define __FIGHT_FLAG

#define __VS_PLAYER 0
#define __VS_AI		1
#define __SOLOPLAY	2

#endif

template <typename A>
bool CheckClearFlag(A *a, int arr_size) {
	for (int row_idx = 0; row_idx < arr_size; row_idx++) {
		for (int col_idx = 0; col_idx < arr_size; col_idx++) {
			if (a[row_idx * arr_size + col_idx] != row_idx * arr_size + col_idx) return false;
		}
	}
	return true;
}

void CNPuzzle::Run() {
	int switch_case = 0;
	printf("vs player - 0, vs ai - 1, solo play - 2 >> ");
	scanf_s("%d", &switch_case);

	switch (switch_case) {
	case __VS_PLAYER:
		player1 = CreateMap(tiles);
		player2 = CreateMap(tiles);

		p1_pos = { 0,0 };
		p2_pos = { 0,0 };

		p1_move = Shuffle(p1_move, player1, &p1_pos, tiles);
		p2_move = Shuffle(p2_move, player2, &p2_pos, tiles);
		printf("\n");

		PrintMap(player1, player2, tiles);

		delete[] player1; player1 = nullptr; p1_move.clear();
		delete[] player2; player2 = nullptr; p2_move.clear();
		break;
	case __VS_AI:
		player1 = CreateMap(tiles);
		player2 = CreateMap(tiles);

		p1_pos = { 0,0 };
		p2_pos = { 0,0 };

		ignore = Shuffle(p1_move, player1, &p1_pos, tiles);
		p2_move = Shuffle(p2_move, player2, &p2_pos, tiles);
		printf("\n");

		PrintMap(player1, player2, tiles);

		while (!p2_move.empty()) {
			BYTE saved_move = *(p2_move.end() - 1);
			BYTE direction = saved_move % 2 == 0 ? (saved_move / 2 == 0 ? DOWN : UP) : (saved_move / 2 == 0 ? RIGHT : LEFT);
			p2_move.pop_back();
			AutoMove(player2, &p2_pos, tiles, direction);
			PrintMap(player1, player2, tiles);
			if (CheckClearFlag(player1, tiles)) {
				printf("플레이어 승\n");
				break;
			}
			if (CheckClearFlag(player2, tiles)) {
				printf("AI 승\n");
				break;
			}
			Sleep(100);
			system("cls");
		}

		delete[] player1; player1 = nullptr; p1_move.clear();
		delete[] player2; player2 = nullptr; p2_move.clear();
		break;
	case __SOLOPLAY:
		player1 = CreateMap(tiles);

		p1_pos = { 0,0 };

		PrintMap(player1, tiles);
		PrintVector(p1_move);
		printf("%d %d\n", p1_pos._row, p1_pos._col);

		delete[] player1; player1 = nullptr; p1_move.clear();
		break;
	}
}