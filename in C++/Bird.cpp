#include <stdio.h>
#include "Animal.hpp"

class Bird : public Animal
{
public:
	Bird(void) {}
	~Bird(void) {}
	virtual void walks(void) const {
		printf("The bird walks.\n");
	}
	virtual void fly(void) const {
		printf("Bird can fly.\n");
	}
};

//class factories
extern "C" Animal *create() {
	return new Bird;
}

extern "C" void destroy(Animal *p) {
	delete p;
}
