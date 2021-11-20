/* Name: Sarah Huang
 * Date: 11/2
 * Program: bstree_lab.cpp
 * Purpose:
 */

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using namespace CS202::BSTree;
using namespace CS202::BSTNode;




//Copy constructor
BSTree::BSTree(const BSTree &t){
	/* Dlist
	 *	sentinel = new Dnode;
	 *	sentinel->flink = sentinel;
	 *	sentinel->blink = sentinel;*/


	(void) t;

	//Call assignment overload


}
//Assignment overload
BSTree::BSTree& operator= (const BSTree &t){
	/* Dlist
	 *	Dnode* n;
	 *	Clear();
	 *	for(n = d.Begin(); n != d.End(); n = n->flink){
	 *		Push_Back(n->s);
	 *	}
	 *	return *this;*/



	//Not only do they make a copy of the tree, but the copy will be balanced
	//In other words, the middle key will be the root of the tree. 
	//		The middle key of the left subtree will be the key of the left child of the root
	//		The middle key of the right subtree will be the key of the right child of the root. 

	//If a tree has an even number of elements, the "middle" element is (number-of-elements)/2
	//So, if a tree has four keys, the "middle" one is key #2 in Ordered_Keys()

	(void) t;


	//Call Ordered_Keys() to get a vector of keys in sorted order & Ordered_Vals() to get vals
	//Call make_balanced_tree() to create subtree


	return *this;
}





//Distance from a node to the root.  Returns -1 if the key is not in the tree.
int BSTree::Depth(const string &key) const{
	(void) key;
	int distance = 0;

	BSTNode *n;

	n = sentinel->right;
	while (1) {
		if (n == sentinel) return -1;
		if (key == n->key) return distance;
		n = (key < n->key) ? n->left : n->right;
		distance++;
	}
}
//Returns the depth of the node with maximum depth, plus one.	
int BSTree::Height() const{
	//An empty tree has a height of zero. A tree with one node has a height of one.
	//USE recursive_find_height()
	
	//int recursive_find_height(const BSTNode *n) const;
	
	return recursive_find_height(sentinel->right) + 1;
}

//Return a vector of sorted keys
vector <string> BSTree::Ordered_Keys() const{
	vector <string> rv;
	
	//USE make_key_vector()
	
	//make_val_vector(sentinel->right, rv);
	
	make_key_vector(sentinel->right, rv);
	return rv;
}



//Helper for Height()
int BSTree::recursive_find_height(const BSTNode *n) const{
	(void) n;
	int h = 0;
	
	if(n == sentinel) return h;
	recursive_find_height(n->left);
	h += Depth(n);
	recursive_find_height(n->right);

}
//Helper for Ordered_Keys()
void BSTree::make_key_vector(const BSTNode *n, vector <void *> &v) const{
	(void) n;
	(void) v;

	//if(n == sentinel) return;
	//make_val_vector(n->left, v);
	//v.push_back(n->val);
	//make_val_vector(n->right, v);

	if(n == sentinel) return;
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}
//Helper for copy constructor and assignment overload
BSTNode BSTree::*make_balanced_tree(const vector <string> &sorted_keys, const vector<void *> &vals, size_t first_index, size_t num_indices) const{
	(void) sorted_keys;
	(void) vals;
	(void) first_index;
	(void) num_indices;

	//be recursive AND create tree in postorder manner

	//return a root of the tree

	return NULL;
}

