/* Name: Sarah Huang
 * Date: 12/2/2021
 * Program: avltree_lab.cpp
 * Purpose: Simulate an AVL tree
 */

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS202::AVLTree;
using CS202::AVLNode;

//Assignment overload
AVLTree& AVLTree::operator= (const AVLTree &t){
	(void) t;
	Clear();
	recursive_postorder_copy(t.sentinel->right);
	return *this;
}


//Check whether there is an imbalance around a single node (using heights of left & right children)
bool imbalance(const AVLNode *n){
	int left = n->left->height;
	int right = n->right->height;
	int diff = left - right;

	if(diff < -1 || diff > 1)
		return true;
	else
		return false;
}


void rotate_left(AVLNode *x){
	//AVLNode *x				grandparent (n1)
	AVLNode *y = x->right;		//parent (n2)
	AVLNode *T2 = y->left;		//parent's other child
	AVLNode *gg = x->parent;	//great grandparent? - could be sentinel

	//Perform rotation
	y->left = x;
	x->parent = y;
	x->right = T2;
	T2->parent = x;
	x->height--;

	y->parent = gg;
	if(gg->right->key == x->key || gg->height == 0)
		gg->right = y;
	else
		gg->left = y;
}


void rotate_right(AVLNode *y){
	//AVLNode *y				grandparent (n1)
	AVLNode *x = y->left;	    //parent (n2)
	AVLNode *T2 = x->right;		//parent's other child
	AVLNode *gg = y->parent;	//great grandparent? - could be sentinel

	//Perform rotation
	x->right = y;
	y->parent = x;
	y->left = T2;
	T2->parent = y;
	y->height--;

	x->parent = gg;
	if(gg->right->key == y->key || gg->height == 0)
		gg->right = x;
	else
		gg->left = x;
}


//Readjust the node heights from parent of the new node to the root
void fix_height(AVLNode *n){
	n = n->parent;
	while(n->key != "---SENTINEL---"){
		if(n->left != NULL || n->right != NULL){
			int diff = n->left->height - n->right->height;
			while(diff < -1 || diff > 1){
				if(diff < -1)
					n->left->height++;
				else
					n->right->height++;
				diff = n->left->height - n->right->height;
			}
		
		
			while(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
				if(n->height > n->left->height || n->height > n->right->height)
					break;
			}
		}
		n = n->parent;
	}
}


//Decide which rotation to do: zig zig left/right and zig zag left/right
void fix_imbalance(AVLNode *n, AVLNode *new_node){
	int diff = n->left->height - n->right->height;

	if(diff > 1){
		//zig zig right
		if(new_node->key < n->left->key){
			rotate_right(n);
		}
		//zig zag left right
		else{
			rotate_left(n->left);
			rotate_right(n);
		}
	}
	else if(diff < -1){
		//zig zig left
		if(new_node->key > n->right->key){
			rotate_left(n);
		}
		//zig zag right left
		else{
			rotate_right(n->right);
			rotate_left(n);
		}
	} 
}



bool AVLTree::Insert(const string &key, void *val){
	AVLNode *parent;
	AVLNode *n;
	parent = sentinel;
	n = sentinel->right;
	while (n != sentinel) {
		if (n->key == key) return false;
		parent = n;
		n = (key < n->key) ? n->left : n->right;
	}
	n = new AVLNode;
	n->key = key;
	n->val = val;
	n->parent = parent;
	n->height = 1;
	n->left = sentinel;
	n->right = sentinel;
	if (parent == sentinel) {
		sentinel->right = n;
	} 
	else if (key < parent->key) {
		parent->left = n;
	} 
	else {
		parent->right = n;
	}
	size++;


	//Start with the parent since we don't need to check the newly inserted node
	AVLNode *orig = n;
	AVLNode *prev = n;
	n = n->parent;

	//Go up the tree and check heights and imbalances
	while(n != sentinel){
		if(imbalance(n)){
			fix_imbalance(n, orig);
			fix_height(prev);
			break;
		}
		else{
			if(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
			}
		}
		prev = n;
		n = n->parent;
	}
	return true;
}



