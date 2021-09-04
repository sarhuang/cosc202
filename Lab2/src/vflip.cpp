/*
 * Name: Sarah Huang
 * Date: 9/4/21
 * Program: vflip.cpp
 * Purpose: Given a PGM file, manipulate the pixels so that the image is flipped vertically.
 */

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
	string strInput = "";	//String input placeholder
	int pixel;				//Integer input placeholder
	int row;				//Number of rows
	int col;				//Number of columns
	int pixelCount = -3;	//Total number of pixels (Not the pixel index)
	bool yesP2 = false;		//true if P2 is the first word in the file
	vector <int> pgm;		//Vector to hold all pixel values
	
	

	do{
		if(cin >> pixel){
			pixelCount++;

			////Reading in # of columns, # of rows, and 255 (doesn't count toward # of pixels)
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
				////Print out col, row, 255 if they are all there and no errors
				if(pixel == 255 && yesP2){
					printf("P2\n");
					printf("%d %d\n", col, row);
					printf("%d\n", 255);
				}
				//If there is no P2 at all, no strings in file
				else if(yesP2 == false){
					fprintf(stderr, "Bad PGM file -- first word is not P2\n");
					return 1;
				}
				else{
					fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
					return 1;
				}
			}
			//Reading the value of pixel and its error checks
			else{
				if(pixelCount > (row * col)){
					fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
					return 1;
				}
				else if(pixel < 0 || pixel > 255){
					fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", pixelCount - 1);
					return 1;
				}
	

				//Store pixel values in vector
				pgm.push_back(pixel);			
			}
		}
	

		//STRING INPUT - Reading for P2 and its error checks
		//Note to self: pixelCount does NOT get updated if cin detects a string
		else{
			cin.clear();
			cin >> strInput;

			if(strInput == "P2" && pixelCount == -3)
				yesP2 = true;

			//If the first word is a string that's not P2
			else if(strInput != "P2" && pixelCount == -3){
				fprintf(stderr, "Bad PGM file -- first word is not P2\n");
				return 1;
			}
			//If the column is a string
			else if(yesP2 && pixelCount == -3){
				fprintf(stderr, "Bad PGM file -- No column specification\n");
				return 1;
			}
			//If the row is a string
			else if(yesP2 && pixelCount == -2){
				fprintf(stderr, "Bad PGM file -- No row specification\n");
				return 1;
			}
			//If the counted total number of pixels is less than row*col (what it's supposed to be)	
			else if(pixelCount < (row*col)){
				fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", pixelCount + 1);
				return 1;
			}
		}
	} while(!cin.eof());



	
	int first = 0;					//First (2nd, 3rd, etc.) number in vector
	int last = col * (row - 1);		//Last (2nd last, 3rd last, etc.) number in vector
	int temp;						//Placeholder for first number so it doesn't disappear
	int counter = 0;				//Counts numbers to determine line breaks like in gradescript

	//Flips the first and last numbers in the vector
	while(first < last){
		for(int i = 0; i < col; i++){
			temp = pgm.at(first + i);
			pgm.at(first + i) = pgm.at(last + i);
			pgm.at(last + i) = temp;
		}
		first += col;
		last -= col;
	}

	//Printing the newly ordered vector
	for(unsigned int index = 0; index < pgm.size(); index++){
		if(counter == 15){
			printf("\n");
			counter = 0;
		}

		printf("%3d ", pgm.at(index));
		counter++;
	}


	return 0;
}
