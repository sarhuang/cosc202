/* Name: Sarah Huang
 * Date: 11/8/21
 * Program: enum.cpp
 * Purpose: Enumerate all strings of length length that contain ones ones, and (length-ones) zeros, and print them on standard output in sorted order
 */


#include <iostream>
#include <sstream>
using namespace std;


void do_enumeration(string &s, int index, int n_ones){
	//String's length is 0
	if((int) s.size() == index && index == 0)
		return;

	//No digits to add on
	if((int) s.size() == index){
		cout << s << endl;
		return;
	}


	//Room to insert 0
	if( (index + n_ones) < (int)s.size()){
		s[index] = '0';
		index++;
		do_enumeration(s, index, n_ones);
		s[index] = '-';
		index--;

	}

	//Not all 1s used
	if(n_ones != 0){
		s[index] = '1';
		index++;
		n_ones--;
		do_enumeration(s, index, n_ones);
		s[index] = '-';
	}
}



int main(int argc, char *argv[]){
	int length;		//The length of the string
	int ones;		//The number of 1s
	stringstream ss;

	//There should only be 2 parameters - length & ones
	if(argc != 3){
		return -1;
	}

	//Read input -> int
	ss << argv[1];
	ss >> length;
	ss.clear();
	ss << argv[2];
	ss >> ones;
	string start(length, '-');
	
	do_enumeration(start, 0, ones);
	return 0;
}
