/* Name: Sarah Huang
 * Date:
 * Program:
 * Purpose:
 */


#include <iostream>
#include <sstream>
using namespace std;


void do_enumeration(string &s, int index, int n_ones){
	if((int)s.size() == index && index == 0)
		return;

	if((int)s.size() == index){
		cout << s << endl;
		return;
	}


	//room to insert 0
	if( (index + n_ones) < (int)s.size()){
		s[index] = '0';
		index++;
		//cout << index << ", " << n_ones << endl;
		do_enumeration(s, index, n_ones);
		s[index] = '-';
		index--;

	}

	//not all 1s used
	if(n_ones != 0){
		s[index] = '1';
		index++;
		n_ones--;
		//cout << index << ", " << n_ones << endl;
		do_enumeration(s, index, n_ones);
		s[index] = '-';
	}
}


int main(int argc, char *argv[]){
	int length;		//The length of the string
	int ones;		//The number of 1s
	stringstream ss;

	if(argc != 3){
		return -1;
	}

	ss << argv[1];
	ss >> length;
	ss.clear();
	ss << argv[2];
	ss >> ones;
	string start(length, '-');
	
	do_enumeration(start, 0, ones);
	//cout << "we done with enum!" << endl;

	return 0;
}
