/* Name: Sarah Huang
 * Date: 
 * Program: dlist.cpp
 * Purpose:
 */


#include <iostream>
#include "dlist.hpp"

using namespace std;


/*	class Dnode {
 *		friend class Dlist;
 *	    
 *		public:
 *	        string s;		
 *			Dnode *Next();	- Returns d->flink
 *	        Dnode *Prev();	- Returns d->blink
 *	    
 *	    protected:
 *	        Dnode *flink;	- Points to the next node in the list		
 *			Dnode *blink;	- Points to the previous node in the list
 *	};
 *
 *	
 *	protected:
 *		Dnode *sentinel;	- Extra node which begins (and ends) each list
 *		size_t size;		- If a list contains size elements, it will contain size+1 nodes
 */


//Constructor
Dlist::Dlist(){
	Dnode *sentinel = new Dnode;
	sentinel->flink = sentinel->blink;
}

//Copy Constructor
Dlist::Dlist(const Dlist &d){
	Dnode *sentinel = new Dnode;
	*this = d;
}

//Assignment Overload
Dlist::Dlist& operator= (const Dlist &d){
	Dlist tmp;
	Dnode *n;
	
	Clear();

	for(n = d.Begin(); n != d.End(); n->Next()){
		tmp.Push_Back(d->n->s);
	}

	//while (!tmp.Empty()) Push(tmp.Pop());

	return *this;
}

//Destructor
Dlist::~Dlist(){
	Clear();
	delete sentinel;
}



//Erase all nodes but sentinel
void Dlist::Clear(){
	//do not delete sentinel node
	Dnode *d;

	for(d = sentinel->flank; d != sentinel; d = d->Next()){
		delete d;
	}

	size = 1;
}

bool Dlist::Empty() const{
	if(size != 0)
		return false;
	else
		return true;
}

size_t Dlist::Size() const{
	return size;
}




//Put new strings on the front of list
void Dlist::Push_Front(const std::string &s){
	//use Insert_Before()
	Dnode *n = new Dnode;
	Dnode *prev;
	Dnode *newnode = new Dnode;

	n = sentinel->flink;
	prev = n->blink;
	newnode->s = s;

	newnode->flink = prev->flink;
	newnode->blink = n->blink;
}

//Put new strings on the back of the list
void Dlist::Push_Back(const std::string &s){
	//use Insert_After()
	Dnode *n = new Dnode;
	Dnode *next;
	Dnode *newnode = new Dnode;

	n = sentinel;
	next = n->flink;
	newnode->s = s;

	newnode->flink = next->blink;
	newnode->blink = n->flink;
}




//Return first element of list
string Dlist::Pop_Front(){
	//use Erase()
	Dnode *n = new Dnode;
	string val;

	n = sentinel->flank;
	val = n->s;

	Dnode *prev;
	Dnode *next;

	prev = n->Prev();
	next = n->Next();

	next->blink = prev->flink;
	next->flink = prev->blink;

	delete n;
	size--;

	return val;
}

//Return last element of list
string Dlist::Pop_Back(){
	//use Erase()
	Dnode *n = new Dnode;
	string val;

	n = sentinel;
	val = n->s;

	Dnode *prev;
	Dnode *next;

	prev = n->Prev();
	next = n->Next();

	next->blink = prev->flink;
	next->flink = prev->blink;

	delete n;
	size--;

	return val;
}




//pointer to the first node on the list
Dnode Dlist::*Begin() const{
	return sentinel->flink;
}

//Pointer to "one past" the last node of the list
Dnode Dlist::*End() const{
	return sentinel;
}

//Pointer to the last node on the list
Dnode Dlist::*Rbegin() const{
	return sentinel->blink;
}

//Pointer to "one before" the first node on the list
Dnode Dlist::*Rend() const{	
	return sentinel;
}




void Dlist::Insert_Before(const std::string &s, Dnode *n){
	Dnode *prev;
	Dnode *newnode = new Dnode;

	prev = n->blink;
	newnode->s = s;

	newnode->flink = prev->flink;
	newnode->blink = n->blink;
}

void Dlist::Insert_After(const std::string &s, Dnode *n){
	Dnode *next;
	Dnode *newnode = new Dnode;

	next = n->flink;
	newnode->s = s;

	newnode->flink = next->blink;
	newnode->blink = n->flink;
}

void Dlist::Erase(Dnode *n){
	Dnode *prev;
	Dnode *next;

	prev = n->Prev();
	next = n->Next();

	next->blink = prev->flink;
	next->flink = prev->blink;

	delete n;
	size--;
}
