/* Name:
 * Date:
 * Program:
 * Purpose:
 */

#include <iostream>
#include <set>
#include "fraction.hpp"

using namespace std;


//Clear both the numerator and denominator
void Fraction::Clear(){
	numerator.clear();
	denominator.clear();
}




//Add a number to the numerator
bool Fraction::Multiply_Number(int n){
	if(n <= 0)
		return false;

	if(n > 1){
		if(denominator.find(n) == denominator.end())
			numerator.insert(n);
		else
			denominator.erase(denominator.lower_bound(n));
	}
	return true;
}

//Add a number to the denominator
bool Fraction::Divide_Number(int n){
	if(n <= 0)
		return false;
	
	if(n > 1){
		if(numerator.find(n) == numerator.end())
			denominator.insert(n);
		else
			numerator.erase(numerator.lower_bound(n));
	}
	return true;
}




//Add the numbers 2 through n to the numerator
bool Fraction::Multiply_Factorial(int n){
	if(n >= 1){
		for(int i = 2; i <= n; i++){
			if(denominator.find(i) == denominator.end())
				numerator.insert(i);
			else
				denominator.erase(denominator.lower_bound(i));
				//denominator.erase(i);
		}
		return true;
	}
	return false;
}

//Add the numbers 2 through n to the denominator
bool Fraction::Divide_Factorial(int n){
	if(n >= 1){
		for(int i = 2; i <= n; i++){
			if(numerator.find(i) == numerator.end())
				denominator.insert(i);
			else
				numerator.erase(numerator.lower_bound(i));
				//numerator.erase(i);
		}
		return true;
	}
	return false;
}




//Effect multiplying by n-choose-k
bool Fraction::Multiply_Binom(int n, int k){
	if(n <= 0 || k < 0)
		return false;
	
	for(int i = 2; i <= n; i++){
		if(denominator.find(i) == denominator.end())
			numerator.insert(i);
		else
			denominator.erase(denominator.lower_bound(i));
	}
	
	for(int j = 2; j <= k; j++){
		if(numerator.find(j) == numerator.end())
			denominator.insert(j);
		else
			numerator.erase(numerator.lower_bound(j));
	}

	for(int m = 2; m <= (n-k); m++){
		if(numerator.find(m) == numerator.end())
			denominator.insert(m);
		else
			numerator.erase(numerator.lower_bound(m));
	}
	return true;
}

//Effect dividing by n-choose-k
bool Fraction::Divide_Binom(int n, int k){
	if(n <= 0 || k < 0)
		return false;

	for(int j = 2; j <= k; j++){
		if(denominator.find(j) == denominator.end())
			numerator.insert(j);
		else
			denominator.erase(denominator.lower_bound(j));
	}

	for(int m = 2; m <= (n-k); m++){
		if(denominator.find(m) == denominator.end())
			numerator.insert(m);
		else
			denominator.erase(denominator.lower_bound(m));
	}

	for(int i = 2; i <= n; i++){
		if(numerator.find(i) == numerator.end())
			denominator.insert(i);
		else
			numerator.erase(numerator.lower_bound(i));
	}
	return true;
}




//Swap the numerator and denominator
void Fraction::Invert(){
	numerator.swap(denominator);
}

//Print the equation for the fraction
void Fraction::Print() const{
	unsigned int signCounter = 0;
	multiset <int>::const_iterator nit;

	if(numerator.size() == 0 && denominator.size() == 0)
		cout << 1 << endl;	

	else{
		for(nit = numerator.begin(); nit != numerator.end(); nit++){
			cout << *nit;
		
			if(signCounter < numerator.size() - 1)
				cout << " * ";

			signCounter++;
		}
	
		signCounter = 0;
		if(numerator.size() == 0 && denominator.find(1) == denominator.end())
			cout << 1 << " / ";
		
		if(numerator.size() != 0 && denominator.size() != 0)
			cout << " / ";


		for(nit = denominator.begin(); nit != denominator.end(); nit++){
			cout << *nit;

			if(signCounter < denominator.size() - 1)
				cout << " / ";

			signCounter++;
		}
		cout << endl;
	}
}

//Calculate the product as a double
double Fraction::Calculate_Product() const{
	double product = 1;
	multiset <int>::const_iterator nit;

	if(numerator.size() != 0){
		for(nit = numerator.begin(); nit != numerator.end(); nit++){
			product *= *nit;
		}
	}

	if(denominator.size() != 0){
		for(nit = denominator.begin(); nit != denominator.end(); nit++){
			product /= *nit;
		}
	}
	return product;
}
