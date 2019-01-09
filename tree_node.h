/*
 * tree_node.h
 *
 *  Created on: 06 gen 2019
 *      Author: Francesco Benedetti
 */

#ifndef TREE_NODE_H_
#define TREE_NODE_H_
#include "linked_list.h"
#include "exceptions.h"

template<class N>
class tree;

template <class N>
class node{
public:
	friend class tree<N>;
	typedef Linked_list<node<N>*> node_list;
	typedef typename Linked_list<node<N>*>::posizione position;

	node(){
		parent=nullptr;
	}

	node(N v){
		parent=nullptr;
		set_node(v);
	}

	N read_node();
	void set_node(const N);
	bool leaf() const;
	node<N>* get_parent() const;
	node_list& get_sons();
	node<N>* first_son() const;
	node<N>* last_son() const;
	node<N>* next_bro() const;
	node<N>* prev_bro() const;
	bool is_first() const;
	bool is_last() const;

	int get_depth();

	void print_sons() const;

private:
	N val;
	Linked_list<node<N>*> sons;
	node<N> *parent;
};


template<class N>
N node<N>::read_node(){
	return val;
}

template<class N>
void node<N>::set_node(const N v){
	val=v;
}

template<class N>
bool node<N>::leaf() const{
	return(sons.empty());
}

template <class N>
node<N>* node<N>::get_parent() const{
	return parent;
}

template<class N>
typename node<N>::node_list& node<N>::get_sons(){
	return sons;
}

template<class N>
node<N>* node<N>::first_son() const{
	if(!leaf())
		return sons.read(sons.begin());
	else
		throw LeafReached();
}

template<class N>
node<N>* node<N>::last_son() const{
	if(!leaf())
		return sons.read(sons.last());
	else
		throw LeafReached();
}

template<class N>
node<N>* node<N>::next_bro() const{
	if(!is_last()){
		node *p=get_parent();
		position pos;
		node_list sons=p->get_sons();
		pos=sons.begin();
		while(sons.read(pos)!=this){
			pos=sons.next(pos);
		}
		return sons.read(sons.next(pos));
	}
	else throw LastReached();
}

template<class N>
node<N>* node<N>::prev_bro() const{
	if(!is_first()){
		node *p=get_parent();
		position pos;
		node_list sons=p->get_sons();
		pos=sons.begin();
		while(sons.read(pos)!=this){
			pos=sons.next(pos);
		}
		return sons.read(sons.previous(pos));
	}
	else throw FirstReached();

}

template<class N>
bool node<N>::is_first() const{
	node *p=get_parent();
	return(this==p->first_son());
}

template<class N>
bool node<N>::is_last() const{
	node *p=get_parent();
	return(this==p->last_son());
}

template<class N>
void node<N>::print_sons() const{
	position pos;
	pos=sons.begin();
	while(!sons.end(pos)){
		cout << sons.read(pos)->read_node() << " ";
		pos=sons.next(pos);
	}
}

template<class N>
int node<N>::get_depth(){
	int p=0;
	if(get_parent()==nullptr)
		return p;
	else{
		p=1+get_parent()->get_depth();
		return p;
	}
}
#endif /* TREE_NODE_H_ */
