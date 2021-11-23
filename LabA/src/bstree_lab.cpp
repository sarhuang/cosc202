#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <set>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

int BSTree::Depth(const string &key) const{
	(void) key;
	int distance = 0;

	BSTNode *n;
	n = sentinel->right;

	while(1){
		if(n == sentinel) return -1;
		if(key == n->key) return distance;
		n = (key < n->key) ? n->left : n->right;
		distance++;
	}
}

int BSTree::Height() const{ 
	int height = recursive_find_height(sentinel->right) + 1;
	return height;
}

vector <string> BSTree::Ordered_Keys() const{
	vector <string> rv;
	make_key_vector(sentinel->right, rv);
	return rv;
}




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

BSTree& BSTree::operator= (const BSTree &t) {
	//call Ordered_Keys()
	//call Ordered_Vals()
	//call make_balanced_tree()

	(void) t;

	Clear();

	vector <string> ok = t.Ordered_Keys();
	vector <void *> ov = t.Ordered_Vals();
	make_balanced_tree(ok, ov, 0, t.Size());
	return *this;
}




int BSTree::recursive_find_height(const BSTNode *n) const{  
	(void) n;
	static int maxDepth = 0;

	if(sentinel == n) return -1;

	recursive_find_height(n->left);
	recursive_find_height(n->right);

	if(Depth(n->key) > maxDepth){
		maxDepth = Depth(n->key);
	}	

	//cout << "MAX DEPTH = " << maxDepth << endl;


	if(n->parent == sentinel){
		int temp = maxDepth;
		maxDepth = 0;
		return temp;
	}
	return 0;
}

void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const{
	(void) n;
	(void) v;

	if(n == sentinel) return;

	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
		const vector<void *> &vals,
		size_t first_index,
		size_t num_indices) const
{
	(void) sorted_keys;
	(void) vals;
	(void) first_index;
	(void) num_indices;
	static size_t c = 0;
	static int i = 0;
	static set <string> used;
	set <string>::iterator it;
	
	//individually create nodes & connect manually
	BSTNode *parent;
	BSTNode *n;
	string key;
	void * val;

	//parent = sentinel;
	//n = sentinel->right;
	

	if(sorted_keys.size() % 2 != 0 && num_indices <= sorted_keys.size() && (first_index+num_indices/2) < sorted_keys.size()){
		key = sorted_keys.at(first_index + num_indices/2);	//FIX HERE
		//val = vals.at(first_index + num_indices/2);			//FIX HERE
	
		it = used.find(key);
		if(it == used.end()){
			val = vals.at(first_index + num_indices/2);
			used.insert(key);
		}
		else
			key = "";
	}
	else{
		if(num_indices % 2 != 0 && (first_index+num_indices/2) < sorted_keys.size()){
			key = sorted_keys.at(first_index + num_indices/2);
			//val = vals.at(first_index + num_indices/2);
			
			it = used.find(key);
			if(it == used.end()){
				val = vals.at(first_index + num_indices/2);
				used.insert(key);
			}
			else
				key = "";
		}
		else if((num_indices/2 - 1) < sorted_keys.size() && (num_indices/2) < sorted_keys.size()){
			if(sorted_keys.at(num_indices/2 - 1) > sorted_keys.at(num_indices/2)){
				key = sorted_keys.at(num_indices/2 - 1);
				//val = vals.at(num_indices/2 - 1);
				
				it = used.find(key);
				if(it == used.end()){
					val = vals.at(num_indices/2 - 1);
					used.insert(key);
				}
				else
					key = "";
			}
			else{
				key = sorted_keys.at(num_indices/2);
				//val = vals.at(num_indices/2);
				
				it = used.find(key);
				if(it == used.end()){
					val = vals.at(num_indices/2);
					used.insert(key);
				}
				else
					key = "";
			}
		}
	}
	
	cout << "KEY=" << key << endl;




	if(key != ""){
		parent = sentinel;
		n = sentinel->right;
	

	//Find where key should go.
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
	i = 0;
	}
	else 
		i++;
	



	//if(c != sorted_keys.size() && num_indices/2 != 0){
	if(c != sorted_keys.size()){
	//	cout << "first_index=" << first_index << "		num_indices=" << num_indices << endl;

		//if(num_indices/2 != 0){
		if(sorted_keys.size() % 2 != 0 && num_indices/2 != 0){
			make_balanced_tree(sorted_keys, vals, first_index, num_indices/2);
			make_balanced_tree(sorted_keys, vals, first_index + num_indices/2 + 1, num_indices/2);
		}
		else if(sorted_keys.size() % 2 == 0 && num_indices/2 != 0){
			make_balanced_tree(sorted_keys, vals, first_index, num_indices/2);


	//		cout << "\nAFTER	first_index=" << first_index << "      num_indices=" << num_indices << endl;
			
			
			make_balanced_tree(sorted_keys, vals, first_index, num_indices + c + i);
		}
	}


	//cout << "first_index=" << first_index << "		num_indices=" << num_indices << endl;
	return n;
}
