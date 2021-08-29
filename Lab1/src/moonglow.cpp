/*
 * Name: Sarah Huang
 * Date: 8/29/21
 * Program: moonglow.cpp
 * Purpose: From reading a text file, find and print out the student's name and exam score.
 */

#include <iostream>
using namespace std;

int main(){
	
	string name = "";		// student's name
	double score = 0;		// student's total exam score
	double average = 0;		// average of numbers after AVERAGE
	double numInput = 0;	// numerical input
	string strInput = "";	// string input
	int counter = 0;		// amount of numbers after AVERAGE



	/* Reading number input potential responses:
	 *	1. Correct number input --> Add to score
	 *	2. String input --> NAME --> Next word is name
	 *	3. String input --> AVERAGE --> Add & average upcoming numbers --> Add to score
	 *	4. EOF --> Quit asking for input --> Print results */

	do{
		if(cin >> numInput)
			score += numInput;

		else{
			cin.clear();
			cin >> strInput;
			
			if(strInput == "NAME")
				cin >> name;

			else if(strInput == "AVERAGE"){
				while(cin >> numInput){
					average += numInput;
					counter++;
				}
				if(counter != 0){
					average /= counter;
					score += average;
					counter = 0;
					average = 0;
				}
			}
		}
	} while(!cin.eof());

	cout << name << " " << score << endl;
	
	return 0;
}
