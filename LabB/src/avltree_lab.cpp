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


AVLTree& AVLTree::operator= (const AVLTree &t){
	(void) t;
	Clear();
	recursive_postorder_copy(t.sentinel->right);
	return *this;
}




//Chefck whether there is an imbalance around a single node (using heights of left & right children)
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
	//AVLNode *x			grandparent (n1)
	AVLNode *y = x->right;	//parent (n2)
	AVLNode *T2 = y->left;	//parent's other child
	AVLNode *gg = x->parent;//great grandparent? - could be sentinel

	cout << "x = " << x->key << endl;
	cout << "y = " << y->key << endl;
	cout << "T2 = " << T2->key << endl;
	cout << "gg = " << gg->key << endl;


	//Perform rotation
	y->left = x;
	x->parent = y;
	x->right = T2;
	T2->parent = x;
	x->height--;

	y->parent = gg;
	if(gg->height != 0){
		cout << "gg->right->key = " << gg->right->key << endl;
		cout << "gg->left->key = " << gg->left->key << endl;
		cout << "x-key	" << x->key << endl;
	}
	if(gg->right->key == x->key || gg->height == 0){
		cout << "gg go right	Y" << endl;
		gg->right = y;
	}
	else{
		gg->left = y;
	}



	cout << "\nThese are the most update n, p, g" << endl;
	cout << y->key << " = n" << endl;
	if(y->parent->height != 0){
		cout << y->parent->key << " = p" << endl; 
		if(y->parent->parent->height != 0)
			cout << y->parent->parent->key << " = g" << endl;
	}
	//return y;
}

void rotate_right(AVLNode *y){
	//AVLNode *y				grandparent (n1)
	AVLNode *x = y->left;	    //parent (n2)
	AVLNode *T2 = x->right;		//parent's other child
	AVLNode *gg = y->parent;	//great grandparent? - could be sentinel

	cout << "y = " << y->key << endl;
	cout << "x = " << x->key << endl;
	cout << "T2 = " << T2->key << endl;
	cout << "gg = " << gg->key << endl;

	//Perform rotation
	x->right = y;
	y->parent = x;
	y->left = T2;
	T2->parent = y;
	y->height--;

	x->parent = gg;
	if(gg->height != 0){
		cout << "gg->right->key = " << gg->right->key << endl;
		cout << "gg->left->key = " << gg->left->key << endl;
		cout << "y-key	" << y->key << endl;
	}
	
	if(gg->right->key == y->key || gg->height == 0){
		cout << "gg go right	X" << endl;
		gg->right = x;
	}
	else{
		gg->left = x;
	}

	cout << "\nThese are the most update n, p, g" << endl;
	cout << x->key << " = n" << endl;
	if(x->parent->height != 0){
		cout << x->parent->key << " = p" << endl;
		if(x->parent->parent->height != 0)
			cout << x->parent->parent->key << " = g" << endl;
	}
	//return x;
}



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
				cout << "after imbalance NOW, " << n->key << " height = " << n->height << endl;
				if(n->height > n->left->height || n->height > n->right->height)
					break;
			}
		}
		n = n->parent;
	}
	cout << "no more fixing height" << endl;
}




void fix_imbalance(AVLNode *n, AVLNode *new_node){
	//left left		right rotation
	//right right	left rotation
	//left right	left rotation, right rotation
	//right left	right rotation, left rotation

	int diff = n->left->height - n->right->height;

	if(diff > 1){
		//left left
		if(new_node->key < n->left->key){
			cout << "zig zig right" << endl;
			rotate_right(n);
		}
		//left right
		else{
			cout << "zig zag left right" << endl;
			rotate_left(n->left);
			rotate_right(n);
		}
	}
	else if(diff < -1){
		//right right
		if(new_node->key > n->right->key){
			cout << "zig zig left" << endl;
			rotate_left(n);
			//right left
		}
		else{
			cout << "zig zag right left" << endl;
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
			cout << "	NODE " << n->key << " = " << n->height << endl;
			cout << "	RIGHT " << n->right->key << " = " << n->right->height << endl;
			cout << "	LEFT " << n->left->key << " = " << n->left->height << endl;
			cout << "	PARENT " << n->parent->key << " = " << n->parent->height << endl;


			fix_imbalance(n, orig);
			
			/*cout << sentinel->right->key << endl;
			cout << sentinel->right->right->key << endl;
			cout << sentinel->right->right->left->key << endl;
			cout << sentinel->right->right->right->key << endl;
			*/
		
			fix_height(prev);
			break;
		}
		else{
			if(n->height <= n->left->height || n->height <= n->right->height){
				n->height++;
				cout << "NO IMBALANCE - now " << n->key << " height = " << n->height << endl;
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

	n = sentinel->right;
	while (n != sentinel && key != n->key) {
		n = (key < n->key) ? n->left : n->right;
	}
	if (n == sentinel) return false;
	parent = n->parent;

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
	else {
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
