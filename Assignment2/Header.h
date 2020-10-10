#pragma once
#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using std::vector;
using namespace std;
class Sudoku {
	int grid[9][9];
#define N 9

	bool isPresentInCol(int col, int num) { //check whether num is present in col or not
		for (int row = 0; row < N; row++)
			if (grid[row][col] == num)
				return true;
		return false;
	}
	bool isPresentInRow(int row, int num) { //check whether num is present in row or not
		for (int col = 0; col < N; col++)
			if (grid[row][col] == num)
				return true;
		return false;
	}
	bool isPresentInBox(int boxStartRow, int boxStartCol, int num) {
		//check whether num is present in 3x3 box or not
		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				if (grid[row + boxStartRow][col + boxStartCol] == num)
					return true;
		return false;
	}

	bool findEmptyPlace(int& row, int& col) { //get empty location and update row and column
		for (row = 0; row < N; row++)
			for (col = 0; col < N; col++)
				if (grid[row][col] == 0) //marked with 0 is empty
					return true;
		return false;
	}
	bool isValidPlace(int row, int col, int num) {
		//when item not found in col, row and current 3x3 box
		return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3,
			col - col % 3, num);
	}

public:
	void read_puzzle(int argc, char* const argv[])
	{
		int m;
		vector <int> P;
		if (argc > 1) {
			ifstream input_file(argv[1]);
			if (input_file.is_open()) {
				while (input_file >> m) {
					P.push_back(m);
				}
			}
		}
		for (int i = 0;i < 9;i++) {
			for (int j = 0; j < 9; j++) {
				int position = i * 9 + j;
				grid[i][j] = P[position];
			}
		}
	}

	void print_puzzle()
	{
		std::cout << std::endl << "Board Position" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((grid[i][j] >= 1) && (grid[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					std::cout << grid[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					std::cout << "X ";
				}
			}
			std::cout << std::endl;
		}
	}

	bool Solve() {
		int row, col;
		if (!findEmptyPlace(row, col))
			return true; //when all places are filled
		for (int num = 1; num <= 9; num++) { //valid numbers are 1 - 9
			if (isValidPlace(row, col, num)) { //check validation, if yes, put the number in the grid
				grid[row][col] = num;
				if (Solve()) //recursively go for other rooms in the grid
					return true;
				grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
			}
		}
		return false;
	}
};
#endif
