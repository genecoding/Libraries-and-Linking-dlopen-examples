#include "Animal.hpp"
#include <string>
#include <dlfcn.h>
#include <iostream>
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " animal_type behavior\n";
		return 1;
	}
	
	string animal = argv[1];
	string behavior = argv[2];
	
	string path = "./lib";
	if(animal.compare("dog") == 0)
		path += "dog.so";
	else if(animal.compare("cat") == 0)
		path += "cat.so";
	else if(animal.compare("bird") == 0)
		path += "bird.so";
	else {
		cerr << "Error: unknown animal type: " << animal << endl;
		return 1;
	}
		
	void *lib;	
	lib = dlopen(path.c_str(), RTLD_LAZY);
	if(!lib) { //fail to load the library
		cerr << "Error: " << dlerror() << endl;
		return 1;
	}

	// load the symbols
    create_t* create_anim = (create_t*) dlsym(lib, "create");
    const char* dlsym_error = dlerror();
    if(dlsym_error) {
        cerr << "Cannot load symbol create: " << dlsym_error << endl;
        return 1;
    }
    
    destroy_t* destroy_anim = (destroy_t*) dlsym(lib, "destroy");
    dlsym_error = dlerror();
    if(dlsym_error) {
        cerr << "Cannot load symbol destroy: " << dlsym_error << endl;
        return 1;
    }

    // create an instance of the class
    Animal* animPtr = create_anim();

	if(behavior.compare("walks") == 0)
	   animPtr->walks();
	else if(behavior.compare("fly") == 0)
	   animPtr->fly();
	else { //no such function
		cerr << "Error: unknown behavior: " << behavior << endl;
		return 1;
	}

    // destroy the class
    destroy_anim(animPtr);
	
	dlclose(lib);

	return 0;
}

