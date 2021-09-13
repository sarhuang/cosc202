/* Name: Sarah Huang
 * Date: 9/12/21
 * Program: pgm.cpp
 * Purpose: Implement methods that read, write, and manipulate a pgm file.
 */


#include "pgm.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


/* (ALREADY WRITTEN FOR YOU)
 * Reads in a pgm file with file name as input.
 * If the pgm file doesn't have the specific row, col, and 255, it fails to read it.
 * Resizes the Pixels matrix and stores the pixel values in there. */

bool Pgm::Read(const std::string &file)
{
  ifstream fin;				//Input file stream
  string s;					//String placeholder to read "P2"	
  size_t i, j, r, c, v;		//Placeholders, row, col, pixel value

  fin.open(file.c_str());
  if (fin.fail()) return false;
  
  if (!(fin >> s)) return false;
  if (s != "P2") return false;
  if (!(fin >> c) || c <= 0) return false;
  if (!(fin >> r) || r <= 0) return false;
  if (!(fin >> i) || i != 255) return false;

  Pixels.resize(r);
  for (i = 0; i < r; i++) {
    Pixels[i].clear();
    for (j = 0; j < c; j++) {
      if (!(fin >> v) || v > 255) return false;
      Pixels[i].push_back(v);
    }
  }
  if (fin >> s) return false;
  fin.close();
  return true;
}




/* Writes a new pgm file using the given file name & row, col, and pixel values from Pixels matrix.
 *
 * Specific format:
 *	 - P2 on its own line, no spaces.
 *	 - cols rows on the next line, separated by a space, no additional spaces
 *	 - 255 on its own line, no spaces.
 *	 - Then the pixels: 20 pixels per line, one space between pixels, no additional spaces.
 *	 - You don't print additional newlines at the end of each row of pixels -- just start the next row of pixels.
 *   - The last line is the only one that can have fewer than 20 pixels. 
 *
 * ERROR if the Pixels matrix is completely empty (or if we can't write the file for some reason) */  

bool Pgm::Write(const std::string &file) const{
	(void) file;				//User input - file name
	ofstream ofs;				//Output file stream
	size_t pixelValue = 0;		//Value of the pixel
	size_t totalPixels = 0;		//Total number of pixels in pgm file

	ofs.open(file.c_str());

	if(!ofs || Pixels.size() == 0)
		return false;
	
	pixelValue = Pixels[0][0];
	totalPixels = Pixels.size() * Pixels[0].size();
	
	ofs << "P2" << endl;
	ofs << Pixels[0].size() << " " << Pixels.size() << endl;
	ofs << 255 << endl;

	for(size_t i = 1; i < totalPixels; i++){
		if(i % 20 != 0)
			ofs << pixelValue << " ";
		else
			ofs << pixelValue << "\n";
		
		pixelValue = Pixels[i / Pixels[0].size()][i % Pixels[0].size()];
	}
	ofs << pixelValue << "\n";
	ofs.close();
	return true;
}




/* Resizes the Pixels matrix wit the given row and column & set the pixel value (will be all the same).
 * ERROR if the row is 0, col is 0, or the pixel value is over 255 (non-existent) */

bool Pgm::Create(size_t r, size_t c, size_t pv){
	(void) r;	//Row size
	(void) c;	//Column size
	(void) pv;	//Pixel value


	if(c == 0 || r == 0 || pv > 255)
		return false;

	Pixels.resize(r, vector<int>(c, 0));
	
	for(size_t i = 0; i < Pixels.size(); i++){
		for(size_t j = 0; j < Pixels[i].size(); j++){
			Pixels[i][j] = pv;
		}
	}
	return true;
}




/* Rotates the pgm file clockwise by 90 degrees.
 * ERROR if the Pixels matrix is empty. */

bool Pgm::Clockwise(){
	size_t row = Pixels.size();				//Original row size
	size_t col = Pixels[0].size();			//Original column size
	vector <vector <int> > temp = Pixels;	//Placeholder for original Pixels matrix

	if(Pixels.size() == 0)
		return false;
	
	//Resize Pixels vector
	Pixels = vector <vector <int> > (col, vector<int>(row));

	for(size_t i = 0; i < row; i++){
		for(size_t j = 0; j < col; j++){
			Pixels[j][row-1-i] = temp[i][j];
		}
	}
	return true;
}




/* Rotates the pgm file counterclockwise by 90 degrees.
 * ERROR if the Pixels matrix is empty. */

