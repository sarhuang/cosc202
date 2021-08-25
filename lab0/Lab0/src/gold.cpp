#include <iostream>
using namespace std;


int main(){
	char c;
	int total;

	//some loop(cin >> c)
	//Check if not '-' or '.'
	//Add to running total based on character value
	
	while(cin >> c){
		if(c != '.'  || c != '-'){
			if(c >= 'A' && c <= 'Z'){
				total += (c - 'A') + 1;
			}
		}
	}



	cout << total << endl;
	
	return 0;
}
