

all: build static-lib dynamic-lib example

build:
	gcc -c cmdlineoptions.c
	
static-lib: build
	ar cq libcmdlineoptions.a cmdlineoptions.o
	
	
dynamic-lib:
	gcc -c -fPIC -o cmdlineoptions-static.o cmdlineoptions.c
	ld -G cmdlineoptions-static.o -o libcmdlineoptions.so


clean:
	rm -f *.o *.a *.so example
	
	
example:
	gcc -ggdb example.c -o example libcmdlineoptions.a