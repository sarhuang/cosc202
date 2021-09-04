/*
 * Name: Sarah Huang
 * Date: 9/3/21
 * Program: pgminfo.cpp
 * Purpose: Reading in a .pgm file, find and print...
 *			1. The number of rows
 *			2. The number of columns
 *			3. Total number of pixels
 *			4. Average value of all pixels, padded to 3 decimal places
 *			
 *			Print out an error on any invalid PGM file.
 */


#include <iostream>
#include <cstdio>
using namespace std;



int main(){

	string strInput = "";	//String input placeholder
	int pixel = 0;			//Integer input placeholder
	int row = 0;			//Number of rows
	int col = 0;			//Number of columns
	int pixelCount = -3;	//Total number of pixels (not counting col, row, and 255)
	double average = 0.0;	//Average value of all pixels


	
	do{
		if(cin >> pixel){
			pixelCount++;
			
			//Reading in # of columns, # of rows, and 255 (does not count toward # of pixels)
			if(pixelCount == -2){
				if(pixel > 0)
					col = pixel;
				else{
					cerr << "Bad PGM file -- No column specification" << endl;
					return 1;
				}
			}
			else if(pixelCount == -1){
				if(pixel > 0)
					row = pixel;
				else{
					cerr << "Bad PGM file -- No row specification" << endl;
					return 1;
				}
			}
			else if(pixelCount == 0 && pixel != 255){
				cerr << "Bad PGM file -- not 255" << endl;
				return 1;
			}
	
			//Reading the value of pixel
			else{
				if(pixelCount > (row * col)){
					cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
					return 1;

				}
				else if(pixel < 0 || pixel > 255){
					cerr << "Bad PGM file -- pixel " << (pixelCount - 1) << " is not a number between 0 and 255" << endl;
					return 1;
				}
				

				if(pixelCount > 0)
					average += pixel;
			}
		}

		//Reading for P2 (should only run once)
		else{
			cin.clear();
			cin >> strInput;

			if(strInput != "P2"){
				cerr << "Bad PGM file -- first word is not P2" << endl;
				return 1;
			}
		}
	} while(!cin.eof());


	//After reading the file, report results with right spacing

	average = average / (row * col);

	printf("# Rows: %11d\n", row);
	printf("# Columns: %8d\n", col);
	printf("# Pixels: %9d\n", (row*col));
	printf("Avg Pixel: %8.3f\n", average); 

	return 0;
}
