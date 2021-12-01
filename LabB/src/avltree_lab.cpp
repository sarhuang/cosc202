/* Name: Sarah Huang
 * Date: 
 * Program:
 * Purpose:
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



//Check whether there is an imbalance around a single node (by checking heights of children)
bool imbalance(const AVLNode *n){
	(void) n;
	
	int diff = n->left->height - n->right->height;
	cout << "IMBALANCE CHECK: " << n->left->height << " - " << n->right->height << " = " << diff << endl;
	if(diff < -1 || diff > 1){
		cout << "YES imbalance" << endl;
		return true;
	}
	else{
		return false;
	}
}


void fix_height(AVLNode *n){
	cout << "\nfix_height START" << endl;
	
	while(n->key != "---SENTINEL---"){
		if(n->left != NULL || n->right != NULL){	//Has at least a child
			int diff = n->left->height - n->right->height;
			cout << "	" << n->left->height << " - " << n->right->height << " = " << diff << endl;

			//Increases the heights of the children until the difference is 0 or 1
			while(diff < -1 || diff > 1){
				if(diff < -1){
					cout << "diff < -1" << endl;
					n->left->height++;
					cout << n->left->key << " = " << n->left->height << endl;
				}
				else if(diff > 1){
					cout << "diff > 1" << endl;
					n->right->height++;
					cout << n->right->key << " = " << n->right->height << endl;
				}
				diff = n->left->height - n->right->height;
			}

			//Increases the node's height until it is greater than the children by 1
			while(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
				cout << "now " << n->key << " height = " << n->height << endl;

			    if(n->height > n->left->height || n->height > n->right->height)		
					break;
			}
		}
		cout << "NEW HEIGHT	KEY " <<  n->key << ":	" << n->height << endl;
		n = n->parent;
	}
	cout << "fix_height END" << endl;
}


void fix_imbalance(AVLNode *n, string choice){
	cout << "\nFiX ImBaLaNcE" << endl;
	//AVLNode *n = node itself
	AVLNode *p = n->parent;
	AVLNode *g = p->parent;

	cout << "n = " << n->key << endl;
	cout << "p = " << p->key << endl;
	cout << "g = " << g->key << endl;
	

	//zig zig left
	if(choice == "zigzig_l"){
		cout << g->left->key << endl;
		cout << g->left->right->key << endl;
		cout << g->left->right->right->key << endl;
		cout << g->left->right->right->right->key << endl;

		cout << "\nzig zig LEFT" << endl;
		p->parent = n;
		p->right = n->left;
		p->height--;

		if(g->right == p)
			g->right = n;
		else
			g->left = n;
		n->parent = g;
		n->left = p;
	}	
	//zig zig right
	if(choice == "zigzig_r"){
		cout << "\nzig zig RIGHT" << endl;
		p->parent = n;
		p->left = n->right;
		p->height--;

		if(g->right == p){
			cout << "----GO	RIGHT!-------" << endl;
			g->right = n;
		}
		else{
			cout << "WE ARE GOING LEFT I REPEAT GOING LEFT" << endl;
			g->left = n;
		}
		n->parent = g;
		n->right = p;
	}


	//zig zag right left
	else if(choice == "zigzag_rl"){
		cout << "\nzig ZAG right left" << endl;
	
		//first rotation
		p->parent = n;
		p->left = n->right;
		
		g->right = n;
		n->parent = g;
		n->right = p;

		p->height--;

		//second rotation
		p = n->parent;
		g = p->parent;
		cout << n->key << " (n)  NEW " << endl;
		cout << p->key << " (p)  NEW " << endl; 
		cout << g->key << " (g)  NEW" << endl;  

		p->parent = n;
		p->right = n->left;
		
		if(g->height != 0){
			cout << "g->right->key = " << g->right->key << endl;
			cout << "g->left->key = " << g->left->key << endl;
		
			if(g->right->key == p->key){
				cout << "	g->right == n" << endl;
				g->right = n;
			}
			else
				g->left = n;
		}
		else	//SENTINEL
			g->right = n;

	
		n->parent = g;
		n->left = p;
		p->height--;

	}

	//zig zag left right
	if(choice == "zigzag_lr"){
		cout << "\nzig ZAG left right" << endl;
		
		//first rotation
		p->parent = n;
		p->right = n->left;
		
		g->left = n;
		n->parent = g;
		n->left = p;

		p->height--;


		//second rotation
		p = n->parent;
		g = p->parent;
		cout << n->key << " (n)  NEW " << endl;
		cout << p->key << " (p)  NEW " << endl;	//11
		cout << g->key << " (g)  NEW" << endl;	//5
		

		p->parent = n;
		p->left = n->right;

		if(g->height != 0){
			cout << "g->right->key = " << g->right->key << endl;
			cout << "g->left->key = " << g->left->key << endl;

			if(g->right->key == p->key){
				cout << "	g->right == n" << endl;
				g->right = n;
			}
			else{
				cout << "	g->left == n" << endl;
				g->left = n;
			}
		}
		else
			g->right = n;

		n->parent = g;
		n->right = p;

		p->height--;
	}
}





//Assignment Operator
AVLTree& AVLTree::operator= (const AVLTree &t){
	(void) t;

	Clear();
	recursive_postorder_copy(t.sentinel->right);
	return *this;
}





bool AVLTree::Insert(const string &key, void *val){
	AVLNode *parent;
	AVLNode *n;

	parent = sentinel;
	n = sentinel->right;

	//Find where the key should go.  If you find the key, return false.
	while (n != sentinel) {
		if (n->key == key) return false;
		parent = n;
		n = (key < n->key) ? n->left : n->right;
	}

	/*At this point, parent is the node that will be the parent of the new node.
	  Create the new node, and hook it in. */
	n = new AVLNode;
	n->key = key;
	n->val = val;
	n->parent = parent;
	n->height = 1;
	n->left = sentinel;
	n->right = sentinel;

	// Use the correct pointer in the parent to point to the new node. 
	if (parent == sentinel) 
		sentinel->right = n;
	else if (key < parent->key) 
		parent->left = n;
	else
		parent->right = n;
	
	size++;



	
	//My code
	AVLNode *prevprev = n;
	int counter = 1;
	n = n->parent;	//REMEMBER WE START AT THE PARENT OF THE NEW NODE
	
	while(n != sentinel){	//Goes all the way to the top
		if(imbalance(n)){
			cout << "	NODE " << n->key << " = " << n->height << endl;
			cout << "	RIGHT " << n->right->key << " = " << n->right->height << endl;
			cout << "	LEFT " << n->left->key << " = " << n->left->height << endl;
			cout << "	PARENT " << n->parent->key << " = " << n->parent->height << endl;
			cout << "	prevprev " << prevprev->key << " = " << prevprev->height << endl;

			//prevprev->key doesn't always work
			if(n->height == n->left->height && (n->height - n->left->right->height == 1)){
				cout << "zigzag_lr" << endl;
				fix_imbalance(n->left->right, "zigzag_lr");
			}
			
			else if(n->height == n->right->height && (n->height - n->right->left->height == 1)){
				cout << "zigzag_rl" << endl;
				fix_imbalance(n->right->left, "zigzag_rl");
			}
			
			
			//HOW CAN I DIFFERENTIATE ZIG ZIG LEFT AND RIGHT?
			else if((n->left->height == 0 && n->right->left->height == 0)){
				cout << "zigzig_l" << endl;
				if(n->left->height == 0){
					cout << "i can only do n->right" << endl;
					fix_imbalance(n->right, "zigzig_l");
				}
				else
					fix_imbalance(n->left, "zigzig_l");
			}
			else if(n->key < sentinel->right->key){
				cout << "also zigzig_l" << endl;
				if(n->left->height == 0)
					fix_imbalance(n->right, "zigzig_l");
				else
					fix_imbalance(n->left, "zigzig_l");
			}

			//Just let else be right so less brainpower
			else{
				cout << "zigzig_r" << endl;
				if(n->right->height == 0){
					cout << "no choice but to do n->left" << endl;
					fix_imbalance(n->left, "zigzig_r");
				}
				else
					fix_imbalance(n->right, "zigzig_r");
			}
			
			fix_height(prevprev);
			break;
		}
		else{
			//Increases the height until it is greater than children by 1
			//This code is in fix_height but this is for not imbalanced nodes
			while(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
				cout << "NO IMBALANCE - now " << n->key << " height = " << n->height << endl;

				//If it's the right height and there is only one child node (the other is always 0)
				if(n->height > n->left->height || n->height > n->right->height)
					break;
			}
			if(counter % 2 == 0)
				prevprev = n;
			n = n->parent;
		}
	}
	cout << endl << endl;
	return true;
}






