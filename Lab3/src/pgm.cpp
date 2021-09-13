#include "pgm.hpp"


#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
  ifstream fin;
  string s;
  size_t i, j, r, c, v;

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


bool Pgm::Write(const std::string &file) const{
	(void) file; //do this for every new function without warnings/errors
	ofstream ofs;
	int numColumns = 0;
	int pixelValue = 0;
	int totalPixels = 0;

	ofs.open(file.c_str());

	if(!ofs)
		return false;


	if(Pixels.size() == 0)
		return false;

	
	pixelValue = Pixels[0][0];
	numColumns = Pixels[0].size();
	totalPixels = Pixels.size() * numColumns;
	
	
	ofs << "P2" << endl;
	ofs << numColumns << " " << Pixels.size() << endl;	//CHANGE TO OFS
	ofs << 255 << endl;


	
	for(int k = 1; k < totalPixels; k++){
		if(k % 20 != 0){
			//if(k == totalPixels)
			//	ofs << pixelValue << "\n";
			//else
				ofs << pixelValue << " ";
		}
		else
			ofs << pixelValue << "\n";
		
		pixelValue = Pixels[k / Pixels[0].size()][k % Pixels[0].size()];
		
		
		//cout << "k = " << k << " and Pixels.size() = " << Pixels.size() << endl;
		//cout << "[" << k/Pixels[0].size() << "] [" << k%Pixels[0].size() << "]" << endl;
	}
	ofs << pixelValue << "\n";
	

	/*
	for(unsigned int i = 0; i < Pixels.size(); i++){
		for(unsigned int j = 0; j < Pixles[0].size(); j++){
			pixelValue = Pixels[i][j];
			
			if( (i+j)
		}
	}*/
	
	ofs.close();
	return true;
}


bool Pgm::Create(size_t r, size_t c, size_t pv){
	(void) r;	//number of rows
	(void) c;	//number of columns
	(void) pv;	//pixel value

	if(c == 0 || r == 0 || pv > 255)
		return false;


	Pixels.resize(r, vector<int>(c, 0));
	
	for(unsigned int i = 0; i < Pixels.size(); i++){
		for(unsigned int j = 0; j < Pixels[i].size(); j++){
			Pixels[i][j] = pv;
		}
	}
	return true;
}



bool Pgm::Clockwise(){
	size_t row = Pixels.size();
	size_t col = 0;
	vector <vector <int> > temp = Pixels;

	if(Pixels.size() == 0)
		return false;
	
	col = Pixels[0].size();

	
	//cout << "row1 = " << Pixels.size() << " col1 = " << Pixels[0].size() << endl;	//216 277
	
	Pixels = vector <vector <int> > (col, vector<int>(row));

	//cout << "row2 = " << Pixels.size() << " col2 = " << Pixels[5].size() << endl;	//277 277
	//cout << "but variable row = " << row << " variable col = " << col << endl;		//216 277


	for(unsigned int i = 0; i < row; i++){
		for(unsigned int j = 0; j < col; j++){
			Pixels[j][row-1-i] = temp[i][j];
			//cout << "[j][row-1-i] = " << j << " " << row-1-i << " = " << temp[i][j] << endl;
		}
		//cout << "exit the j loop" << endl;
	}
	//cout << "After CW, Pixels.size() = " << Pixels.size() << " and Pixels[0].size() = " << Pixels[0].size() << endl;
	return true;
}



bool Pgm::Cclockwise(){
	size_t rows = Pixels.size();
	size_t cols = 0;
	vector <vector <int> > temp = Pixels;

	if(Pixels.size() == 0)
		return false;

	cols = Pixels[0].size();

	Pixels = vector <vector <int> > (cols, vector<int> (rows));

	for(unsigned int i = 0; i < rows; i++){
		for(unsigned int j = 0; j < cols; j++)
			Pixels[cols-1-j][i] = temp[i][j];
	}
	//cout << "After CCW, Pixels.size() = "<< Pixels.size() << " and Pixels[0].size() = " << Pixels[0].size() << endl;
	return true;
}



