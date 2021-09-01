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

class FauxPalindromes {
  public:
    string classifyIt(string word);
};

string FauxPalindromes::classifyIt(string word)
{
	string reverse, word2, reverse2; 



	for(int i = word.size()-1; i >= 0; i--){
		reverse.push_back(word[i]);
	}
	if(word == reverse)
		return "PALINDROME";
	


	word2.push_back(word[0]);
	for(unsigned int j = 1; j < word.size(); j++){
		if(word[j] != word[j-1])
			word2.push_back(word[j]);
	}

	for(int k = word2.size()-1; k >= 0; k--){
		reverse2.push_back(word2[k]);
	}
	if(reverse2 == word2)
		return "FAUX";



	return "NOT EVEN FAUX";
}
