/* Name: Sarah Huang
 * Date: 10/17/21
 * Program: keno.cpp
 * Purpose: Simulate the Keno betting game and utilize fraction.cpp
 */

#include <vector>
#include <iostream>
#include <cstdio>
#include "fraction.hpp"

using namespace std;

int main(){
	vector <double> pairs;	//pairs - catch (number of balls to match), payout
	double bet;				//amount to bet
	int balls;				//number of balls
	Fraction frac;			//Fraction object - be able to use fraction.cpp & binomial stuff
	double prob;			//Probability
	double allReturns;		//Sum of all expected returns
	

	cin >> bet;
	cin >> balls;
	pairs.resize((balls+1) * 2);	//Resizes it big enough to have 8 catches

	printf("Bet: %.2f\n", bet);
	cout << "Balls Picked: " << balls << endl;
	


	
	//Using vector to store catch & payout bc idk how many will be entered
	//Even entries (catches) AND odd entries (payout)
	for(unsigned int i = 0; i < pairs.size(); i++){
		cin >> pairs[i];	
	}
	
	for(unsigned int j = 0; j < pairs.size(); j+=2){
		//It's an empty vector pair if there is no money (but a catch can be 0)
		if(pairs[j+1] != 0){ 
			frac.Multiply_Binom(80-balls, 20-pairs[j]);
			frac.Multiply_Binom(balls, pairs[j]);
			frac.Divide_Binom(80, 20);
			prob = frac.Calculate_Product();
		
			cout << "  Probability of catching " << pairs[j] << " of " << balls << ": " << prob << " -- Expected return: " << (prob * pairs[j+1]) << endl;
		
			allReturns += (prob * pairs[j+1]);
			frac.Clear();
		}
	}

	printf("Your return per bet: %.2f\n", allReturns - bet);
	printf("Normalized: %.2f\n", (allReturns - bet) / bet);

	return 0;
}
