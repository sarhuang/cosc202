

#include "hash_202.hpp"
#include <sstream>
#include <cstdio>
using namespace std;



string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string & collision){
	(void) table_size;
	(void) fxn;
	(void) collision;
	
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



string Hash_202::Add(const string &key, const string &val){
	(void) key;
	(void) val;
	istringstream ss;
	size_t counter = 0;	//Count stuff
	int hexInt = 0;		//Hexidecimal string as integer
	string 7digits;		//Placeholder for 7 char digits
	int xorHash = 0;	//Result of XOR
	int origIndex = 0;	//Original place where hash was supposed to go
						// - For Double, if it gets back to the original, it's over
	int origHex = 0;
	int newIndex = 0;


	//ERROR CHECKING
	if(Keys.size() == 0)
		return "Hash table not set up";
	else if(key == "")
		return "Empty key";
	for(unsigned int int i = 0; i < key.size(); i++){
		if(key[i] < '0' || (key[i] > '9' && key[i] < 'a') || key[i] > 'f')
			return "Bad key (not all hex digits)";
	}
	if(val == "")
		return "Empty val";
	

	//LAST7
	if(Fxn == 'L'){
		if(key.size() < 7){
			ss.str(key);
			ss >> hex >> hexInt;
		}
		else{
			7digits = key.substr(key.size() - 7);
			ss.str(7digits);
			ss >> hex >> hexInt;
		}
	}
	//XOR
	else{
		for(unsigned int k = 0; k < key.size(); k++){
			if(k % 7 == 0 && k != 0){
				7digits = key.substr(k-7, k);
				ss.str(7digits);
				ss >> hex >> hexInt;
				xorHash = xorHash ^ hexInt;
				counter++;
			}
		}
		if((counter*7) < key.size()){
			7digits = key.substr(counter*7);
			ss.clear();
			ss.str(7digits);
			ss >> hex >> hexInt;
			xorHash = xorHash ^ hexInt;
		}
		hexInt = xorHash;
		counter = 0;
	}

	//Resetting variables just in case
	origHex = hexInt;
	origIndex = hexInt % Keys.size();
	xorHash = 0;

	
	//DETECT COLLISIONS
	if(Keys[hexInt % Keys.size()] == ""){
		Keys[hexInt % Keys.size()] = key;
		Vals[hexInt % Vals.size()] = val;
	}
	else{
		//LINEAR
		if(Coll == 'L'){
			for(unsigned int m = 0; m < Keys.size(); m++){
				counter = (hexInt + m) % Keys.size();
				if(Keys[counter] == ""){
					Keys[counter] = key;
					Vals[counter] = val;
					return "";
				}
				else if(Keys[counter] == key)
					return "Key already in the table";
			}
			return "Hash table full";
		}
		//DOUBLE HASING
		else{
			do{
				//1st function Last7, 2nd function XOR
				if(Fxn == 'L'){
					for(unsigned n = 0; n < key.size(); n++){
						if(n % 7 == 0 && n != 0){
							7digits = key.substr(n-7, n);
							ss.str(7digits);
							ss >> hex >> hexInt;
							xorHash = xorHash ^ hexInt;
							counter++;
						}
					}
					if((counter*7) < key.size()){
						7digits = key.substr(n-7, n);
						ss.clear();
						ss.str(7digits);
						ss >> hex >> hexInt;
						xorHash = xorHash ^ hexInt;
					}
					hexInt = xorHash;
					counter = 0;
				}
				//1st function XOR, 2nd function Last7
				else{
					if(key.size() < 7){
						ss.str(key);
						ss >> hex >> hexInt;
					}
					else{
						7digits = key.substr(key.size() - 7);
						ss.str(7digits);
						ss >> hex >> hexInt;
					}
				}
				newIndex = hexInt % Keys.size();
				if(newIndex == 0)
					newIndex = 1;

				newIndex = (origHex + newIndex) % Keys.size();

				if(Keys[newIndex] == ""){
					Keys[newIndex] = key;
					Vals[newIndex] = val;
					return "";
				}
			}while(newIndex != origIndex);
			return "Cannot insert key";
		}
	}
	return "";
}



string Hash_202::Find(const string &key){
	(void) key;
	int index = 0;
	
	if(Keys.size() == 0)
		return "";
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] < '0' || (key[i] > '9' && key[i] < 'a') || key[i] > 'f')
			return "";
	}

	for(int j = 0; j < Keys.size(); j++){
		
		
		if(Keys[j] == key)
			return Vals[j];
	}
	return "";
}



string Hash_202::Print() const{
	if(Keys.size() != 0){
		for(unsigned int i = 0; i < Keys.size(); i++){
			if(Keys[i] != "")
				printf("%5d %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
		}
	}
}




size_t Hash_202::Total_Probes(){
	int total = 0;

	if(Keys.size() != 0){
		for(unsigned int i = 0; i < Keys.size(); i++){
			if(Find(Keys[i] != "")
				total += Nprobes;
		}
	}

	return total;
}
