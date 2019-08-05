#include <stdio.h>
#include "Animal.hpp"

class Cat : public Animal
{
public:
	Cat(void) {}
	~Cat(void) {}
	virtual void walks(void) const {
		printf("The cat walks.\n");
	}
	virtual void fly(void) const {
		printf("Cat cannot fly.\n");
	}
};

//class factories
extern "C" Animal *create() {
	return new Cat;
}

extern "C" void destroy(Animal *p) {
	delete p;
}
