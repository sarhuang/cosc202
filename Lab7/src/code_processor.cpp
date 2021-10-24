/* Name: Sarah Huang
 * Date: 10/23/21
 * Program: code_processor.cpp
 * Purpose: Simulate a rewards program where users can accumulate points by collecting codes from various products.
 *			Users can enter codes via a web site, or they can register one or more cell phones with their account, 
 *			and then they can text codes from a given phone number, which will register the points.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include "code_processor.hpp"

using namespace std;


/* User:
 *		string username;				"jimplank"
 *		string realname;				"Jim Plank"
 *		int points;						//total number of points user has
 *		set <string> phone_numbers;		//phone numbers registered to user
 *
 * Prize:
 *		string id;						//unique string for each prize
 *		string description;				//longer description of each prize
 *		int points;						//# of points it takes to get prize
 *		int quantity;					//quantity of prizes
 */


/* Protected Variables:
 *	 map <string, User *> Names;	
 *	 map <string, User *> Phones;	 
 *	 set <string> Codes;
 *	 map <string, Prize *> Prizes;
 */



/*Creates a new prize and puts it into Prizes
	
  Error check:
	- There is already a prize with the given id in prizes.
	- Points is less than or equal to zero.
	- Quantity is less than or equal to zero.	*/
bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity){
	
	if(Prizes.find(id) != Prizes.end() || points <= 0 || quantity <= 0)
		return false;

	Prize *newPrize = new Prize;
	newPrize->id = id;
	newPrize->description = description;
	newPrize->points = points;
	newPrize->quantity = quantity;
	Prizes.insert(make_pair(id, newPrize));
	
	return true;
}


/*Creates a new user with the given information, and puts it into Names. 	
  The user will start with no registered phone numbers.
	
  Error check:
	- There is already a user with that username.
	- Starting_points is less than zero.	*/
bool Code_Processor::New_User(const string &username, const string &realname, int starting_points){
	
	if(Names.find(username) != Names.end() || starting_points < 0)
		return false;
	
	User *newUser = new User;
	newUser->username = username;
	newUser->realname = realname;
	newUser->points = starting_points;
	Names.insert(make_pair(username, newUser));
	
	return true;
}


/*Erase the user from Names, and it should erase all of the user's phone numbers from Phones. 
  After that, it should call delete on the user's pointer. 

  Error check:
	- If the username is not in Names	*/
bool Code_Processor::Delete_User(const string &username){
	map <string, User *>::iterator nit;
	
	if(Names.find(username) == Names.end())
		return false;

	for(nit = Phones.begin(); nit != Phones.end();){
		if(nit->second->username == username){
			Phones.erase(nit++);
		}
		else
			nit++;
	}

	delete Names.find(username)->second;
	Names.erase(username);
	
	return true;
}




/*Should register the given phone string with the user. 
  That means putting the phone on both the Phones map, and on the user's phone_numbers set

  Error check:
	- There is no user with that username.
	- The phone number is already registered, either with that user or with another	*/
bool Code_Processor::Add_Phone(const string &username, const string &phone){
	
	if(Names.find(username) == Names.end() || Phones.find(phone) != Phones.end())
		return false;

	Names.find(username)->second->phone_numbers.insert(phone);
	Phones.insert(make_pair(phone, Names.find(username)->second));
	
	return true;	
}


/*Remove the phone from the system -- both from Phones and from the user's phone_numbers set
	
  Error check:
	- There is no user with that username.
	- There is no phone string with that phone.
	- The phone number is registered to a different user.	*/
bool Code_Processor::Remove_Phone(const string &username, const string &phone){
	
	if(Names.find(username) == Names.end() || Phones.find(phone) == Phones.end())
		return false;

	if(Phones.find(phone)->second->username != username)
		return false;

	Names.find(username)->second->phone_numbers.erase(phone);
	Phones.erase(phone);
	
	return true;
}

/*Return a string containing all of that user's phone numbers, in lexicographic order, each separated by a newline. 
  There should be a newline at the end of the string too

  Error check:
	- user doesn't exist
	- user has no phones	*/
string Code_Processor::Show_Phones(const string &username) const{
	set <string>::const_iterator nit;
	string numbers;	//string with all user's phone numbers

	if(Names.find(username) == Names.end())
		return "BAD USER";

	if(Names.find(username)->second->phone_numbers.size() == 0)
		return "";
	
	for(nit = Names.find(username)->second->phone_numbers.begin(); nit != Names.find(username)->second->phone_numbers.end(); nit++){
		numbers += *nit;
		numbers += "\n";
	}

	return numbers;
}





//This is called when a user enters a code. 
//You need to first check the Codes set to see if the code has been entered before. 
//If it has, or if the user doesn't exist, return -1. 
//Otherwise, you need to check to see if the code is valid: 
//		A valid code's djbhash() must either be divisible by 17 or 13. 
//		If divisible by 17, then it is worth ten points. 
//		Otherwise, if it is divisible by 13, then it is worth three points. 
//
//If the code is valid, then add it to Codes, increment the user's account and return the number of points added.
int Code_Processor::Enter_Code(const string &username, const string &code){
	unsigned int h = 5381;

	if(Names.find(username) == Names.end() || Codes.find(code) != Codes.end())
		return -1;

	//djb hash
	for(unsigned int i = 0; i < code.size(); i++){
		h = (h << 5) + h + code[i];
	}

	if(h % 17 == 0){
		Names.find(username)->second->points += 10;
		Codes.insert(code);
		return 10;
	}
	else if(h % 13 == 0){
		Names.find(username)->second->points += 3;
		Codes.insert(code);
		return 3;
	}
	else
		return 0;
}


