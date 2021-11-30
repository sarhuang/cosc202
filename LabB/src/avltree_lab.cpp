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
	//cout << n->left->height << " - " << n->right->height << " = " << diff << endl;

	if(diff < -1 || diff > 1){
		cout << "wow that's an imbalance" << endl;
		return true;
	}
	else
		return false;
}


void fix_height(AVLNode *n){
	cout << "time to fix height" << endl;
	
	while(n->key != "---SENTINEL---"){
		if(n->left != NULL || n->right != NULL){
	
			
			
			int diff = n->left->height - n->right->height;
			cout << "	" << n->left->height << " - " << n->right->height << " = " << diff << endl;

			while(diff < -1 || diff > 1){
				if(diff < -1){
					cout << "diff < -1" << endl;
					n->left->height++;
				}
				else if(diff > 1){
					cout << "diff > 1" << endl;
					n->right->height++;
				}
				diff = n->left->height - n->right->height;
			}

			
			while(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
				cout << "now " << n->key << " height = " << n->height << endl;

			    if(n->height > n->left->height || n->height > n->right->height)		
					break;
			}
		}


		cout << "	KEY " <<  n->key << ":	" << n->height << endl;
		n = n->parent;
	}
	cout << "i'm done with height" << endl;
}


void fix_imbalance(AVLNode *n){
	cout << "FiX ImBaLaNcE" << endl;
	//AVLNode *n = node itself
	AVLNode *p = n->parent;
	AVLNode *g = n->parent->parent;
	AVLNode *gg = n->parent->parent->parent;


	cout << "n = " << n->key << endl;
	cout << "p = " << p->key << endl;
	cout << "g = " << g->key << endl;
	cout << "gg = " << gg->key << endl;

	//zig zig one direction
	if(p->right == n && g->right == p){
		cout << "zig zig LEFT" << endl;
		g->parent = p;
		g->right = p->left;
		g->height--;

		if(gg->right == g)
			gg->right = p;
		else
			gg->left = p;
		p->parent = gg;
		p->left = g;
	}	
	//zig zig other direction
	else if(p->left == n && g->left == p){
		cout << "zig zig RIGHT" << endl;
		g->parent = p;
		g->left = p->right;
		g->height--;

		if(gg->right == g){
			cout << "----GO	RIGHT!-------" << endl;
			gg->right = p;
		}
		else{
			cout << "WE ARE GOING LEFT I REPEAT GOING LEFT" << endl;
			gg->left = p;
		}
		p->parent = gg;
		p->right = g;
	}


	//zig zag one direction
	else if(p->left == n && g->right == p){
		cout << "zig ZAG right left" << endl;
	
		//first rotation
		p->parent = n;
		p->left = n->right;
		p->height--;
		
		g->right = n;
		n->parent = g;
		n->right = p;

		//second rotation
		g->parent = n;
		g->right = n->left;
		g->height--;

		if(gg->right == g)
			gg->right = n;
		else
			gg->left = n;
		n->parent = gg;
		n->left = g;
	}

	//zig zag other direction
	else if(p->right == n && g->left == p){
		cout << "zig ZAG left right" << endl;
		
		//first rotation
		p->parent = n;
		p->right = n->left;
		p->height--;

		g->left = n;
		n->parent = g;
		n->left = p;

		//second rotation
		g->parent = n;
		g->left = n->right;
		g->height--;

		if(gg->right == g)
			gg->right = n;
		else
			gg->left = n;
		n->parent = gg;
		n->right = g;
	}

	cout << n->key << " (n)  height = " << n->height << endl;
	cout << p->key << " (p)  height = " << p->height << endl;
	cout << g->key << " (g)  height = " << g->height << endl;
	cout << gg->key << " (gg) height = " << gg->height << endl;
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



	AVLNode *temp = n;

	//Imbalance
	n = n->parent;
	while(n != sentinel){	
		if(imbalance(n)){
			fix_imbalance(temp);
			fix_height(n);
			break;
		}
		else{
			while(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
				cout << "now " << n->key << " height = " << n->height << endl;

				if(n->height > n->left->height || n->height > n->right->height)
					break;
			}

			n = n->parent;
		}

	}

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
