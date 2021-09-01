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

class MagicalStringDiv2 {
  public:
    int minimalMoves(string S);
};

int MagicalStringDiv2::minimalMoves(string S)
{	
  //index < S.size()/2 is not '>'
  //index >= S.size()/2 is not '<'

	int moves = 0;


	for(int i = 0; i < S.size(); i++){
		
		if(i < S.size()/2 && S[i] == '<')
			moves += 1;
		else if(i >= S.size()/2 && S[i] == '>')
			moves += 1;
	}

	
	return moves;
}
