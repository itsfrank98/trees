/*
 * linked_list.h
 *
 *  Created on: 07 gen 2019
 *      Author: Francesco
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "linear_list.h"

template<class T>
class Linked_list;

template< class T >
class List_node{
	friend class Linked_list<T>;
 private:
	T _value;
	List_node<T> * _pPrev;
	List_node<T> * _pNext;
};




template< class T >
class Linked_list : public Linear_list<T, List_node<T>*>{
 public:
	typedef typename Linear_list<T, List_node<T>*>::value_type value_type;
	typedef typename Linear_list<T, List_node<T>*>::posizione posizione;

	Linked_list();
	Linked_list(int);
	// copy constructor
	Linked_list(const Linked_list<T>& );
	~Linked_list();

	void create();
	bool empty() const;
	value_type read(posizione) const;
	void write(const value_type &, posizione);
	posizione begin() const;
	posizione last() const;
	bool end(posizione) const;
	posizione next(posizione) const;
	posizione previous(posizione) const;
	void insert(const value_type &, posizione);
	void erase(posizione);
	int size() const {
		return _length;
	};

	Linked_list<T>& operator=(const Linked_list<T>&);
	bool operator==(const Linked_list<T> &) const;

 private:
	List_node<T> * _pHead;
	int _length;
};

template< class T >
Linked_list< T >::Linked_list() {
	_pHead = new List_node<T>;
	_pHead->_pNext = _pHead;
	_pHead->_pPrev = _pHead;
	_length = 0;
}


template< class T >
Linked_list< T >::Linked_list(const Linked_list<T>& L) {
  _length = L.size();

  _pHead = new List_node<T>;
  _pHead->_pNext = _pHead;
  _pHead->_pPrev = _pHead;

  if (!L.empty()){
	posizione p = L.last();
	for (int i=0; i <= L._length; i++){
		insert(L.read(p), begin());
		p = L.previous(p);
	}
  }
}


template< class T >
Linked_list< T >::~Linked_list(){
	while(!empty())
		erase(begin());
	delete _pHead;
}

template< class T >
void Linked_list< T >::create(){
	if (empty())
		_length = 0;
}

template< class T >
bool Linked_list< T >::empty() const {
	return(_pHead == _pHead->_pNext);
}

template< class T >
typename Linked_list< T >::posizione
Linked_list< T >::begin() const {
	return (_pHead->_pNext);
}

template< class T >
typename Linked_list< T >::posizione
Linked_list< T >::last() const {
	return (_pHead->_pPrev);
}


template< class T >
typename Linked_list< T >::posizione
Linked_list< T >::next(posizione p) const {
	return(p->_pNext);
}

template< class T >
typename Linked_list< T >::posizione Linked_list< T >::previous(posizione p) const {
	if (p != _pHead)
		return(p->_pPrev);
}

template< class T >
bool Linked_list< T >::end(posizione p) const {
	return(p == _pHead);
}

template< class T >
typename Linked_list< T >::value_type
Linked_list< T >::read(posizione p) const {
	if (!end(p))
		return(p->_value);
}

template< class T >
void Linked_list< T >::write(const value_type &a, posizione p) {
	if (!end(p))
    p->_value = a;
}

template< class T >
void Linked_list< T >::insert(const value_type &a, posizione p){
	posizione t = new List_node<T>;
	t->_value = a;

	t->_pNext = p;
	t->_pPrev = p->_pPrev;
	p->_pPrev->_pNext = t;
	p->_pPrev = t;

	_length++;
}

template< class T >
void Linked_list< T >::erase(posizione p){
	if (!empty() && !end(p)){
		p->_pPrev->_pNext = p->_pNext;
		p->_pNext->_pPrev = p->_pPrev;
		delete p;
	}
}


template<class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& L){
	if (this != &L){
		_length = L.size();

		_pHead = new List_node<T>;
		_pHead->_pNext = _pHead;
		_pHead->_pPrev = _pHead;

        cout << L.empty();
        cout << L.size();
		if (!L.empty()){
            posizione p = L.last();
			for (int i=0; i < L.size(); i++){
				cout << i, L.read(p);
				insert(L.read(p), begin());
				p = L.previous(p);
			}
		}
	}
	return *this;
}


template<class T>
bool Linked_list<T>::operator==(const Linked_list<T> &L) const{
	if (L.size() != _length)
		return false;
	posizione p, pL;
	p = begin();
	pL = L.begin();
	while (!end(p)){
		if (p->_value != pL->_value)
			return false;
		p = p->_pNext;
		pL = pL->_pNext;
	}
	return true;
}

#endif /* LINKED_LIST_H_ */
