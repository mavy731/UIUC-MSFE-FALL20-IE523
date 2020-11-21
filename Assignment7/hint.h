/*
 *  alice_and_bob.h
 *  Loosing as little as possible
 *
 *  Created by Ramavarapu Sreenivas on 9/2/12.
 *  Copyright 2012 University of Illinois at Urbana-Champaign. All rights reserved.
 *
 */
#ifndef ALICE_AND_BOB
#define ALICE_AND_BOB

#include <cmath>
#include <cstdlib>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;
vector<vector <int> > tmp (1000, vector<int>(1000,-1));

unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator;

class I_have_nothing_apropos_for_this_class
{
private:
	double alice_probability, bob_probability;
	
	// private member function: uniform RV generator
	double get_uniform()
	{
		// write the appropriate code here
		uniform_real_distribution<double> distribution(0.0, 1.0);
		double number = distribution(generator);
		return (number);
	}
	
	// private member function: nCi (i.e. n-take-i) 
	int take(int n, int i)
	{
		// write a **RECURSIVE** implementation of n-take-i. 
		// If you made it non-recurisive (i.e. n!/((n-i)!i!)) -- it 
		// will take too long for large sizes 
		int ans = 0;
		if (i == 0) {
			return 1;
		}
		else if (i == 1) {
			return n;
		}
		else if (n == i) {
			return 1;
		}
		else if (tmp[n][i] >= 0) {
			return tmp[n][i];
		}
		else {
			ans = n * take(n - 1, i - 1)/i;
			tmp[n][i] = ans;
			return ans;
		}
	}
	
	// this routine implements the probability that Alice has more 
	// heads than Bob after n-many coin tosses
	double theoretical_value(double q, double p, int n)
	{
		// implement equation 1.1 of Addona-Wagon-Wilf paper
		double ans = 0.0;
		double term1 = 0.0;
		for (int r = 0;r <= n;r++) {
			int s = r+1;
			double term2 = 0.0;
			for (;s <= n;s++) {
				term2 =term2+ take(n, s) * pow(q, s) * pow(1-q, n - s);
			}
			term1 = take(n, r) * pow(p, r) * pow(1 - p, n - r)*term2;
			ans = ans + term1;
		}
		return ans;
	}

public: 
	// public function: 
	void set_probability(double alice_p, double bob_p)
	{
		alice_probability = alice_p;
		bob_probability = bob_p;
	}
	
	// probability of Alice winning the game.
	double simulated_value(int number_of_coin_tosses_in_each_game, int no_of_trials)
	{
		int no_of_wins_for_alice = 0;
		for (int i = 0; i < no_of_trials; i++) 
		{
			int number_of_heads_for_alice = 0;
			int number_of_heads_for_bob = 0;
			for (int j = 0; j < number_of_coin_tosses_in_each_game; j++) 
			{
				if (get_uniform() < alice_probability) 
					number_of_heads_for_alice++;
				if (get_uniform() < bob_probability)
					number_of_heads_for_bob++;
			}
			if (number_of_heads_for_alice > number_of_heads_for_bob)
				no_of_wins_for_alice++;
		}
		return (((double) no_of_wins_for_alice)/((double) no_of_trials));
	}
		
	int search_result()
	{
		// implememt a discrete-search procedure for the optimal n-value. 
		// start with n = 1 and find the discrete-value of n that has 
		// the largest probability for Alice winning.  Why would this work?
		// See Theorem 2.2 of the paper for the reason!
		int i = 1;
		double current = 0.0;
		double next = 0.0;
		current = theoretical_value(alice_probability, bob_probability, i);
		next= theoretical_value(alice_probability, bob_probability, i+1);

		while (next >= current) {
			i++;
			current =next;
			next = theoretical_value(alice_probability, bob_probability, i + 1);
		}
		return i;
	}

	void print_ans() {
		ofstream myout("C:/Users/mavy7/Box/2020-2021 SEM A/IE523 Financial Computing/Assignments/Assignment #7/ans.txt");
		double q = alice_probability;
		double p = bob_probability;
		for (int i = 1;i < 40;i++) {
			double a, b;
			a = simulated_value(i, 1000000);
			b= theoretical_value(q, p, i);
			myout << i << "," << a << "," << b << endl;
		}
	}


};
#endif