bool Pgm::Pad(size_t w, size_t pv){
	(void) w;
	(void) pv;

	if(Pixels.size() == 0 || pv >= 255)
		return false;

	size_t oldRow = Pixels.size();
	size_t oldCol = Pixels[0].size();
	size_t newRow = oldRow + 2*w;
	size_t newCol = oldCol + 2*w;
	vector <vector <int> > temp = Pixels;
	bool prev_pv = false;
	bool next_0 = false;
	//int counter = 0;
		
	Pixels = vector < vector <int> > (newRow, vector<int> (newCol));

	
	
	for(unsigned int i = 0; i < newRow; i++){
		for(unsigned int j = 0; j < newCol; j++){

			if(i == w && j == w){
				for(unsigned int m = w; m < w + oldRow; m++){
					for(unsigned int n = w; n < w + oldCol; n++){
						Pixels[m][n] = temp[m-w][n-w];
					}
					
					for(unsigned int b = 0; b < w; b++){
						Pixels[m][b + w + oldCol] = pv;
					}

					//for(unsigned int b = 1; b >= 2; b++){
						for(unsigned int c = 0; c < w; c++){
							Pixels[m+1][c] = pv;
						}
					//}
				}
			}
			
			else if(Pixels[i][j] == 0 /*&& (i <= w || i >= w+oldRow)*/){
				next_0 = (j < (newCol-2) && Pixels[i][j+1] == 0 && Pixels[i][j+2] == 0);
				prev_pv = (j >= 2 && (unsigned int)Pixels[i][j-1] == pv && (unsigned int)Pixels[i][j-2] == pv);
				
				
				if(next_0 && prev_pv){
					Pixels[i][j] = pv;
				}

				//< w+1
				else if(i < w || i >= newRow-w){
					Pixels[i][j] = pv;

				}
				
				else if(i == w){
					for(unsigned int d = 0; d < w; d++){
						Pixels[i][d] = pv;
					}
				}				
			}
		}
	}
	//cout << "After Pad, Pixels.size() = " << Pixels.size() << " and Pixels[0].size() = " << Pixels[0].size() << endl;
	return true;
}




bool Pgm::Panel(size_t r, size_t c){
	(void) r;
	(void) c;

	if(Pixels.size() == 0 || r == 0 || c == 0)
		return false;
	
	size_t newRow = r * Pixels.size();
	size_t newCol = c * Pixels[0].size();
	
	vector <vector <int> > temp = Pixels;
	Pixels = vector <vector <int> > (newRow, vector<int> (newCol));

	for(unsigned int i = 0; i < newRow; i++){
		for(unsigned int j = 0; j < newCol; j++){
			Pixels[i][j] = temp[i % temp.size()][j % temp[0].size()];
			//cout << "Pixels[" << i << "][" << j << "] = " << Pixels[i][j] << endl;
			//cout << "temp[" << (i % temp.size()) << "][" << (j % temp[0].size()) << "] = " << temp[i%temp.size()][j%temp[0].size()] << endl;
			//cout << "---------------------------------" << endl;

		}
	}
	//cout << "After Panel, Pixels.size() = " << Pixels.size() << " and Pixels[0].size = " << Pixels[0].size() << endl;
	return true;
}


//Panel
//r=2, c=2
//2x3 --> 4x6	2*r=4	3*c=6
//
//1 2 3		1 2 3
//4 5 6		4 5 6
//	  1 2 3 1 2 3
//    4 5 6 4 5 6
//
//k goes 0-5 -->  012012 by doing k%3
//0%3=0, 1%3=1, 2%3=2, 3%3=0, 4%3=1, 5%3=2
//------------------------------------------


bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols){
	(void) r;		//Starting row position
	(void) c;		//Starting col position
	(void) rows;	//New row size
	(void) cols;	//New col size

	if(Pixels.size() == 0)
		return false;

	//cout << Pixels.size() << " vs " << rows << endl;
	//cout << Pixels[0].size() << " vs " << cols << endl;

	if(Pixels.size() < (r+rows) || Pixels[0].size() < (c+cols))
		return false;

	vector <vector <int> > temp = Pixels;
	Pixels = vector <vector <int> > (rows, vector<int> (cols));

	
	for(unsigned int i = 0; i < Pixels.size(); i++){
		for(unsigned int j = 0; j < Pixels[0].size(); j++){
			Pixels[i][j] = temp[r+i][c+j];
		}
	}
	
	//cout << "After Crop, Pixels.size() = " << Pixels.size() << " and Pixels[0].size() = " << Pixels[0].size() << endl;
	return true;
}


//Crop
//45 - starting row 
//60 - starting column
//50 - new row
//100- new column
//
//[45-95] [60-160]
//
//200x300
//
//50x100 - loop 50 & 100?
//45, 60 - start at 45 & 60?
//
//
//0, 1, 2, 2
//
//1 2 3	    -->  2 3
//4 5 6			 5 6