//This should work just like Enter_Code(), except the user's account is identified by the phone number.
int Code_Processor::Text_Code(const string &phone, const string &code){
	string username;	//Store the username to make it more readable
	unsigned int h = 5381;
	
	if(Phones.find(phone) == Phones.end() || Codes.find(code) != Codes.end())
		return -1;

	username = Phones.find(phone)->second->username;

	//djb hash
	for(unsigned int i = 0; i < code.size(); i++){
		h = (h << 5) + h + code[i];
	}

	if(h % 17 == 0){
		Names.find(username)->second->points += 10;
		Codes.insert(code);
		return 10;
	}
	else if(h % 13 == 0){
		Names.find(username)->second->points += 3;
		Codes.insert(code);
		return 3;
	}
	else
		return 0;
}


/*This is called to mark a code as used, even though no user is entering it. 
  Error check:
	- If the code is not valid or it is already in Codes	*/
bool Code_Processor::Mark_Code_Used(const string &code){
	unsigned int h = 5381;
	
	if(Codes.find(code) != Codes.end())
		return false;

	//djb hash
	for(unsigned int i = 0; i < code.size(); i++){
		h = (h << 5) + h + code[i];
	}

	if(h % 17 == 0 || h % 13 == 0){
		Codes.insert(code);
		return true;
	}
	else
		return false;
}





//Return user's points
//Error check if user doesn't exist
int Code_Processor::Balance(const string &username) const{
	
	if(Names.find(username) == Names.end())
		return -1;

	return Names.find(username)->second->points;
}


/*This is called when a user wants to redeem a prize. The prize is identified by its id.
  Decrement the points from the user's account
  Decrement the prize's quantity by one

  Error check:
	- If the user or prize don't exist
	- if the user doesn't have enough points	*/
bool Code_Processor::Redeem_Prize(const string &username, const string &prize){
	
	if(Names.find(username) == Names.end() || Prizes.find(prize) == Prizes.end())
		return false;

	if(Names.find(username)->second->points < Prizes.find(prize)->second->points)
		return false;
	else
		Names.find(username)->second->points -= Prizes.find(prize)->second->points;


	Prizes.find(prize)->second->quantity -= 1;
	if(Prizes.find(prize)->second->quantity == 0){
		delete Prizes.find(prize)->second;
		Prizes.erase(prize);
	}
	return true;
}



//write a destructor that calls delete on all the users and prizes. 
//The destructor doesn't have to clear the maps or sets 
Code_Processor::~Code_Processor(){
	map <string, User *>::iterator nit;
	map <string, Prize *>::iterator pit;

	for(nit = Names.begin(); nit != Names.end(); nit++){
		delete nit->second;
	}

	for(pit = Prizes.begin(); pit != Prizes.end(); pit++){
		delete pit->second;
	}
}


/* The Write() method should save the Code_Processor's state to the given file and return true. 
   It should return false if it can't open/create the file.
  
   The format of Write() should be as a file that cp_tester can use as input to recreate the state of the Code_Processor. 
   It should only consist of ADD_USER, PRIZE, ADD_PHONE and MARK_USED lines.
   When cp_tester is run with the file as input, it should recreate the state of the Code_Processor.	*/
bool Code_Processor::Write(const string &filename) const{
	ofstream ofs;									
	map <string, Prize *>::const_iterator pit;		//Prizes iterator
	map <string, User *>::const_iterator nit;		//Names iterator
	map <string, User *>::const_iterator phoneit;	//Phones iterator
	set <string>::const_iterator cit;				//Codes iterator

	string id;
	string description;
	int points;
	int quantity;
	
	string username;
	string realname;
	string phone;


	ofs.open(filename.c_str());
	if(!ofs)
		return false;
	
	
	for(pit = Prizes.begin(); pit != Prizes.end(); pit++){
		id = pit->first;
		description = pit->second->description;
		points = pit->second->points;
		quantity = pit->second->quantity;
		ofs << "PRIZE	" << id << "	" << points << "	" << quantity << "	" << description << endl;
	}

	for(nit = Names.begin(); nit != Names.end(); nit++){
		username = nit->first;
		realname = nit->second->realname;
		points = nit->second->points;
		ofs << "ADD_USER	" << username << "	" << points << "	" << realname << endl;
	}
	
	for(phoneit = Phones.begin(); phoneit != Phones.end(); phoneit++){
		username = phoneit->second->username;
		phone = phoneit->first;
		ofs << "ADD_PHONE	" << username << "	" << phone << endl;
	}

	for(cit = Codes.begin(); cit != Codes.end(); cit++){
		ofs << "MARK_USED	" << *cit << endl;
	}

	ofs.close();
	return true;
}
