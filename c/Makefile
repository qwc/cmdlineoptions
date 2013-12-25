

all: build lib static

build:
	gcc -c cmdlineoptions.c
	
lib:
	rm -f libcmdlineoptions.a
	ar cq libcmdlineoptions.a cmdlineoptions.o
	
	
static:
	rm -f cmdlineoptions-static.o libcmdlineoptions.so
	gcc -c -fPIC -o cmdlineoptions-static.o cmdlineoptions.c
	ld -G cmdlineoptions-static.o -o libcmdlineoptions.so
