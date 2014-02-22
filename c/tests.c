/*
 * tests.c
 *
 *  Created on: 22.02.2014
 *      Author: qwc
 */

#include "cmdlineoptions.h"

void configureDefaultSet(){
	CmdLO_Init(1);
	CmdLO_Add("test", "--test");
	CmdLO_Add("test", "-t");
	CmdLO_Add("example", "--example");
	CmdLO_Add("example", "-e");
	CmdLO_Add("something", "-s");
	CmdLO_AddDefaultParameter("something", "sometest");
	CmdLO_AddDescription("test","Well, this is a test command line option.");
	CmdLO_AddDescription("example", "An example commandline option");
	CmdLO_AddPossibleParameter("example","test");
	CmdLO_AddPossibleParameter("example","test2");
}


int main(int argc, char** argv) {
	// configure the options
	configureDefaultSet();

	// emulate parameters
	int myargc = 0;
	char** myargv = 0;

	// test 1 parse nothing.
	CmdLO_Parse(myargc,myargv);

	// check contents...


	// test 2 parse everything


	// test 3 parse something


	// test 4 producing some errors...


	return 0;
}


