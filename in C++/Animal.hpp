#pragma once
#include <stdio.h>

class Animal
{
public:
	Animal(void) {}
	virtual ~Animal(void) {}
	virtual void walks(void) const {
		printf("The animal walks.\n");
	}
	virtual void fly(void) const = 0;
};

//the types of the class factories
typedef Animal *create_t();
typedef void destroy_t(Animal *);
