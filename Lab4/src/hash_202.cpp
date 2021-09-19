#include "hash_202.hpp"
#include <sstream>
#include <cstdio>
using namespace std;



string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string & collision){
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



string Hash_202::Add(const string &key, const string &val){
	(void) key;
	(void) val;
	istringstream ss;
	size_t counter = 0;	//Count stuff
	int hexInt = 0;		//Hexidecimal string as integer
	string sevenDigits;		//Placeholder for 7 char digits
	int xorHash = 0;	//Result of XOR
	int origIndex = 0;	//Original place where hash was supposed to go
						// - For Double, if it gets back to the original, it's over
	int origHex = 0;
	int newIndex = 0;
	size_t loopRepeat = 0;
	int currProbes = 0;


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


	for(unsigned int z = 0; z < Keys.size(); z++){
		if(Keys[z] != "")
			counter++;
	}
	if(counter == Keys.size())
		return "Hash table full";
	else 
		counter = 0;
	
//	printf("\n\nKEY: %s\n", key.c_str());
	
	//LAST7
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
	//XOR
	else{
		for(unsigned int k = 0; k < key.size(); k++){
			if(k % 7 == 0 && k != 0){
				sevenDigits = key.substr(k-7, k);
				
				if(sevenDigits.size() != 7){
					sevenDigits = sevenDigits.substr(0, 7);
				}
					

//				printf("sevenDigits (XOR 1st function) = %s\n", sevenDigits.c_str());
				
				
				ss.clear();
				ss.str(sevenDigits);
				ss >> hex >> hexInt;
//				printf("hexInt = %d\n", hexInt);
				
				xorHash = xorHash ^ hexInt;
//				printf("xorHash = %d\n", xorHash);

				counter++;
			}
		}
		if((counter*7) < key.size()){
			sevenDigits = key.substr(counter*7);
//			printf("Last sevenDigits (XOR 1st function) = %s\n", sevenDigits.c_str());
			ss.clear();
			ss.str(sevenDigits);
			ss >> hex >> hexInt;
//			printf("hexInt = %d\n", hexInt);

			xorHash = xorHash ^ hexInt;
//			printf("xorHash = %d\n", xorHash);
		}
		hexInt = xorHash;
		counter = 0;
	}


	//Resetting variables just in case
	origHex = hexInt;
	origIndex = hexInt % Keys.size();
//	printf("origHex OG = %d as well as origIndex = %d\n", origHex, origIndex);
	xorHash = 0;

	
	//DETECT COLLISIONS
	if(Keys[origIndex] == ""){
		Keys[origIndex] = key;
		Vals[origIndex] = val;
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
				else if(Keys[counter] == key){
					Nprobes -= currProbes;
					return "Key already in the table";
					//return "Hash table full";
				}

				Nprobes++;
				currProbes++;
			}
			Nprobes -= currProbes;
			return "Hash table full";
		}
		//DOUBLE HASING
		else{
			if(Fxn == 'L'){
				for(unsigned n = 0; n < key.size(); n++){
					if(n % 7 == 0 && n != 0){
						sevenDigits = key.substr(n-7, n);
						if(sevenDigits.size() != 7)
							sevenDigits = sevenDigits.substr(0, 7);
						
//						printf("sevenDigits = %s\n", sevenDigits.c_str());
					
						ss.clear();
						ss.str(sevenDigits);
						ss >> hex >> hexInt;
//						printf("hexInt 7s = %d\n", hexInt);
						xorHash = xorHash ^ hexInt;
//						printf("xorHash 7s = %d\n", xorHash);
						counter++;
					}
				}
				if((counter*7) < key.size()){
					sevenDigits = key.substr(counter*7);
//					printf("sevenDigits = %s\n", sevenDigits.c_str());
					ss.clear();
					ss.str(sevenDigits);
					ss >> hex >> hexInt;
//					printf("hexInt last = %d\n", hexInt);
					xorHash = xorHash ^ hexInt;
//					printf("xorHash last one = %d\n", xorHash);
				}
				hexInt = xorHash;
				counter = 0;
			}
			//1st function XOR, 2nd function Last7
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
//			printf("newIndex 2nd function = %d\n", newIndex);
			
	
			int result = 0;
						
			for(loopRepeat = 0; loopRepeat < Keys.size(); loopRepeat++){
				//printf("Nprobes = %lu\n", Nprobes);
//				printf("LOOP REPEAT = %lu\n", loopRepeat);
				

				
//				printf("newIndex before = %d\n", newIndex);
//				printf("origHex = %d\n", origHex);

				result = (origHex + (newIndex * loopRepeat)) % Keys.size();
				
//				printf("result = %d\n", result);

				if(Keys[result] == ""){
					Keys[result] = key;
					Vals[result] = val;
//					printf("OUT OF THE LOOP!\n");
					//printf("Nprobes = %lu\n", Nprobes);
					return "";
				}
				else if(Keys[result] == key){
					Nprobes -= currProbes;
					return "Key already in the table";
				}

				Nprobes++;
				currProbes++;
			}
		
//			printf("error check at the end\n");
			counter = 0;
			for(unsigned int s = 0; s < Keys.size(); s++){
				if(Keys[s] != "")
					counter++;
			}
			if(counter < Keys.size()){
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



string Hash_202::Find(const string &key){
	(void) key;
	
	
	if(Keys.size() == 0)
		return "";
	for(unsigned int i = 0; i < key.size(); i++){
		if(key[i] < '0' || (key[i] > '9' && key[i] < 'a') || key[i] > 'f')
			return "";
	}

	for(unsigned int j = 0; j < Keys.size(); j++){
		if(Keys[j] == key)
			return Vals[j];
	}

	return "";
}



void Hash_202::Print() const{
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
		//for(unsigned int i = 0; i < Keys.size(); i++){
		//	if(Find(Keys[i]) != "")
		//		total += Nprobes;
		//}
		total = Nprobes;
	}

	return total;
}
