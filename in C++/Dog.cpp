#include <stdio.h>
#include "Animal.hpp"

class Dog : public Animal
{
public:
	Dog(void) {}
	~Dog(void) {}
	virtual void walks(void) const {
		printf("The dog walks.\n");
	}
	virtual void fly(void) const {
		printf("Dog cannot fly.\n");
	}
};

//class factories
extern "C" Animal *create() {
	return new Dog;
}

extern "C" void destroy(Animal *p) {
	delete p;
}
