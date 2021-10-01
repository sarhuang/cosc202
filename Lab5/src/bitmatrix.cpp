/* Name: Sarah Huang
 * Date: 
 * Program: bitmatrix.cpp
 * Purpose:
 */


#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;


//vector <string> M; - The matrix, elemnts are '0' or '1'
// 1. If M is storing a r by c matrix, it will contain r strings each with c characters.
// 2. Characters are either '0' for zero or '1' for one.


/* Create an empty bitmatrix with the given size. 
 * Throw the string "Bad rows" if (rows <= 0).
 * Throw the string "Bad cols" if (cols <= 0). */
Bitmatrix::Bitmatrix(int rows, int cols){
	(void) rows;
	(void) cols;
	string r = "Bad rows";
	string c = "Bad cols";
	string z;
	
	if(rows <= 0)
		throw(r);
	
	if(cols <= 0)
		throw(c);

	z = string(cols, '0');
	
	if(rows > 0 && cols > 0){
		M.resize(rows);
		
		for(int i = 0; i < rows; i++){
			M.at(i) = z;
		}
	}
}
           

/* Read the bitmatrix from a file.
 * Throw "Can't open file" if you can't open the file.
 * Throw "Bad file format" if you can't read the file. 
 *
 * 1. Blank lines are ignored
 * 2. Non-blank lines must be composed soley of zeroes, ones or whitespace
 * 3. Each non-blank line represents a row of the matrix (with whitespace ignored)
 * 4. Each row has to have the same number of columns. */
Bitmatrix::Bitmatrix(const string &fn){
	(void) fn;
	ifstream fin;
	string row;
	string newRow;
	string noOpen = "Can't open file";
		
	fin.open(fn.c_str());
	if(fin.fail())
		throw(noOpen);

	//if(!(fin >> row))
	//	throw("Bad file format");

	do{
		getline(fin, row);
		
		if(row != ""){
			for(unsigned int i = 0; i < row.size(); i++){
				if(row[i] == '0' || row[i] == '1')
					newRow += row[i];
			}
			
			M.push_back(newRow);
			newRow = "";
		}
	} while(!fin.eof());
	fin.close();
}


/* Create a new bitmatrix using new, which is a copy of the caller's bitmatrix
 * Return a pointer to it. */
Bitmatrix *Bitmatrix::Copy() const {
	Bitmatrix *copy = new Bitmatrix(M.size(), M.at(0).size());	
	copy->M = this->M;
	return copy;
}
                 




/* Write to a file.  
 * You will print one line per row of the bitmatrix
 *	- Each line is only composed of 0's and 1's.
 * Return true if successful and false if not. */	                                            
bool Bitmatrix::Write(const string &fn) const {
	(void) fn;
	ofstream ofs;

	ofs.open(fn.c_str());
	if(!ofs)
		return false;

	for(unsigned int r = 0; r < M.size(); r++){
		ofs << M.at(r) << endl; 
	}
	ofs.close();
	return true;
}
 

/* Print on standard output.  
 * You will print one line per row of the bitmatrix.  
 *	- Each line is composed of 0's and 1's, and there will be a space after every w characters 
 *	- Don't put a space at the end if the number of columns is a multiple of w                                                                                                                              
 * Also put a blank line after every w rows (except the last, if the number of rows is a multiple of w). 
 *
 * 1. If w <= 0, print each row on its own line with no spaces.
 *	  Otherwise, print a space after every w columns and a blank line after every w rows.*/
void Bitmatrix::Print(size_t w) const {
	(void) w;
	
	if(M.size() != 0){
		for(unsigned int r = 0; r < M.size(); r++){
			if(w <= 0 || w >= M.at(r).size())
				printf("%s\n", M.at(r).c_str());

			else{
				//Printing row with spacing	
				printf("%s ", M.at(r).substr(0, w).c_str());
				
				for(unsigned int i = w; i < M.at(r).size(); i++){
					if(i % w == 0){
						if((M.at(r).size() - i) <= w)
							printf("%s\n", M.at(r).substr(i).c_str());
						else
							printf("%s ", M.at(r).substr(i, w).c_str());
					}
				}
			}
			if(w != 0 && ((r+1) % w == 0)){	
				if(M.size() % w != 0 || r != M.size()-1)
					printf("\n");
			}
		}
	}
}
            

/* Create a PGM file. Each entry is a p by p square (white for zero and 100 for gray)
 * If the border is greater than zero, then there should be a black border of that many pixels separating each square and around the whole matrix
 * Return true if successful and false if not. 
 *
 * 1. Zero entries are white(255) and one entries are gray(100)
 * 2. Each entry is a pixels by pixels square
 * 3. If border > 0, there should be black(0) border of that many pixels separating each square and around the whole matrix. */
