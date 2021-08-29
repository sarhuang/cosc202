/*
 * Name: Sarah Huang
 * Date: 8/28/21
 * Program: checkerboard.cpp
 * Purpose: Prints (R * C) grid starting from given char to end of cycle char.
 *			Using width, each char of grid is printed as (W * W) square.
 */


#include <iostream>
using namespace std;

int main(){

	int r = 0;					//# of rows
	int c = 0;					//# of columns
	int cs = 1;					//cycle size
	int w = 0;					//width
	char sc = 0;				//starting character (the first char of each line - will change)
	char firstChar = 0;			//the ORIGINAL sc
	char currentChar = 0;		//the char the program is printing now
	char lastChar = 0;			//last char before restarting cycle

	

	/* Asking for input, all in one line
	 * Print error if not enough parameters */
	
	if(!(cin >> r && cin >> c && cin >> sc && cin >> cs && cin >> w)){
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W" << endl;
		return 1;
	}
		

	//Exits silently if parameter <=0 and ASCII value of sc + cs > 127
	
	if(r > 0 && c > 0 && sc > 0 && cs > 0 && w > 0){
		if((sc + cs) <= 127){
			firstChar = sc;
			lastChar = sc + (cs - 1);
			

			/* Print each char w times, update char to next one (reset back to original after cycle size)
			 * Repeat loop repeats the previous row to make it (width * width)
			 * sc updates to start next char repeat loop/(w*w) and firstChar keeps original input char */
		
			for(int numRow = 0; numRow < r; numRow++){	
				currentChar = sc;
		
				for(int repeat = 0; repeat < w; repeat++){

					for(int numCol = 0; numCol < c; numCol++){
						for(int i = 0; i < w; i++){
							cout << currentChar;
						}

						if(currentChar == lastChar)
							currentChar = firstChar;
						else
							currentChar += 1;
					}
					cout << endl;
					currentChar = sc;
				}

				if(sc == lastChar)
					sc = firstChar;
				else
					sc += 1;
			}	
		}
	}

	return 0;
}
