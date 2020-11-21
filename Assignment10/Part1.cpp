#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

int T, n, m;
double r, sigma, S_0, K, B;
double Simulation_Call,Simulation_Put, Adjustment_Call, Adjustment_Put, Theo_Call, Theo_Put;


//unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
unsigned seed = 3.1;
default_random_engine generator;

double get_uniform() {
std:uniform_real_distribution<double> distribution(0.0, 1.0);
	double number = distribution(generator);
	return (number);
}

double max(double a, double b) {
	return (b < a) ? a : b;
}

double N(const double& z) {
	if (z > 6.0) { return 1.0; }; // this guards against overflow 
	if (z < -6.0) { return 0.0; };
	double b1 = 0.31938153;
	double b2 = -0.356563782;
	double b3 = 1.781477937;
	double b4 = -1.821255978;
	double b5 = 1.330274429;
	double p = 0.2316419;
	double c2 = 0.3989423;
	double a = fabs(z);
	double t = 1.0 / (1.0 + a * p);
	double b = c2 * exp((-z) * (z / 2.0));
	double n = ((((b5 * t + b4) * t + b3) * t + b2) * t + b1) * t;
	n = 1.0 - b * n;
	if (z < 0.0) n = 1.0 - n;
	return n;
};


double option_price_put_black_scholes(const double& S, const double& K,const double& r,const double& sigma,const double& time) {
	double time_sqrt = sqrt(time);
	double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
	double d2 = d1 - (sigma * time_sqrt);
	return K * exp(-r * time) * N(-d2) - S * N(-d1);
};

double option_price_call_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time) {  // time to maturity 
	double time_sqrt = sqrt(time);
	double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
	double d2 = d1 - (sigma * time_sqrt);
	return S * N(d1) - K * exp(-r * time) * N(d2);
};
 
void simulation_european(int T, double r,double sigma, double S_0, double K,int n, int m, double B ) {
	double d_t, d_R, d_std;
	vector<double> S(5,0);
	
	d_t = T / (double)m;
	d_R = (r - 0.5 * pow(sigma, 2)) * d_t;
	d_std = sigma * sqrt(d_t);

	double sum_payoff_call = 0.0;
	double avg_payoff_call= 0.0;
	double sum_payoff_put = 0.0;
	double avg_payoff_put = 0.0;

	double adj_sum_call = 0.0;
	double adj_sum_put = 0.0;
	double p;

	int count = 0;

	for (int i = 0;i < n;i++) {
		S[1] = S_0;
		S[2] = S_0;
		S[3] = S_0;
		S[4] = S_0;
		double payoff_call = 0.0;
		double payoff_put = 0.0;
		for (int j = 0;j < m;j++) {
			double x = get_uniform();
			double y = get_uniform();
			double a = sqrt(-2.0 * log(x)) * cos(6.283185307999998 * y);
			double b = sqrt(-2.0 * log(x)) * sin(6.283185307999998 * y);
			S[1] = S[1] * exp(d_R + d_std * a);
			S[2] = S[2] * exp(d_R - d_std * a);
			S[3] = S[3] * exp(d_R + d_std * b);
			S[4] = S[4] * exp(d_R - d_std * b);
			for (int k = 1; k < 5; k++) {
				if (S[k] <= B) {
					S[k] = 0;
				}
			}
		}
		for (int k = 1; k < 5;k++) {
			if (S[k] > 0) {
				payoff_call = payoff_call + max(0, S[k] - K);
				payoff_put = payoff_put + max(0, K - S[k]);
				p = exp((-2) * log(S_0 / B) * log(S[k] / B) / (pow(sigma, 2.0) * T));
				adj_sum_call = adj_sum_call + max(0, S[k] - K) * (1 - p);
				adj_sum_put = adj_sum_put + max(0, K - S[k]) * (1 - p);
				count++;
			}
		}
		payoff_call = payoff_call / 4;
		sum_payoff_call = sum_payoff_call + payoff_call;
		payoff_put = payoff_put / 4;
		sum_payoff_put = sum_payoff_put + payoff_put;
	}
	avg_payoff_call = sum_payoff_call / n;
	avg_payoff_put = sum_payoff_put / n;
	Simulation_Call = avg_payoff_call / exp(r * T);
	Adjustment_Call = adj_sum_call /(count* exp(r * T));
	Simulation_Put = avg_payoff_put / exp(r * T);
	Adjustment_Put = adj_sum_put / (count* exp(r * T));
}


int main(int argc, char* argv[])
{
	sscanf(argv[1], "%d", &T);
	sscanf(argv[2], "%lf", &r);
	sscanf(argv[3], "%lf", &sigma);
	sscanf(argv[4], "%lf", &S_0);
	sscanf(argv[5], "%lf", &K);
	sscanf(argv[6], "%d", &n);
	sscanf(argv[7], "%d", &m);
	sscanf(argv[8], "%lf", &B);



	cout << "European Down-and-Out Cotinuous Barrier Options Pricing" << endl;
	cout << "Expiration Time (Years) = " <<T << endl;
	cout << "Risk Free Interest Rate = " << r << endl;
	cout << "Volatility (%age of stock value) = " << sigma * 100 << endl;
	cout << "Strike Price = " << K << endl;
	cout << "Initial Stock Price = " << S_0 << endl;
	cout << "Barrier Price = " << B << endl;
	cout << "Number of Trials = " << n << endl;
	cout << "Number of Divisions = " << m << endl;
	cout << "--------------------------------------" << endl;
	simulation_european(T, r, sigma, S_0, K, n, m, B);
	Theo_Call = option_price_call_black_scholes(S_0, K, r, sigma, T);
	Theo_Put = option_price_put_black_scholes(S_0, K, r, sigma, T);
	cout << "--------------------------------------" << endl;
	cout << "The average Call Price by explicit simulation = " << Simulation_Call << endl;
	cout << "The call price using the (1-p)-adjustment term = " << Adjustment_Call << endl;
	cout << "Theoretical Call Price = " << Theo_Call << endl;
	cout << "--------------------------------------" << endl;
	cout << "The average Put Price by explicit simulation = " << Simulation_Put << endl;
	cout << "The put price using the (1-p)-adjustment term = " << Adjustment_Put << endl;
	cout << "Theoretical Put Price = " << Theo_Put << endl;
	cout << "--------------------------------------" << endl;

}