bool AVLTree::Delete(const string &key)
{
	AVLNode *n, *parent, *mlc;
	string tmpkey;
	void *tmpval;


	//Try to find the key -- if you can't return false.
	n = sentinel->right;
	while (n != sentinel && key != n->key) {
		n = (key < n->key) ? n->left : n->right;
	}
	if (n == sentinel) return false;


	/* We go through the three cases for deletion, although it's a little
	   different from the canonical explanation. */
	parent = n->parent;



	/* Case 1 - I have no left child.  Replace me with my right child.
	   Note that this handles the case of having no children, too. */
	if (n->left == sentinel) {
		if (n == parent->left) {
			parent->left = n->right;
		} else {
			parent->right = n->right;
		}
		if (n->right != sentinel) n->right->parent = parent;
		delete n;
		size--;


		/* Case 2 - I have no right child.  Replace me with my left child. */
	} else if (n->right == sentinel) {
		if (n == parent->left) {
			parent->left = n->left;
		} else {
			parent->right = n->left;
		}
		n->left->parent = parent;
		delete n;
		size--;


		/* If I have two children, then find the node "before" me in the tree.
		   That node will have no right child, so I can recursively delete it.
		   When I'm done, I'll replace the key and val of n with the key and
		   val of the deleted node.  You'll note that the recursive call 
		   updates the size, so you don't have to do it here. */
	} else {
		for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
		tmpkey = mlc->key;
		tmpval = mlc->val;
		Delete(tmpkey);
		n->key = tmpkey;
		n->val = tmpval;
		return true;
	}

	return true;
}








vector <string> AVLTree::Ordered_Keys() const{
	vector <string> rv;
	make_key_vector(sentinel->right, rv);
	return rv;
}

void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const{
	(void) n;
	(void) v;

	if(n == sentinel) return;

	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}





size_t AVLTree::Height() const{
	AVLNode *n;
	n = sentinel->right;
	return n->height;
}








/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

AVLNode* AVLTree::recursive_postorder_copy(const AVLNode *n) const{
	(void) n;
	AVLNode *temp;


	//If it's the tree's sentinel node, height should be 0
	if(n->height == 0){
		//cout << "ah a sentinel node" << endl;
		return NULL;
	}


	temp = new AVLNode;
	temp->key = n->key;
	temp->val = n->val;
	temp->parent = n->parent;
	temp->height = n->height;
	temp->left = n->left;
	temp->right = n->right;

	//cout << "Just created a node!" << endl;
	//cout << "KEY: " << temp->key << endl;


	recursive_postorder_copy(n->left);
	recursive_postorder_copy(n->right);

	return temp;
}
