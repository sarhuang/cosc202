#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class FoxAndWord {
  public:
    int howManyPairs(vector <string> words);
};

int FoxAndWord::howManyPairs(vector <string> words)
{
	int numPairs = 0;
	string a;
	string b;
	string c;
	string currentWord;
	string nextWord;
	
	//cout << "INPUT RECEIVED!" << endl;
	
	for(int j = 0; j < words.size(); j++){
		currentWord = words.at(j);
		//cout << "currentWord = " << currentWord << endl;
		
		for(int k = j+1; k < words.size(); k++){
			//currentWord = words.at(j);
			nextWord = words.at(k);
			//cout << "nextWord = " << nextWord << endl;

			for(int i = 1; i < currentWord.length(); i++){
			//substr() = return substring from given index to end
				a = currentWord.substr(0, i);
				b = currentWord.substr(i);
				c = b + a;
				//cout << c << endl;

				if(c == nextWord){
					numPairs++;
					break;
				}
			}
		}
	}
	

	return numPairs;
}
