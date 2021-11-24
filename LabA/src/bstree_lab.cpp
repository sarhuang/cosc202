/* Name: Sarah Huang
 * Date: 11/23/21
 * Program: bstree_lab.cpp
 * Purpose: Simulate a binary search tree. 
 *			Y'know it's okay to take some Ls. It's hard to stay motivated near the end.
*/


#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;


//Distance from a node to the root
int BSTree::Depth(const string &key) const{
	(void) key;
	int distance = 0;

	BSTNode *n;
	n = sentinel->right;

	while(1){
		if(n == sentinel) return -1;		//Key not found in tree
		if(key == n->key) return distance;
		n = (key < n->key) ? n->left : n->right;
		distance++;
	}
}

//Returns the depth of the node with maximum depth, plus one.
int BSTree::Height() const{ 
	int height = recursive_find_height(sentinel->right) + 1;
	return height;
}

//Return a vector of sorted keys
vector <string> BSTree::Ordered_Keys() const{
	vector <string> rv;
	make_key_vector(sentinel->right, rv);
	return rv;
}




//Copy constructor
BSTree::BSTree(const BSTree &t) {
	(void) t;
	sentinel = new BSTNode;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	sentinel->parent = NULL;
	sentinel->key = "---SENTINEL---";
	sentinel->val = NULL;
	size = 0;

	*this = t;
}

//Assignment overload
BSTree& BSTree::operator= (const BSTree &t) {
	(void) t;
	vector <string> ok = t.Ordered_Keys();
	vector <void *> ov = t.Ordered_Vals();

	Clear();
	make_balanced_tree(ok, ov, 0, t.Size()-1);

	return *this;
}



//Helper for Height()
int BSTree::recursive_find_height(const BSTNode *n) const{  
	(void) n;
	static int maxDepth = 0;	//The maximum depth found (static so it doesn't make copies during recursion)

	
	if(sentinel == n) return -1;

	recursive_find_height(n->left);
	recursive_find_height(n->right);

	//If the calculated depth is greater than current max depth
	if(Depth(n->key) > maxDepth)
		maxDepth = Depth(n->key);	

	//Once we return to base case
	if(n->parent == sentinel){
		int temp = maxDepth;
		maxDepth = 0;	//Must reset static variable for future calls
		return temp;
	}
	return 0;
}

//Helper for Ordered_Keys()
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const{
	(void) n;
	(void) v;

	if(n == sentinel) return;

	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

//Helper for copy constructor and assignment overload
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
		const vector<void *> &vals,
		size_t first_index,
		size_t num_indices) const
{
	(void) sorted_keys;
	(void) vals;
	(void) first_index;
	(void) num_indices;

	BSTNode *parent;
	BSTNode *n;
	string key;				
	void * val;			
	static size_t c = 0;	//Counter to check current size of tree
	int mid;
	
	

	if((first_index < num_indices && num_indices > sorted_keys.size()) || first_index > num_indices){
		return NULL;
	}

	mid = (first_index + num_indices)/2;
	key = sorted_keys.at(mid);
	val = vals.at(mid);
	

	//Find where key should go.
	parent = sentinel;
	n = sentinel->right;
	while(n != sentinel){
		parent = n;
		n = (key < n->key) ? n->left : n->right;
	}

	//Create new node and hook it in
	n = new BSTNode;
	n->key = key;		
	n->val = val;			
	n->parent = parent;
	n->left = sentinel;
	n->right = sentinel;
	
	//Use correct pointer in parent to point to new node
	if (parent == sentinel) 
		sentinel->right = n;
	else if (key < parent->key)	
		parent->left = n;
	else 
		parent->right = n;

	

	c++;	
	if(c < sorted_keys.size()){	
		make_balanced_tree(sorted_keys, vals, first_index, mid-1);
		make_balanced_tree(sorted_keys, vals, mid+1, num_indices);	
	}

	if(c == sorted_keys.size())
		c = 0;

	return n;
}
