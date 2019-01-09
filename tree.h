/*
 * tree.h
 *
 *  Created on: 07 gen 2019
 *      Author: Francesco Benedetti
 */

#ifndef TREE_H_
#define TREE_H_
#include "tree_node.h"
#include "linked_list.h"
#include "exceptions.h"
//#include "code.h"
#define MAX_NODES 100

template<class N>
class tree{
public:
	typedef typename node<N>::node_list node_list;
	typedef typename Linked_list<node<N>*>::posizione position;
	tree(){
		root=nullptr;
		num_nodes=0;
	}

	tree(int n){
		num_nodes=n;
		root=nullptr;
	}

	~tree(){
		remove_sub_tree(root);
	}
	int get_num_nodes() const;
	bool empty_tree() const;
	void ins_root(N);
	node<N>* get_root() const;
	void ins_first_son(node<N>*, N);
	void ins_son(node<N>*, N);
	void ins_first_son_node(node<N>*, node<N>*);	//This function allows to insert directly a node, without having to create a new one internally
	void ins_son_node(node<N>*, node<N>*);			//This function allows to insert directly a node, without having to create a new one internally
	void ins_subtree(node<N>*, tree<N>&);
	void ins_first_subtree(node<N>*, tree<N>&);

	void remove_disc(node<N>*);			//Removes the offspring of the subtree radicated in n, without removing n
	void remove_sub_tree(node<N>*);		//After calling remove_disc, removes n

	void print_depth(node<N>*) const;		//Prints the nodes and their depth
	void print_sub(node<N>*) const;
	void print() const;

	void previsit(node<N>*) const;
	void postvisit(node<N>*) const;

private:
	int num_nodes;
	node<N> *root;
};

template<class N>
int tree<N>::get_num_nodes() const{
	return num_nodes;
}

template<class N>
bool tree<N>::empty_tree() const{
	return (num_nodes==0);
}

template<class N>
void tree<N>::ins_root(N v){
	root = new node<N>;
	root->parent=nullptr;
	root->val=v;
	num_nodes++;
}

template <class N>
node<N>* tree<N>::get_root() const{
	return root;
}

template<class N>
void tree<N>::ins_first_son(node<N>* n, N v){
	if(num_nodes < MAX_NODES){
		node<N> *son = new node<N>;
		son->val=v;
		son->parent=n;
		num_nodes++;
		n->sons.insert(son, n->sons.begin());
	}
	else
		throw FullSize();
}


template<class N>
void tree<N>::ins_son(node<N>* n, N v){
	if(num_nodes < MAX_NODES){
		position l;
		node<N> *son = new node<N>;
		son->parent=n;
		son->val=v;
		l=n->sons.begin();
		while(!n->sons.end(l)){
			l=n->sons.next(l);
		}
		num_nodes++;
		n->sons.insert(son, l);
	}
	else
		throw FullSize();
}

/*The following function inserts the node 'son' into the tree as first son of the node 'n' , without creating a node internally. This function will be used by
 * the function 'ins_first_subtree'
 */

template<class N>
void tree<N>::ins_first_son_node(node<N>* n, node<N>* son){
	if(num_nodes < MAX_NODES){
		son->parent=n;
		num_nodes++;
		n->sons.insert(son, n->sons.begin());
	}
	else
		throw FullSize();
}

/*The following function inserts the node 'son' into the tree as son of the node 'n' , without creating a node internally. This function will be used by
 * the function 'ins_subtree'
 */
template<class N>
void tree<N>::ins_son_node(node<N>* n, node<N>* son){
	if(num_nodes < MAX_NODES){
		position l;
		l=n->sons.begin();
		son->parent=n;
		while(!n->sons.end(l)){
			l=n->sons.next(l);
		}
		num_nodes++;
		n->sons.insert(son, l);
	}
	else
		throw FullSize();
}

template<class N>
void tree<N>::ins_subtree(node<N>* n, tree<N>& subtree){
	if(num_nodes+subtree.get_num_nodes()<=MAX_NODES){
		ins_son_node(n, subtree.get_root());
		num_nodes+=subtree.get_num_nodes()-1;
	}
	else
		throw FullSize();
}

template<class N>
void tree<N>::ins_first_subtree(node<N>* n, tree<N>& subtree){
	if(num_nodes+subtree.get_num_nodes() <= MAX_NODES){
		ins_first_son_node(n, subtree.get_root());
		num_nodes+=subtree.get_num_nodes()-1;
	}
	else
		throw FullSize();
}

template<class N>
void tree<N>::remove_disc(node<N>* n){
	if(n!=nullptr){
		if(!n->leaf()){
			while(!n->get_sons().empty())
				remove_disc(n->get_sons().read(n->get_sons().begin()));
		}
		else{
			position l=n->parent->sons.begin();
			while(n->parent->sons.read(l)!=n){
				l=n->parent->sons.next(l);
			}
			n->parent->sons.erase(l);
		}
	}
}

template<class N>
void tree<N>::remove_sub_tree(node<N>* n){
	remove_disc(n);
	if(n!= root){
		position l=n->parent->sons.begin();
		while((n->parent->sons.read(l)!=n) && (!n->parent->sons.end(l))){
			l=n->parent->sons.next(l);
		}
		n->parent->sons.erase(l);
	}
	else
		root=nullptr;
}

template<class N>
void tree<N>::print_sub(node<N>* n) const{
	cout << endl<< n->read_node() << ":    ";
	n->print_sons();
	position l;
	node_list &sons=n->get_sons();
	l=sons.begin();
	while(!sons.end(l)){
		print_sub(sons.read(l));
		l=sons.next(l);
	}
}

template<class N>
void tree<N>::print_depth(node<N>* n) const{
	if(n!=nullptr){
		cout << endl<< n->read_node() << ":    ";
		cout << n->get_depth();
		position l;
		node_list &sons=n->get_sons();
		l=sons.begin();
		while(!sons.end(l)){
			print_depth(sons.read(l));
			l=sons.next(l);
		}
	}
	else
		cout<< "Null root!";
}

template<class N>
void tree<N>::print() const{
	if(root != nullptr)
		print_sub(root);
	else
		cout<< "Null root!";
}

template <class N>
void tree<N>::previsit(node<N> *n) const{
	if(n!=nullptr){
		cout << n->read_node();
		node<N> *n1 = new node<N>;
		if(!n->leaf()){
			n1=n->first_son();
			while(!n1->is_last()){
				previsit(n1);
				n1=n1->next_bro();
			}
			previsit(n1);
		}
	}
	else
		cout<< "Null root!";
}

template <class N>
void tree<N>::postvisit(node<N> *n) const{
	if(n!=nullptr){
		node<N> *n1 = new node<N>;
		if(!n->leaf()){
			n1=n->first_son();
			while(!n1->is_last()){
				postvisit(n1);
				n1=n1->next_bro();
			}
			postvisit(n1);
		}
		cout << n->read_node();
	}
	else
		cout<< "Null root!";
}

#endif /* TREE_H_ */
