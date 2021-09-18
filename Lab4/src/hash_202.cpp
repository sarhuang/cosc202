/* Name: Sarah Huang
 * Date: 9/
 * Program: hash_202.cpp
 * Purpose:
 */


#include "hash_202.hpp"
#include <sstream>
#include <cstdio>
using namespace std;


// vector <string> Keys;	Hash table of keys - strings of hex digits	
// vector <string> Vals;	Vals[i] is the val associated with Keys[i]	= same size as Keys

// size_t NKeys;			Number of keys that have been inserted
// int Fxn;					Hash function. 'X' = 'XOR' and 'L' = 'Last7'
// int Coll;				Collision resolution strategy. 'L' and 'D'
// size_t Nprobes;			When you call Find(), set this value to the number of probes:



string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{
	//Takes the hash table size, a name of a hash function (Last7 or XOR), and name of a collision resolution strategy (Linear or Double)
	//Error check input and look for erros in the following order.
	//		- Table already set up					"Hash table already set up"
	//		- Bad table size						"Bad table size"
	//		- Bad hash function						"Bad hash function"
	//		- Bad collision resolution strategy		"Baed collision resolution strategy"


	(void) table_size;
	(void) fxn;
	(void) collision;
	Nprobes = 0;
	
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




string Hash_202::Add(const string &key, const string &val)
{
	//Adds the given key/val pair to the hash table
	//If successful, return an empty string
	//Error check in the order
	//		- Table not set up					"Hash table not set up"
	//		- Empty string for key				"Empty key"
	//		- Key not composed of hex digits	"Bad key (not all hex digits)"
	//		- Empty string for the val			"Empty val"
	//		- Hash table is full				"Hash table full"
	//		- Cannot insert key					"Cannot insert key"
	//		- Key is already in the table		"Key already in the table"

	(void) key;
	(void) val;
	int hexInt;
	istringstream ss;
	size_t holder = 0;
	string key2;
	int origIndex = 0;
	int newIndex = 0;
	size_t counter = 0;
	int XORresult = 0;
	
	if(Keys.size() == 0)
		return "Hash table not set up";
	
	else if(key == "")
		return "Empty key";

	
	//0-9 --> 16-25
	//a-f --> 65-70
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] < '0')
			return "Bad key (not all hex digits)";

		if(key[i] > '9' && key[i] < 'a')
			return "Bad key (not all hex digits)";
			
		if(key[i] > 'f'){
			return "Bad key (not all hex digits)";
		}
	
	}

	if(val == "")
		return "Empty val";


	for(unsigned int j = 0; j < Keys.size(); j++){
		if(Keys[j] != "")
			holder++;
	}
	if(holder == Keys.size())
		return "Hash table full";
	else
		holder = 0;


	//LAST7
	if(Fxn == 'L'){	
		if(key.size() < 7){
			ss.str(key);
			ss >> hex >> hexInt;
		}
		else{
			key2 = key.substr(key.size() - 7);
			ss.str(key2);
			ss >> hex >> hexInt;
		}
	}
	//XOR
	else{
		//printf("key.size() = %lu\n", key.size());

		for(unsigned int n = 0; n < key.size(); n++){
			if(n % 7 == 0 && n != 0){
				key2 = key.substr(n-7, n);
				//printf("key2 = %s\n", key2.c_str());
				ss.str(key2);
				ss >> hex >> holder;
				//printf("holder = %lu\n", holder);
				//printf("XORresult before = %d\n", XORresult);
				XORresult = XORresult ^ holder;
				//printf("XORresult after = %d\n", XORresult);
				counter++;
			}
		}
		if((counter*7) < key.size()){
			key2 = key.substr(counter*7);
			//printf("--------------\nkey2 (not 7 digits) = %s\n", key2.c_str());
			ss.clear();
			ss.str(key2);
			ss >> hex >> holder;
			//printf("holder = %lu\n", holder);
			//printf("XORresult before = %d\n", XORresult);
			XORresult = XORresult ^ holder;
			//printf("XORresult after = %d\n", XORresult);
		}
		hexInt = XORresult;
	}

	printf("hexInt = %d and Keys.size() = %lu SO... index = %lu\n", hexInt, Keys.size(), hexInt % Keys.size());

	
	origIndex = hexInt % Keys.size();
	
	holder = 0;
	newIndex = 0;
	counter = 0;
	
	
	//COLLISION
	if(Keys[hexInt % Keys.size()] != ""){
		//LINEAR
		if(Coll == 'L'){
			for(unsigned int k = 0; k < Keys.size(); k++){
				Nprobes++;
				holder = (hexInt + k) % Keys.size();
				if(Keys[holder] == ""){
					Keys[holder] = key;
					Vals[holder] = val;
					return "";
				}
			}
			return "Key already in the table";
		}

		//DOUBLE
		else{
			do{			
				//first XOR, now LAST7
				if(Fxn == 'X'){
					if(key.size() < 7){
						ss.str(key);
						ss >> hex >> holder;
					}
					else{
						key2 = key.substr(key.size() - 7);
						ss.str(key2);
						ss >> hex >> holder;
					}
				}

				//XOR --> LAST7
				else{
					for(unsigned int m = 0; m < key.size(); m++){
						if(m % 7 == 0 && m != 0){
							key2 = key.substr(m-7, m);
							ss.str(key2);
							ss >> hex >> holder;
							newIndex = newIndex ^ holder; 
							counter++;
						}
					}
					if((counter*7) < key.size()){
						key2 = key.substr(counter*7);
						ss.clear();
						ss.str(key2);
						ss >> hex >> holder;
						newIndex = newIndex ^ holder;
					}
					holder = newIndex;
				}


				printf("holder = %lu\n", holder);
				
				newIndex = holder % Keys.size();
				printf("newIndex before = %d\n", newIndex);
				
				
				newIndex = (hexInt + newIndex) % Keys.size();
				printf("newIndex after = %d\n", newIndex);

				Nprobes++;
				if(Keys[newIndex] == ""){
					Keys[newIndex] = key;
					Vals[newIndex] = val;
					return "";
				}
		
			}while(newIndex != origIndex);
			return "Cannot insert key";
		}
	}
	else{
		Keys[hexInt % Keys.size()] = key;
		Vals[hexInt % Vals.size()] = val;
	}
	
	
	//printf("Keys[%lu] = %s\n", hexInt % Keys.size(), key.c_str());
	//printf("Vals[%lu] = %s\n", hexInt % Vals.size(), val.c_str());
	//printf("Nprobes = %lu\n", Nprobes);
	
	return "";
}




