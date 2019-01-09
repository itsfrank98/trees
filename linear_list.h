/*
 * linear_list.h
 *
 *  Created on: 06 gen 2019
 *      Author: Francesco
 */

#ifndef LINEAR_LIST_H_
#define LINEAR_LIST_H_
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template< class T, class P >
class Linear_list{
 public:
	typedef T value_type;   // the type of object, T, stored in the list
	typedef P posizione;

	// operators
	virtual ~Linear_list(){};
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual value_type read(posizione) const = 0;
	virtual void write(const value_type & x, posizione p) = 0;
	virtual posizione begin() const = 0;
	virtual posizione last() const = 0;
	virtual bool end(posizione) const = 0;
	virtual posizione next(posizione) const = 0;
	virtual posizione previous(posizione) const = 0;
	virtual void insert(const value_type &, posizione) = 0;
	virtual void erase(posizione pos) = 0;
};

/* overloads the operator <<. Warning: if the type returned by 'read' isn't primitive, we will have to
 * overload the operator << for this type too
 */
template< class T, class P >
ostream& operator<<(ostream& os, const Linear_list<T,P> &l){
	typename Linear_list<T,P>::posizione p;
	p = l.begin();
	os << "[";
	while (!l.end(p)){
		if (p != l.begin())
			os << ", " << l.read(p);
		else
			os << l.read(p);
		p = l.next(p);
	}
	os << "]" << endl;
	return os;
}

#endif /* LINEAR_LIST_H_ */

