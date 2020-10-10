#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <algorithm>
using std::vector;
using namespace std;
class Sudoku {
	int puzzle[9][9];
	
	bool Empty(int& row, int& col) { 
		for (row = 0; row < 9; row++)
			for (col = 0; col < 9; col++)
				if (puzzle[row][col] == 0) 
					return true;
		return false;
	}

	bool Valid(int row, int col, int k) {
		for (int i= 0; i < 9; i++)
			if (puzzle[i][col]== k)
				return false;
			else if(puzzle[row][i] == k)
				return false;
		int BoxRow = row - row % 3;
		int BoxCol = col - col % 3;
		for (int i = 0;i < 3;i++) {
			for (int j = 0; j < 3; j++) {
				if (k == puzzle[BoxRow+i][BoxCol+j]) {
					return false;
				}
			}
		}
		return true;
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
				puzzle[i][j] = P[position];
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
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					std::cout << puzzle[i][j] << " ";
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
		if (!Empty(row, col))
			return true;
		for (int k = 1; k < 10; k++) {
			if (Valid(row,col,k)) {
				puzzle[row][col] = k;
				if (Solve()) 
					return true;
				puzzle[row][col] = 0;
			}
		}
		return false;
	}

	int ans=0;

	void alternate_Solve() {
		int row, col;
		if (!Empty(row, col)) {
			ans++;
			cout << "Solution #" << ans << endl;
			print_puzzle();
			return;
		}
		int m = row, n = col;
		for (int k = 1; k < 10; k++) {
			if (Valid(m, n, k)) {
				puzzle[m][n] = k;
				alternate_Solve();
				puzzle[m][n] = 0;
			}
		}
		return;
	}
};
#endif
