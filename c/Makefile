

all: build static dynamic

build:
	gcc -c cmdlineoptions.c
	
static: build
	ar cq libcmdlineoptions.a cmdlineoptions.o
	
	
dynamic:
	gcc -c -fPIC -o cmdlineoptions-static.o cmdlineoptions.c
	ld -G cmdlineoptions-static.o -o libcmdlineoptions.so


clean:
	rm -f *.o *.a *.so