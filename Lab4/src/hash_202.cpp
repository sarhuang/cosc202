/* Name: Sarah Huang
 * Date: 9/19/21
 * Program: hash_202.cpp
 * Purpose: Simulate a hash table and implement hash functions (Last7 and XOR) and collision resolution strategies (Linear and Double).
 */

#include "hash_202.hpp"
#include <sstream>
#include <cstdio>
using namespace std;


/*	Remember that you have these variables at your disposal from "hash_202.hpp"!
 *		vector <string> Keys;	- The hash table of keys
 *		vector <string> Vals;	- Vals[i] is the val associated with Keys[i]
 *		size_t Nkeys;			- Number of keys that have been inserted
 *		int Fxn;				- Hash function -> 'X' for XOR or 'L' for Last7
 *		int Coll;				- Collision resolution strategy -> 'L' for Linear Probing or 'D' for Double Hasing
 *		size_t Nprobes;			- Number of probes	*/





/* Set_Up() - SETS UP THE HASH TABLE
 *
 * This method takes... 
 *		1. Hash table size, 
 *		2. Name of a hash function (either "Last7" or "XOR")
 *		3. Name of a collision resolution strategy (either "Linear" or "Double")
 *                
 * You should error check your input, and look for the following errors, in the following order.  
 * If you see one of these errors, return the string specified:
 *       - Table already set up:                "Hash table already set up"
 *       - Bad table size:                      "Bad table size"
 *       - Bad hash function:                   "Bad hash function"
 *       - Bad collision resolution strategy:   "Bad collision resolution strategy" */

string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string & collision){
	(void) table_size;	//Size of the hash table
	(void) fxn;			//Hash function name (either 'Last7' or 'XOR')
	(void) collision;	//Collision resolution strategy (either 'Linear' Probing or 'Double' Hasing)
	Nkeys = 0;
	Nprobes = 0;

	//ERROR CHECKING
	if(Keys.size() != 0)
		return "Hash table already set up";
	else if(table_size == 0)
		return "Bad table size";
	else if(fxn != "XOR" && fxn != "Last7")
		return "Bad hash function";
	else if(collision != "Linear" && collision != "Double")
		return "Bad collision resolution strategy";

	Keys.resize(table_size);
	Vals.resize(table_size);

	if(fxn == "XOR")
		Fxn = 'X';
	else
		Fxn = 'L';

	if(collision == "Linear")
		Coll = 'L';
	else
		Coll = 'D';

	return "";
}




/* Add() - ADDS THE GIVEN KEY/VAL PAIR TO THE HASH TABLE
 *
 * If successful, it should return an empty string.  
 *
 * Add should test for the following errors, in this order, and return the given strings:
 *	 - Table not set up:                "Hash table not set up"
 *	 - Empty string for the key:        "Empty key"
 *	 - Key not composed of hex digits:  "Bad key (not all hex digits)"
 *	 - Empty string for the val:        "Empty val"
 *	 - The hash table is full:          "Hash table full"
 *	 - Cannot insert key:               "Cannot insert key"
 *	 - The key is already in the table  "Key already in the table"	*/