string Hash_202::Find(const string &key)
{
	//Returns val associated with given key
	//Return empty string if...
	//	- Hash table hsa not been set up
	//	- Key is not in hash table
	//	- Key is not composed of all hex digits
	//Sets the variable Nprobes to equal the number of probes that it took to find the answer
	
	(void) key;
	string val = "";
	

	if(Keys.size() == 0)
		return val;

	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] < '0')
			return val;

		if(key[i] > '9' && key[i] < 'a')
			return val;

		if(key[i] > 'f')
			return val;
	}

	for(unsigned int j = 0; j < Keys.size(); j++){
		if(Keys[j] == key)
			val = Vals[j];
	}
	//if(val == "")
	//	Nprobes++;
	
	
	return val;
}




void Hash_202::Print() const
{
	//Prints all non-empty slots in hash table, one per line
	//Index should be printed first, justified and padded to 5 characters
	//Space, key, space, val (do nothing if hash table has not been set up)
	
	if(Keys.size() != 0){
		for(unsigned int i = 0; i < Keys.size(); i++){
			if(Keys[i] != ""){
				printf("%5d %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
			}
		}
	}
}




size_t Hash_202::Total_Probes()
{	
	//Traverse hash table & for every key, calculate how many probes it takes to find that key
	//Return total number of probes or return 0 if the hash table hsa not been set up
	//Use Find() to find the number of probes for each key
	
	int total = 0;

	if(Keys.size() != 0){
	/*	for(unsigned int i = 0; i < Keys.size(); i++){
			if(Find(Keys[i]) == Vals[i]){
				printf("Nprobes = %lu\n", Nprobes);
				total += Nprobes;
			}
		}*/
		total += Nprobes;
	}

	return total;
}
