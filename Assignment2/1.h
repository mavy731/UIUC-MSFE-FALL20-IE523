/*
 *  sudoku.h
 *  Sudoku
 *  Created by Prof. Ramavarapu Sreenivas 
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
 *  Modified by Yue Ma for course IE523 (MSFE FALL20) Assignment #2
*/

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using std::vector;
using namespace std;
class Sudoku
{
	// Private
	int puzzle[9][9];

	// Private member function that checks if it is valid
	bool safe(int row, int col) {
		unordered_map<int, int>
			R[9], C[9], B[3][3];
		for (int i = 0; i < 9;i++) {
			for (int j = 0; j < 9; j++) {
				R[i][puzzle[i][j]] += 1;
				C[j][puzzle[i][j]] += 1;
				B[i / 3][j / 3][puzzle[i][j]] += 1;

				if (B[i / 3][j / 3][puzzle[i][j]] > 1 || C[j][puzzle[i][j]] > 1 || R[i][puzzle[i][j]] > 1) {
					return false;
				}
			}
		}
		return true;
	}

public:
		// Public member function that reads the incomplete puzzle
		// we are not doing any checks on the input puzzle -- that is,
		// we are assuming they are indeed valid
		void read_puzzle(int argc, char* const argv[])
		{
			// write code that reads the input puzzle using the 
			// guidelines of figure 23 of the bootcamp material
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

		// Public member function that prints the puzzle when called
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

		// Public member function that (recursively) implements the brute-force 
		// search for possible solutions to the incomplete Sudoku puzzle
		bool Solve(int row, int col)
		{
			// this part of the code identifies the row and col number of the 
			// first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
			// no zeros, the variable row will be 9 => the puzzle is done, as 
			// each entry is row-, col- and block-valid...
			if (row == 9) {
				return true;
			}
			int i=row, j=col;
			if (col == 8) {
				 i = row++;
				 j = 0;
			}
			for (; i < 9;i++) {
				for (;j < 9;j++) {
					if (puzzle[i][j] == 0) {
						goto mark;
					}
				}
			}

		mark:
			// use the pseudo code of figure 3 of the description
			for (int k = 1; k < 10; k++) {
				puzzle[i][j] = k;
				if (Solve(i, j) && safe(i,j)) {
					return true;
				}
				puzzle[i][j] = 0;
			}
			return 0;
		}
};

#endif