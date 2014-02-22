

all: build static-lib dynamic-lib example compile-tests

build:
	gcc -c -g cmdlineoptions.c
	
static-lib: build
	ar cq libcmdlineoptions.a cmdlineoptions.o
	
	
dynamic-lib:
	gcc -c -fPIC -g -o cmdlineoptions-dynamic.o cmdlineoptions.c
	ld -G cmdlineoptions-dynamic.o -o libcmdlineoptions.so


clean:
	rm -f *.o *.a *.so example
	
	
example:
	gcc -I. -g example.c -o example-shared -L. -lcmdlineoptions
	gcc -g example.c -o example-static libcmdlineoptions.a
	
	
compile-tests:
	gcc -I. -g tests.c -o tests-shared -L. -lcmdlineoptions
	gcc tests.c -o tests-static libcmdlineoptions.a
	
test:
	LD_LIBRARY_PATH="." tests-shared
	tests-static