bool Pgm::Cclockwise(){
	size_t row = Pixels.size();				//Original row size
	size_t col = Pixels[0].size();			//Original column size
	vector <vector <int> > temp = Pixels;	//Placeholder for original Pixels matrix

	if(Pixels.size() == 0)
		return false;
	

	Pixels = vector <vector <int> > (col, vector<int> (row));

	for(unsigned int i = 0; i < row; i++){
		for(unsigned int j = 0; j < col; j++)
			Pixels[col-1-j][i] = temp[i][j];	//Identical to Clockwise but swapped
	}
	return true;
}




/* Add a border of w pixels with the given value.
 * Checks through every pixel - that's why there's multiple checks and for loops
 * ERROR if Pixels matrix is empty*/
bool Pgm::Pad(size_t w, size_t pv){
	(void) w;								//Width = How much padding
	(void) pv;								//Pixel value

	if(Pixels.size() == 0 || pv >= 255)
		return false;

	size_t oldRow = Pixels.size();			//Original row size
	size_t oldCol = Pixels[0].size();		//Original column size
	size_t newRow = oldRow + 2*w;			//New row size
	size_t newCol = oldCol + 2*w;			//New column size
	vector <vector <int> > temp = Pixels;	//Placeholder for original Pixels matrix
	bool prev_pv = false;					//True if last two elements equal pv
	bool next_0 = false;					//True if next two elements equal 0
	
		
	Pixels = vector < vector <int> > (newRow, vector<int> (newCol));


	for(unsigned int i = 0; i < newRow; i++){
		for(unsigned int j = 0; j < newCol; j++){

			//At i==w and j==w, the top left corner of the original matrix is there, not padding.
			if(i == w && j == w){
				for(size_t a = w; a < w + oldRow; a++){

					//Copy original matrix values to resized matrix
					for(size_t b = w; b < w + oldCol; b++){
						Pixels[a][b] = temp[a-w][b-w];
					}
					
					//Padding in current row
					for(size_t c = 0; c < w; c++){
						Pixels[a][c + w + oldCol] = pv;
					}
					
					//Padding before the next copy of values in the next row
					for(size_t d = 0; d < w; d++){
						Pixels[a+1][d] = pv;
					}
				}
			}
			
			else if(Pixels[i][j] == 0){
				next_0 = (j < (newCol-2) && Pixels[i][j+1] == 0 && Pixels[i][j+2] == 0);
				prev_pv = (j >= 2 && (unsigned int)Pixels[i][j-1] == pv && (unsigned int)Pixels[i][j-2] == pv);
				
				//Ex. 188 188 _ 0 0  --> definetly padding 
				if(next_0 && prev_pv)
					Pixels[i][j] = pv;

				//Padding way before and after original matrix
				else if(i < w || i >= newRow-w)
					Pixels[i][j] = pv;
				
				//Padding right before original matrix
				else if(i == w){
					for(size_t e = 0; e < w; e++){
						Pixels[i][e] = pv;
					}
				}				
			}
		}
	}
	return true;
}




/* Makes multiple copies of the original Pixels matrix and stores them in the resized matrix.
 * ERROR if the Pixels matrix is empty, the row is 0, or the column is 0. */

bool Pgm::Panel(size_t r, size_t c){
	(void) r;								//Row multiplier
	(void) c;								//Column multiplier

	if(Pixels.size() == 0 || r == 0 || c == 0)
		return false;
	
	size_t newRow = r * Pixels.size();		//New row size
	size_t newCol = c * Pixels[0].size();	//New column size
	vector <vector <int> > temp = Pixels;	//Placeholder for original Pixels matrix

	Pixels = vector <vector <int> > (newRow, vector<int> (newCol));

	for(size_t i = 0; i < newRow; i++){
		for(size_t j = 0; j < newCol; j++){
			Pixels[i][j] = temp[i % temp.size()][j % temp[0].size()];
		}
	}
	return true;
}




/* Crops the pgm file from the given starting row col position to new given row and col sizes.
 * ERROR if the Pixels matrix is empty or the user tries to crop more than what's available. */

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols){
	(void) r;								//Starting row position
	(void) c;								//Starting col position
	(void) rows;							//New row size
	(void) cols;							//New col size

	if(Pixels.size() == 0 || Pixels.size() < (r+rows) || Pixels[0].size() < (c+cols))
		return false;

	vector <vector <int> > temp = Pixels;	//Placeholder for original Pixels matrix
	Pixels = vector <vector <int> > (rows, vector<int> (cols));

	
	for(size_t i = 0; i < Pixels.size(); i++){
		for(size_t j = 0; j < Pixels[0].size(); j++){
			Pixels[i][j] = temp[r+i][c+j];
		}
	}
	return true;
}
