/* Name: Sarah Huang
 * Date: 
 * Program: bitmatrix_start.cpp
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
Bitmatrix::Bitmatrix(int rows, int cols)
{
	(void) rows;
	(void) cols;
	
	if(rows <= 0)
		throw("Bad rows");
	
	if(cols <= 0)
		throw("Bad cols");

	if(rows > 0 && cols > 0)
		M.resize(rows * cols);
}
           

/* Read the bitmatrix from a file.
 * Throw "Can't open file" if you can't open the file.
 * Throw "Bad file format" if you can't read the file. 
 *
 * 1. Blank lines are ignored
 * 2. Non-blank lines must be composed soley of zeroes, ones or whitespace
 * 3. Each non-blank line represents a row of the matrix (with whitespace ignored)
 * 4. Each row has hto have the same number of columns. */
Bitmatrix::Bitmatrix(const string &fn)
{
  (void) fn;
}


/* Create a new bitmatrix using new, which is a copy of the caller's bitmatrix
 * Return a pointer to it. */
Bitmatrix *Bitmatrix::Copy() const
{
  return NULL;
}
                 




/* Write to a file.  
 * You will print one line per row of the bitmatrix
 *	- Each line is only composed of 0's and 1's.
 * Return true if successful and false if not. */	                                            
bool Bitmatrix::Write(const string &fn) const
{
  (void) fn;
  return false;
}
 

/* Print on standard output.  
 * You will print one line per row of the bitmatrix.  
 *	- Each line is composed of 0's and 1's, and there will be a space after every w characters 
 *	- Don't put a space at the end if the number of columns is a multiple of w                                                                                                                              
 * Also put a blank line after every w rows (except the last, if the number of rows is a multiple of w). 
 *
 * 1. If w <= 0, print each row on its own line with no spaces.
 *	  Otherwise, print a space after every w columns and a blank line after every w rows.*/
void Bitmatrix::Print(size_t w) const
{
  (void) w;
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
  return -1;
}
//Return number of columns
int Bitmatrix::Cols() const
{
  return -1;
}                          
/* Return specified element ('0' or '1')
 * Return 'x' if row or col is bad */
char Bitmatrix::Val(int row, int col) const
{
  (void) row;
  (void) col;
  return 'x';
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
  return false;
}
        

/* Swap these rows.  
 * Return true if successful and false if not. */
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
  (void) r1;
  (void) r2;
  return false;
}
              

/* Set the row r1 to the sum of row r1 and r2.
 * Return true if successful and false if not. */
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
  (void) r1;
  (void) r2;
  return false;
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
  return NULL;
}

//Create new bit-matrix which is the products of a1 and a2
//a1->Rows() rows and a2->Cols() columns
//If a1->Cols() DOES NOT match a2->Rows(), return NULL
Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
  (void) a1;
  (void) a2;
  return NULL;
}

//Creates new bit0matrix composed of the specified rows of the given bit-matrix
//It's ok to repeat entries in rows
//If rows is empty or contains bad indices, return NULL
Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
  (void) a1;
  (void) rows;
  return NULL;
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
}

/* Store a bitmatrix with the given key. 
 * Return true if successful and false if not. 
 * Return false if the key is already there. */
bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
  (void) key;
  (void) bm;
  return false;
}

/* Retrieve a bitmatrix with the given key.
 * Return NULL if unsuccessful. */
Bitmatrix *BM_Hash::Recall(const string &key) const
{
  (void) key;
  return NULL;
}

//Return a vector of all of the hash table entries.
//Stores the entries in order
//		Ex. "A" hashes 5, "B" hashes 1, "C" hashes 1 but was added later --> Return HTE's in order "B", "C", "A"
vector <HTE> BM_Hash::All() const
{
  vector <HTE> rv;
  return rv;
}