bool AVLTree::Delete(const string &key){
	AVLNode *n, *parent, *mlc;
	string tmpkey;
	void *tmpval;

	//Try to find key, return false if it's not there
	n = sentinel->right;
	while (n != sentinel && key != n->key) {
		n = (key < n->key) ? n->left : n->right;
	}
	if (n == sentinel) return false;

	
	parent = n->parent;

	//1. I have no left child.  Replace me with my right child.
	if (n->left == sentinel) {
		if (n == parent->left) {
			parent->left = n->right;
		} 
		else {
			parent->right = n->right;
		}
		if (n->right != sentinel) n->right->parent = parent;
		delete n;
		size--;

	} 
	//2. I have no right child.  Replace me with my left child.
	else if (n->right == sentinel) {
		if (n == parent->left) {
			parent->left = n->left;
		} 
		else {
			parent->right = n->left;
		}
		n->left->parent = parent;
		delete n;
		size--;
	} 
	/*3. If I have two children, then find the node "before" me in the tree.
			That node will have no right child, so I can recursively delete it.
			When I'm done, I'll replace the key and val of n with the key and
			val of the deleted node.*/
	else {
		for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
		tmpkey = mlc->key;
		tmpval = mlc->val;
		Delete(tmpkey);
		n->key = tmpkey;
		n->val = tmpval;
		return true;
	}



	

	cout << "n = " << n->key << endl;
	int diff;
	int diff_L;
	int diff_R;
	
	//trying to figure out where nodes are and to use n or parent?
	//cout << sentinel->right->key << endl;
	//cout << sentinel->right->left->key << endl;

	/*
	while(n != sentinel){
		if(n->left == NULL)
			diff = n->right->height * -1;
		else if(n->right == NULL)
			diff = n->left->height;
		else
			diff = n->left->height - n->right->height;

		cout << "diff = " << diff << endl;
		

		if(diff < -1 || diff > 1){
			if(n->left == NULL){
				cout << "no left child" << endl;
				diff_L = 0;
			}
			else
				diff_L = n->left->left->height - n->left->right->height;
			
			if(n->right == NULL){
				cout << "no right child" << endl;
				diff_R = 0;
			}
			else
				diff_R = n->right->left->height - n->right->right->height;



			if(diff == 2){
				if(diff_L >= 0){
					cout << "zig zig left" << endl;
					rotate_right(n);
				}
				else{
					cout << "zig zag left right" << endl;
					rotate_left(n->left);
					rotate_right(n);
				}
			}
			else if(diff == -2){
				if(diff_R <= 0){
					cout << "zig zig right" << endl;
					rotate_left(n);
				}
				else{
					cout << "zig zag right left" << endl;
					rotate_right(n->right);
					rotate_left(n);
				}
			}
		}
		else{
			if(n->height >= n->left->height || n->height >= n->right->height){
				n->height--;
				cout << n->key << "	height is now " << n->height << endl;
			}
		}
		n = n->parent;
	}
	*/



	return true;
}


//Return a vector of sorted keys
vector <string> AVLTree::Ordered_Keys() const{
	vector <string> rv;
	make_key_vector(sentinel->right, rv);
	return rv;
}


//Helper for Ordered_Keys()
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const{
	(void) n;
	(void) v;
	if(n == sentinel) return;

	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

//Returns the height of the tree
size_t AVLTree::Height() const{
	AVLNode *n;
	n = sentinel->right;
	return n->height;
}


//Helper for the assignment overload
AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const{
	(void) n;
	AVLNode *temp;

	if(n->height == 0) return NULL;

	temp = new AVLNode;
	temp->key = n->key;
	temp->val = n->val;
	temp->parent = n->parent;
	temp->height = n->height;
	temp->left = n->left;
	temp->right = n->right;

	recursive_postorder_copy(n->left);
	recursive_postorder_copy(n->right);

	return temp;
}
