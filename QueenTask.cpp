/**
 * QueenTask.cpp - программа для нахождения расстановки n не бьющих друг друга
 * ферзей на шахматной доске размером n x n
 *
 * Copyright (c) 2021, Vladislav Shkut <shkut@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <iostream>
#include <fstream>

using namespace std;

//y - vertical
//A[y] - gorizontal
bool IsAvailablePosition(int x, int y, int* queenPositions)
{
	for (int i = 1; queenPositions[i] != 0; i++) {
		if ((x == queenPositions[i]) || (x + y == queenPositions[i] + i) || (x - y == queenPositions[i] - i)) {
			return false;
		}
	}
    return true;
}

void FindLayout(int* queenPositions, int* checkedPositions, int yStartIndex, int xStartIndex, int columnNumber, int lineNumber)
{
	bool positionFound = false;
	// проверяем все клетки
    for (int y = yStartIndex; y <= columnNumber; y++) {
		positionFound = false;
		for (int x = xStartIndex + 1; x <= lineNumber; x++) {
			// если доступна
			if (IsAvailablePosition(x, y, queenPositions)) {
				// то ставим нового ферзя
				queenPositions[y] = x;
				// и запоминаем проверенные клетки
				checkedPositions[y] = x;
				positionFound = true;
				break;
			}
		}
		// если недоступна
		if (!positionFound) {
			if (y - 1 == 0) throw -1;
			// снимаем предыдущего ферзя
			queenPositions[y - 1] = 0;
			// проверяем клетки, пропуская уже проверенные
			int uncheckedStartXIndex = checkedPositions[y - 1];
			while (queenPositions[y] == 0 && uncheckedStartXIndex <= lineNumber) {
				FindLayout(queenPositions, checkedPositions, y - 1, uncheckedStartXIndex, y - 1, lineNumber);
				// снова пытаемся поставить текущего ферзя
				FindLayout(queenPositions, checkedPositions, y, 0, y, lineNumber);
			}
			if (queenPositions[y] == 0) throw - 1;
		}
    }
}

int main()
{
	ifstream fin("input.txt");
	int n;
	fin >> n;
	fin.close();

	int* queenPositions = new int[n + 1];
	int* checkedPositions = new int[n + 1];

	for (int i = 1; i <= n; i++) {
		queenPositions[i] = 0;
		checkedPositions[i] = 0;
	}

	ofstream fout("output.txt");
	try
	{
		FindLayout(queenPositions, checkedPositions, 1, 0, n, n);
	}
	catch (int a)
	{
		fout << -1;
		fout.close();

		delete[] queenPositions;
		delete[] checkedPositions;

		return 0;
	}

	for (int i = 1; i <= n; i++) {
		fout << i << " " << queenPositions[i] << " ";
	}
	fout.close();

	delete[] queenPositions;
	delete[] checkedPositions;
	
	return 0;
}
