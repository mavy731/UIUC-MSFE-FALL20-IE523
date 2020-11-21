/*
 *  card_game.h
 *  Card Game
 *
 *  Created by Ramavarapu Sreenivas  
*/

#ifndef	CARDGAME_H
#define CARDGAME_H
#include <algorithm>
#include <vector>

using namespace std;
vector<double> tmp(100, -1.0);
vector<vector<double>> save(100, tmp);


double value(int r, int b)
{
	double ans;
	if (0 == r)
		return ((double)b);
	if (0 == b)
		return (0);
	if (save[r][b]>=0.0) {
		ans = save[r][b];
	}
	else {
		double term1 = ((double)r / (r + b)) * value(r - 1, b);
		double term2 = ((double)b / (r + b)) * value(r, b - 1);
		ans = max((term1 + term2), (double)(b - r));
		save[r][b] = ans;
	}
	
	return ans;
}
#endif