bool Bitmatrix::PGM(const string &fn, int p, int border) const		//DO THIS LAST!!!
{
  (void) fn;
  (void) p;
  (void) border;
  return false;
}




//Return number of rows
int Bitmatrix::Rows() const
{
	return M.size();
}
//Return number of columns
int Bitmatrix::Cols() const
{
	return M.at(0).size();
}                          
/* Return specified element ('0' or '1')
 * Return 'x' if row or col is bad */
char Bitmatrix::Val(int row, int col) const
{
	(void) row;
	(void) col;

	//printf("M.size() = %lu\n", M.size());
	//printf("M.at(0).size() = %lu\n", M.at(0).size());
	
	if((unsigned int)row >= M.size() || (unsigned int)col >= M.at(0).size())
		return 'x';
	else
		return M[row][col];
}
            



/* Set the specified element to val.
 * Val must be 0, 1, '0', or '1'
 * If val is 0 or 1, store '0'/'1' in the matrix.
 * Return true if successful and false if not. */
bool Bitmatrix::Set(int row, int col, char val)
{
	(void) row;
	(void) col;
	(void) val;
	
	if((unsigned int)row >= M.size() || (unsigned int)col >= M.at(0).size()){
		return false;
	}
	
	if(val == 0 || val == '0')
		M[row][col] = '0';

	else if(val == 1 || val == '1')
		M[row][col] = '1';
	
	else
		return false;
  
	return true;
}
        

/* Swap these rows.  
 * Return true if successful and false if not. */
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
	(void) r1;
	(void) r2;
	string holder;

	if((size_t) r1 >= M.size() || (size_t) r2 >= M.size())
		return false;

	else{
		holder = M.at(r1);
		M.at(r1) = M.at(r2);
		M.at(r2) = holder;
	}
	return true;
}
              

/* Set the row r1 to the sum of row r1 and r2.
 * Rdjeturn true if successful and false if not. */
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
	(void) r1;
	(void) r2;
	int r1Char = 0;
	int r2Char = 0;
	stringstream ss;
  
	if((size_t) r1 >= M.size() || (size_t) r2 >= M.size())
		return false;

	else{
		for(unsigned int i = 0; i < M.at(r1).size(); i++){
			ss.clear();
			ss << M[r1][i];
			ss >> r1Char;
			ss.clear();
			ss << M[r2][i];
			ss >> r2Char;

			if((r1Char + r2Char) % 2 == 0)
				M[r1][i] = '0';
			else
				M[r1][i] = '1';

			r1Char = 0;
			r2Char = 0;
		}
	}
	return true;
}
      






/* Return true if successful and false if not.
 * They must be written using the methods of the Bitmatrix class above.
 * Return NULL if unsuccessful. 
 *
 * 1. You have to use Rows(), Cols(), Set(), and Val()*/

//Creates new bit-matrix which is the sum of a1 and a2
//Return NULL if a1 and a2 are NOT the same size
Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
	(void) a1;  
	(void) a2;
	stringstream ss;
	Bitmatrix *bm;
	int a1Char = 0;
	int a2Char = 0;

	if(a1->Rows() != a2->Rows() && a1->Cols() != a2->Cols())
		return NULL;
	
	bm = new Bitmatrix(a1->Rows(), a1->Cols());

	for(int r = 0; r < a1->Rows(); r++){
		for(int c = 0; c < a1->Cols(); c++){
			ss.clear();
			ss << a1->Val(r, c);
			ss >> a1Char;
			ss.clear();
			ss << a2->Val(r, c);
			ss >> a2Char;

			if((a1Char + a2Char) % 2 == 0)
				bm->Set(r, c, '0');
			else
				bm->Set(r, c, '1');

			a1Char = 0;
			a2Char = 0;
		}
	}
	return bm;
}

