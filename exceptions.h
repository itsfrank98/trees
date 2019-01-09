/*
 * exceptions.h
 *
 *  Created on: 07 gen 2019
 *      Author: Francesco
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>

struct LastReached : public std::domain_error{
	LastReached() : domain_error("The node doesn't have a next brother."){};
};

struct FirstReached : public std::domain_error{
	FirstReached() : domain_error("The node doesn't have a previous brother."){};
};

struct LeafReached : public std::domain_error{
	LeafReached() : domain_error("The node doesn't have sons."){};
};

struct FullSize : public std::invalid_argument {
    FullSize() : invalid_argument("Full size reached.") {};
};

#endif /* EXCEPTIONS_H_ */
