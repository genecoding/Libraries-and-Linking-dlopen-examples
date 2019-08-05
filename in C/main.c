#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef void (*lib_func)(void);

int main(int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "Usage: %s animal_type\n", argv[0]);
		return EXIT_FAILURE;
	}

	char path[20];
	strcpy(path, "./lib");
	if(strcmp(argv[1], "dog") == 0)
		strcat(path, "dog.so");
	else if(strcmp(argv[1], "cat") == 0)
		strcat(path, "cat.so");
	else if(strcmp(argv[1], "bird") == 0)
		strcat(path, "bird.so");
	else {
		fprintf(stderr, "Error: unknown animal type: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	void *lib;
	lib = dlopen(path, RTLD_LAZY);
	
	if(!lib) { /*fail to load the library*/
		fprintf(stderr, "Error: %s\n", dlerror());
		return EXIT_FAILURE;
	}

	lib_func func_walks = dlsym(lib, "walks");
	if(!func_walks) { /*no such function*/
		fprintf(stderr, "Error: %s\n", dlerror());
		return EXIT_FAILURE;
	}

	func_walks();
	dlclose(lib);

	return EXIT_SUCCESS;
}
