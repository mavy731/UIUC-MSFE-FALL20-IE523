// Soduku Solver using Brute-Force Search implemted using 
// recursion.
// Written for IE523: Financial Computation by Prof. Sreenivas
// and GE523: Discrete Event Systems
//
#include <iostream>
#include "sudoku1.h"
	
int main (int argc, char * const argv[]) 
{
	Sudoku x;
	x.read_puzzle(argc, argv);
	x.print_puzzle();
	//x.Solve();
	x.alternate_Solve();
	//x.print_puzzle();
	
    return 0;
}
