/* Name: Sarah Huang
 * Date: 11/1/2021
 * Program: dlist.cpp
 * Purpose: Simulate a doubly-linked list.
 *				- May be traversed in the forward and reverse direction
 *				- Arbitrary insertion of nodes anywhere in the list
 *				- Arbitrary deletion of any nodes
 */

#include <iostream>
#include "dlist.hpp"
using namespace std;

/*	class Dnode {
 *		friend class Dlist;
 *		public:
 *			string s;		
 *			Dnode *Next();	- Returns d->flink
 *			Dnode *Prev();	- Returns d->blink
 *	           
 *	        protected:
 *	        Dnode *flink;	- Points to the next node in the list		
 *	        Dnode *blink;	- Points to the previous node in the list
 *	};
 *	            
 *	             
 *	    protected:
 *	        Dnode *sentinel;	- Extra node which begins (and ends) each list
 *			size_t size;		- If a list contains size elements, it will contain size+1 nodes
 */


Dnode* Dnode::Next(){
	return flink;
}

Dnode* Dnode::Prev(){
	return blink;
}



//Constructor
Dlist::Dlist(){
	sentinel = new Dnode;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
}
//Copy constructor
Dlist::Dlist(const Dlist &d){
	sentinel = new Dnode;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
	*this = d;
}
//Assignment overload
Dlist& Dlist::operator= (const Dlist &d){
	Dnode* n;

	Clear();
	for(n = d.Begin(); n != d.End(); n = n->flink){
		Push_Back(n->s);
	}
	return *this;
}
//Destructor
Dlist::~Dlist(){
	Clear();
	delete sentinel;
	size--;
}



//Clear the list - delete every node EXCEPT the sentinel
void Dlist::Clear(){
	while(!Empty()){
		Erase(Begin());
	}
}

//Returns whether the list is empty.
bool Dlist::Empty() const{
	if(sentinel->flink == sentinel && sentinel->blink == sentinel)
		return true;
	return false;
}

//Returns the list's size.
size_t Dlist::Size() const{
	return size;
}



//Inserts a new node before the first element
void Dlist::Push_Front(const std::string &s){
	Insert_Before(s, Begin());
}

//Inserts a new node after the last element
void Dlist::Push_Back(const std::string &s){
	Insert_After(s, Rbegin());
}



//Remove and return the first element of the list
string Dlist::Pop_Front(){
	string temp = Begin()->s;
	Erase(Begin());	
	return temp;
}

//Remove and return the last element of the list
string Dlist::Pop_Back(){
	string temp = Rbegin()->s;
	Erase(Rbegin());
	return temp;
}


// Pointer to the first node on the list
Dnode* Dlist::Begin() const{	
	return sentinel->flink;	
}
// Pointer to "one past" the last node on the list.
Dnode* Dlist::End() const{
	return sentinel;
}
// Pointer to the last node on the list
Dnode* Dlist::Rbegin() const{
	return sentinel->blink;
}
// Pointer to "one before" the first node on the list.
Dnode* Dlist::Rend() const{	
	return sentinel;
}


//Insert a new node before a given node
void Dlist::Insert_Before(const std::string &s, Dnode *n){
	Dnode* prev = n->blink;
	Dnode* newnode = new Dnode;
	newnode->s = s;

	newnode->blink = prev;
	newnode->flink = n;
	prev->flink = newnode;
	n->blink = newnode;

	size++;
}

//Insert a new node after a given node
void Dlist::Insert_After(const std::string &s, Dnode *n){
	Dnode* newnode = new Dnode;
	Dnode* next = n->flink;
	newnode->s = s;

	newnode->blink = n;
	newnode->flink = next;
	next->blink = newnode;
	n->flink = newnode;

	size++;
}

//Delete a node from the list except the sentinel
void Dlist::Erase(Dnode *n){
	if(n != sentinel){
		Dnode* prev = n->blink;
		Dnode* next = n->flink;

		next->blink = prev;
		prev->flink = next;

		delete n;
		size--;
	}
}