string Hash_202::Add(const string &key, const string &val){
	(void) key;				//Hexidecimal hash as a string (input)
	(void) val;				//Value that's going to be put in table (input)

	istringstream ss;		//Stringstream - to convert hex string to hex int
	int hexInt = 0;			//Hexidecimal string as integer
	int xorHash = 0;        //Result of XOR hash function
	int origIndex = 0;      //Index calculated by the 1st hash function
	int origHex = 0;        //Hexidecimal int calculated by 1st hash function
	int newIndex = 0;       //Index calculated by the 2nd hash function
	size_t loopRepeat = 0;  //The incrementing variable aka the 'i' for Double Hashing (H2*i)
	int currProbes = 0;		//Current number of probes (used to cancel total if it doesn't count)

	size_t counter = 0;     //Count stuff, general purpose integer
	string sevenDigits;		//Placeholder for 7 char digits
	int result = 0;         //Placeholder for the new index after the Double Hash formula
	

	//ERROR CHECKING
	if(Keys.size() == 0)
		return "Hash table not set up";
	else if(key == "")
		return "Empty key";
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] < '0' || (key[i] > '9' && key[i] < 'a') || key[i] > 'f')
			return "Bad key (not all hex digits)";
	}
	if(val == "")
		return "Empty val";
	if(Nkeys == Keys.size())
		return "Hash table full";
	

	//LAST7 - Grabs the last 7 characters of the hex (or all if less than 7) and convert to int.
	if(Fxn == 'L'){
		if(key.size() < 7){
			ss.str(key);
			ss >> hex >> hexInt;
		}
		else{
			sevenDigits = key.substr(key.size() - 7);
			ss.str(sevenDigits);
			ss >> hex >> hexInt;
		}
	}

	//XOR - Separates the hex in groups of 7, convert to int, and XOR (^) them all.
	else{
		for(unsigned int k = 0; k < key.size(); k++){
			if(k % 7 == 0 && k != 0){
				sevenDigits = key.substr(k-7, k);

				//Sometimes it grabs 8 digits instead of 7
				if(sevenDigits.size() != 7)			
					sevenDigits = sevenDigits.substr(0, 7);

				ss.clear();
				ss.str(sevenDigits);
				ss >> hex >> hexInt;
				xorHash = xorHash ^ hexInt;
				counter++;
			}
		}
		if((counter*7) < key.size()){
			sevenDigits = key.substr(counter*7);
			ss.clear();
			ss.str(sevenDigits);
			ss >> hex >> hexInt;
			xorHash = xorHash ^ hexInt;
		}
		hexInt = xorHash;
		counter = 0;
	}


	//In case there is a collision, store the 1st hash function results
	origHex = hexInt;
	origIndex = hexInt % Keys.size();
	xorHash = 0;

	/*COLLISION RESOLUTION STRATEGY
	 * 1. No collision	 - Set key and value at index calculated by 1st hash function
	 * 2. Linear Probing - Cycle through the hash table and find an empty spot. 
	 * 3. Double Hashing:
	 *		- 1st function Last7, 2nd function XOR
	 *		- 1st function XOR, 2nd function Last7
	 *
	 *		If 2nd function index equals 0, set it to 1.
	 *
	 *		newIndex = (firstFunctionHex + (secondFunctionHex * i)) % hashTableSize
	 *		Increment i until you get it or it goes through the hash table.
	 */

	if(Keys[origIndex] == ""){
		Keys[origIndex] = key;
		Vals[origIndex] = val;
		Nkeys++;
	}
	else{
		//LINEAR PROBING
		if(Coll == 'L'){
			for(unsigned int m = 0; m < Keys.size(); m++){
				counter = (hexInt + m) % Keys.size();

				if(Keys[counter] == ""){
					Keys[counter] = key;
					Vals[counter] = val;
					Nkeys++;
					return "";
				}
				else if(Keys[counter] == key){
					Nprobes -= currProbes;
					return "Key already in the table";
				}
				Nprobes++;
				currProbes++;
			}
			Nprobes -= currProbes;
			return "Hash table full";
		}

		//DOUBLE HASHING
		else{
			//Last7 --> XOR (same process like 1st hash function)
			if(Fxn == 'L'){
				for(unsigned n = 0; n < key.size(); n++){
					if(n % 7 == 0 && n != 0){
						sevenDigits = key.substr(n-7, n);
						if(sevenDigits.size() != 7)
							sevenDigits = sevenDigits.substr(0, 7);
						ss.clear();
						ss.str(sevenDigits);
						ss >> hex >> hexInt;
						xorHash = xorHash ^ hexInt;
						counter++;
					}
				}
				if((counter*7) < key.size()){
					sevenDigits = key.substr(counter*7);
					ss.clear();
					ss.str(sevenDigits);
					ss >> hex >> hexInt;
					xorHash = xorHash ^ hexInt;
				}
				hexInt = xorHash;
				counter = 0;
			}
			//XOR --> Last7 (same process like 1st hash function)
			else{
				if(key.size() < 7){
					ss.clear();
					ss.str(key);
					ss >> hex >> hexInt;
				}
				else{
					sevenDigits = key.substr(key.size() - 7);
					ss.clear();
					ss.str(sevenDigits);
					ss >> hex >> hexInt;
				}
			}


			newIndex = hexInt % Keys.size(); 
			if(newIndex == 0)
				newIndex = 1;

			//Double Hashing formula
			for(loopRepeat = 0; loopRepeat < Keys.size(); loopRepeat++){
				result = (origHex + (newIndex * loopRepeat)) % Keys.size();

				if(Keys[result] == ""){
					Keys[result] = key;
					Vals[result] = val;
					Nkeys++;
					return "";
				}
				else if(Keys[result] == key){
					Nprobes -= currProbes;
					return "Key already in the table";
				}
				Nprobes++;
				currProbes++;
			}

			//ERROR CHECKING - if the double hashing doesn't work or it's full
			if(Nkeys < Keys.size()){
				Nprobes -= currProbes;
				return "Cannot insert key";
			}
			else{
				Nprobes -= currProbes;
				return "Hash table full";
			}
		}
	}
	return "";
}




/* Find() - RETURNS THE VAL ASSOCIATED WITH THE GIVEN KEY
 *
 * Return an empty string "" if the hash table...
 *		1. Has not been set up yet
 *		2. The key is not in the hash table
 *		3. The key is not composed of all hex digits
 *
 * Find() ALSO sets the variables Nprobes to equal the number of probes it took to find the answer */

string Hash_202::Find(const string &key){
	(void) key;		//Hexidecimal string

	//ERROR CHECKING
	if(Keys.size() == 0)
		return "";
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] < '0' || (key[i] > '9' && key[i] < 'a') || key[i] > 'f')
			return "";
	}
	
	
	for(unsigned int j = 0; j < Keys.size(); j++){		
		if(key == Keys[j])
			return Vals[j];
	}
	return "";
}



/* Print() - PRINTS ALL NON-EMPTY SLOTS IN THE HASH TABLE, ONE PER LINE.
 *
 *	1. The index should be printed first, right justified and padded to five characters. 
 *  2. Then a space, the key, a space, and the val, 
 *
 *  This should do nothing if the hash table has not been set up yet.	*/

void Hash_202::Print() const{
	if(Keys.size() != 0){
		for(unsigned int i = 0; i < Keys.size(); i++){
			if(Keys[i] != "")
				printf("%5d %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
		}
	}
}




/* Total_Probes() - CALCULATE HOW MANY PROBES IT TAKES TO FIND EACH KEY AND ADD THEM ALL UP.
 * 
 * Return 0 if the hash table has not been set up yet.	*/

size_t Hash_202::Total_Probes(){
	int total = 0;	//Total number of probes

	if(Keys.size() != 0){
		for(unsigned int i = 0; i < Keys.size(); i++){
			if(Keys[i] != ""){
				total = Nprobes;
			}
		}
	}
	return total;
}