//Create new bit-matrix which is the products of a1 and a2
//a1->Rows() rows and a2->Cols() columns
//If a1->Cols() DOES NOT match a2->Rows(), return NULL
Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
	(void) a1; 
	(void) a2;
	stringstream ss;
	Bitmatrix *bm;
	int a1Char = 0;
	int a2Char = 0;
	int product = 0;

	//printf("a1 Row = %d\n", a1->Rows());
	//printf("a1 Col = %d\n", a1->Cols());
	//printf("a2 Row = %d\n", a2->Rows());
	//printf("a2 Col = %d\n", a2->Cols());

	if(a1->Cols() != a2->Rows())
		return NULL;

	bm = new Bitmatrix(a1->Rows(), a2->Cols());
	
	//printf("Rows: %d\n", bm->Rows());
	//printf("Cols: %d\n", bm->Cols());


	for(int r = 0; r < a1->Rows(); r++){	//a1->Rows()
		for(int bmCol = 0; bmCol < a2->Cols(); bmCol++){	//a2->Cols()
			
			for(int c = 0; c < a2->Rows(); c++){	//a2->Rows()
				ss.clear();
				ss << a1->Val(r, c);
				ss >> a1Char;
				ss.clear();
				ss << a2->Val(c, bmCol);
				ss >> a2Char;

				//printf("%d-%d-%d\n", r, bmCol, c);
				//printf("%d	%d\n", a1Char, a2Char);
				
				product = product + (a1Char * a2Char);
				//printf("product = %d\n", product);

				a1Char = 0;
				a2Char = 0;
			}

			//printf("%%2 = %d\n---------------------\n", product%2);

			if(product % 2 == 0)
				bm->Set(r, bmCol, '0');
			else
				bm->Set(r, bmCol, '1');
			
			product = 0;
		}
	}
	return bm;
}

//Creates new bit0matrix composed of the specified rows of the given bit-matrix
//It's ok to repeat entries in rows
//If rows is empty or contains bad indices, return NULL
Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
	(void) a1; 
	(void) rows;

	if(rows.size() == 0)
		return NULL;

	Bitmatrix *bm = new Bitmatrix(rows.size(), a1->Cols());

	for(unsigned int r = 0; r < rows.size(); r++){
		if(rows[r] < 0 || rows[r] >= a1->Rows())
			return NULL;

		for(int c = 0; c < a1->Cols(); c++)
			bm->Set(r, c, a1->Val(rows[r], c));
	}
	return bm;
}

//Create and return the inverse of a1
//Use Swap_Rows() and R1_Plus_Equals_R2()
//If a1 is not square or not invertible, return NULL
Bitmatrix *Inverse(const Bitmatrix *m)	//WORK ON THIS LAST!!! and check notes at bottom of writeup
{
  (void) m;
  return NULL;
}







/* HTE class - This is a "hash table entry". 
 * Our hash table stores vectors of pointers to these, using separate chaining.
 *	- string key;
 *	- Bitmatrix *bm;
 *
 * BM_Hash class - This is our bitmatrix hash table
 *	- vector <vector <HTE> > Table; = This is the hash table
 *		Each hash table entry has a key and a pointer to a bit-matrix
 *
 *
 * You are going to implement a hash table to store bit-matrices with keys that are strings.
 * Use the djb_hash() function from class as the hash function.
 * Use separate chaining as the collision resolution strategy.
 *
 * DO NOT call new or delete on bit-matrices when you implement any of the hash table methods
 *	*/


/* You specify the table size in the constructor.
 * Throw the string "Bad size" if (size <= 0). */
BM_Hash::BM_Hash(int size)
{
	(void) size;
	string err = "Bad size";

	if(size <= 0)
		throw(err);

	Table.resize(size);
}

/* Store a bitmatrix with the given key. 
 * Return true if successful and false if not. 
 * Return false if the key is already there. */
bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
	(void) key;
	(void) bm;

	size_t i;
	unsigned int h;

	HTE entry;
	entry.key = key;
	entry.bm = bm;
	
	//djb_hash()?
	h = 5381;
	for(i = 0; i < key.size(); i++){
		h = (h << 5) + h + key[i];
	}		
	h = h % Table.size();


	for(unsigned int j = 0; j < Table.size(); j++){
		for(unsigned int k = 0; k < Table[j].size(); k++){
			if(Table[j][k].key == key)
				return false;
		}
	}

	Table[h].push_back(entry);
	return true;
}

/* Retrieve a bitmatrix with the given key.
 * Return NULL if unsuccessful. */
Bitmatrix *BM_Hash::Recall(const string &key) const
{
	(void) key;
	
	for(unsigned int i = 0; i < Table.size(); i++){
		for(unsigned int j = 0; j < Table[i].size(); j++){
			if(Table[i][j].key == key)
				return Table[i][j].bm;
		}
	}
	return NULL;
}

//Return a vector of all of the hash table entries.
//Stores the entries in order
//		Ex. "A" hashes 5, "B" hashes 1, "C" hashes 1 but was added later --> Return HTE's in order "B", "C", "A"
vector <HTE> BM_Hash::All() const
{
	vector <HTE> rv;
  
	for(unsigned int i = 0; i < Table.size(); i++){
		for(unsigned int j = 0; j < Table[i].size(); j++){
			rv.push_back(Table[i][j]);
		}
	}
	
	return rv;
}
