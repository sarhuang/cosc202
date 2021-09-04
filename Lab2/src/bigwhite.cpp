/*
 * Name: Sarah Huang
 * Date: 9/4/21
 * Program: bigwhite.cpp
 * Purpose: Using command line arguments, make a PGM file with argv[1] rows and argv[2] columns of white pixels.
 */

#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

int main(int argc, char **argv){
	stringstream ss;	//Used to convert command line arguments (char) to integers
	int num;			//Placeholder for input
	int row;			//Number of rows
	int col;			//Number of columms


	//Error if not exactly 3 command line arguments (bigwhite, row, col)
	if(argc != 3){
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return 1;
	}


	//Convert command line arguments (char) to int to calculate how many white pixels to print
	//Error if not an int AND input is <= 0
	ss.str(argv[1]);
	if(ss >> num && num > 0){
		row = num;
		
		ss.clear();
		ss.str(argv[2]);
		if(ss >> num && num > 0)
			col = num;

		else{
			fprintf(stderr, "usage: bigwhite rows cols\n");
			return 1;
		}
	}
	else{
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return 1;
	}


	//3 requirements for PGM file
	printf("P2\n");
	printf("%d %d\n", col, row);
	printf("%d\n", 255);

	//Printing row x col amount of white pixels
	for(int i = 0; i < (row*col); i++){
		printf("%d\n", 255);
	}

	return 0;
}
