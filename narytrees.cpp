//============================================================================
// Name        : narytrees.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "tree_node.h"
#include "tree.h"

int main() {
	tree<char> t;
	t.ins_root('a');
	t.ins_first_son(t.get_root(), 'b');
	t.ins_first_son(t.get_root(), 'c');
	t.ins_son(t.get_root()->first_son(), 'p');

	tree<char> b;
	b.ins_root('o');
	b.ins_first_son(b.get_root(), 'i');
	b.ins_son(b.get_root(), 'r');

	t.ins_subtree(t.get_root()->first_son(), b);

	cout << "\n\n\nNodes Sons";
	t.print();
	cout << endl <<"\nNode depth:";
	t.print_depth(t.get_root());

	cout << "\nPrevisit: " << endl;
	t.previsit(t.get_root());

	cout << "\nPostvisit: " << endl;
	t.postvisit(t.get_root());
	//Removes a subtree and then prints the new tree
	t.remove_sub_tree(t.get_root()->first_son());

	cout << endl << "\n\n\nAFTER REMOVING THE SUBTREE RADICATED IN 'c'" << endl;
	cout << "\n\n\nNodes Sons";
	t.print();

	cout << "\nPrevisit: " << endl;
	t.previsit(t.get_root());

	cout << "\nPostvisit: " << endl;
	t.postvisit(t.get_root());


	cout << endl <<"\nNode depth:";
	t.print_depth(t.get_root());



	int i;
	cin>>i;
	return 0;
}
