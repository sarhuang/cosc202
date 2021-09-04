/*
 * Name: Sarah Huang
 * Date: 9/4/21
 * Program: neg.cpp
 * Purpose: Given a PGM file, reverse the pixel colors and print them.
 */

#include <iostream>
#include <cstdio>
using namespace std;

int main(){
	string strInput = "";	//String input placeholder
	int pixel;				//Integer input placeholder
	int row;				//Number of rows
	int col;				//Number of columns
	int pixelCount = -3;	//Total number of pixels (not counting col, row, 255)
	bool yesP2 = false;		//true if P2 is the first word in the file


	do{
		if(cin >> pixel){
			pixelCount++;

			//Reading in # of columns, # of rows, and 255 (doesn't count toward # of pixels)
			if(pixelCount == -2){
				if(pixel > 0)
					col = pixel;
				else{
					fprintf(stderr, "Bad PGM file -- No column specification\n");
					return 1;
				}
			}
			else if(pixelCount == -1){
				if(pixel > 0)
					row = pixel;
				else{
					fprintf(stderr, "Bad PGM file -- No row specification\n");
					return 1;
				}
			}
			else if(pixelCount == 0){
				//Print out col, row, 255 if they are all there and no errors
				if(pixel == 255 && yesP2){
					printf("P2\n");
					printf("%d %d\n", col, row);
					printf("%d\n", 255);
				}
				else{
					fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
					return 1;
				}
			}
			
			//Reading the value of pixel
			else{
				if(pixelCount > (row * col)){
					fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
					return 1;
				}
				else if(pixel < 0 || pixel > 255){
					fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", pixelCount - 1);
					return 1;
				}
				

				//Inverting the colors
				printf("%d\n", 255 - pixel);
			}
		}

		//Reading for P2 (should only run once)
		else{
			cin.clear();
			cin >> strInput;

			if(strInput == "P2" && pixelCount == -3)
				yesP2 = true;

			else if(strInput != "P2" && pixelCount == -3){
				fprintf(stderr, "Bad PGM file -- first word is not P2\n");
				return 1;
			}
		}
	} while(!cin.eof());

	return 0;
}
