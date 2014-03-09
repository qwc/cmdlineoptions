/*
 * tests.c
 *
 *  Created on: 22.02.2014
 *      Author: qwc
 */

#include "cmdlineoptions.h"
#include <stdio.h>
#include <stdlib.h>

void configureDefaultSet() {
	CmdLO_Init(1);
	CmdLO_Add("test", "--test");
	CmdLO_Add("test", "-t");
	CmdLO_Add("example", "--example");
	CmdLO_Add("example", "-e");
	CmdLO_Add("something", "-s");
	CmdLO_AddDefaultParameter("something", "sometest");
	CmdLO_AddDescription("test", "Well, this is a test command line option.");
	CmdLO_AddDescription("example", "An example commandline option");
	CmdLO_AddPossibleParameter("example", "test");
	CmdLO_AddPossibleParameter("example", "test2");
}

#define ASSERT(x,y) if(!(x)) printf("ASSERT FAILED! '%s'.\n",y); else printf("ASSERT '%s' succeded.\n",y)

int main(int argc, char** argv) {
	// configure the options
	configureDefaultSet();

	// emulate parameters
	int myargc = 0;
	char** myargv = 0;

	// test 1 parse nothing.
	printf("Test 1: no parameters.\n");
	CmdLO_Parse(myargc, myargv);

	// check contents...
	// nothing should be set so...
	ASSERT(CmdLO_NodeGet("test")->option->set == 0, "test not set.");
	ASSERT(CmdLO_NodeGet("example")->option->set == 0, "example not set.");
	ASSERT(CmdLO_NodeGet("something")->option->set == 0, "something not set");
	ASSERT(CmdLO_NodeGet("test")->option->optionscount == 2,
			"test option count");
	ASSERT(CmdLO_NodeGet("example")->option->optionscount == 2,
			"example option count");
	ASSERT(CmdLO_NodeGet("something")->option->optionscount == 1,
			"something option count");
	ASSERT(CmdLO_NodeGet("test")->option->defaultparametercount == 0,
			"test defaultparameter");
	ASSERT(CmdLO_NodeGet("example")->option->defaultparametercount == 0,
			"example defaultparameter");
	ASSERT(CmdLO_NodeGet("something")->option->defaultparametercount == 1,
			"something defaultparameter");
	ASSERT(CmdLO_NodeGet("test")->option->possibleparametercount == 0,
			"test possibleparameters");
	ASSERT(CmdLO_NodeGet("example")->option->possibleparametercount == 2,
			"example possibleparameters");
	ASSERT(CmdLO_NodeGet("something")->option->possibleparametercount == 0,
			"something possibleparameters");
	ASSERT(CmdLO_NodeGet("test")->option->valuecount == 0, "test value count");
	ASSERT(CmdLO_NodeGet("example")->option->valuecount == 0,
			"example value count");
	ASSERT(CmdLO_NodeGet("something")->option->valuecount == 0,
			"something value count");

	printf("Test 2: all parameters set with allowed parameters.\n");
	// test 2 parse everything
	//configureDefaultSet();
	myargc = 6;
	myargv = calloc(myargc, sizeof(char*));
	myargv[1] = "--test";
	myargv[2] = "tested";
	myargv[3] = "-e";
	myargv[4] = "test";
	myargv[5] = "-s";

	CmdLO_Parse(myargc, myargv);

	ASSERT(CmdLO_NodeGet("test")->option->set != 0, "test set.");
	ASSERT(CmdLO_NodeGet("example")->option->set != 0, "example set.");
	ASSERT(CmdLO_NodeGet("something")->option->set != 0, "something set");
	ASSERT(CmdLO_NodeGet("test")->option->optionscount == 2,
			"test option count");
	ASSERT(CmdLO_NodeGet("example")->option->optionscount == 2,
			"example option count");
	ASSERT(CmdLO_NodeGet("something")->option->optionscount == 1,
			"something option count");
	ASSERT(CmdLO_NodeGet("test")->option->defaultparametercount == 0,
			"test defaultparameter");
	ASSERT(CmdLO_NodeGet("example")->option->defaultparametercount == 0,
			"example defaultparameter");
	ASSERT(CmdLO_NodeGet("something")->option->defaultparametercount == 1,
			"something defaultparameter");
	ASSERT(CmdLO_NodeGet("test")->option->possibleparametercount == 0,
			"test possibleparameters");
	ASSERT(CmdLO_NodeGet("example")->option->possibleparametercount == 2,
			"example possibleparameters");
	ASSERT(CmdLO_NodeGet("something")->option->possibleparametercount == 0,
			"something possibleparameters");
	ASSERT(CmdLO_NodeGet("test")->option->valuecount == 1, "test value count");
	ASSERT(CmdLO_NodeGet("example")->option->valuecount == 1,
			"example value count");
	ASSERT(CmdLO_NodeGet("something")->option->valuecount == 0,
			"something value count");

	// test 3 parse something
	CmdLO_Destroy();
	configureDefaultSet();
	printf("Test 3: Just some options.\n");
	myargc = 4;
	myargv[1] = "--test";
	myargv[2] = "blah";
	myargv[3] = "testtttt";
	//myargv[4] = "-h";
	CmdLO_Parse(myargc, myargv);

	ASSERT(CmdLO_NodeGet("test")->option->set != 0, "test set.");
	ASSERT(CmdLO_NodeGet("example")->option->set == 0, "example set.");
	ASSERT(CmdLO_NodeGet("something")->option->set == 0, "something set");
	ASSERT(CmdLO_NodeGet("test")->option->optionscount == 2,
			"test option count");
	ASSERT(CmdLO_NodeGet("example")->option->optionscount == 2,
			"example option count");
	ASSERT(CmdLO_NodeGet("something")->option->optionscount == 1,
			"something option count");
	ASSERT(CmdLO_NodeGet("test")->option->defaultparametercount == 0,
			"test defaultparameter");
	ASSERT(CmdLO_NodeGet("example")->option->defaultparametercount == 0,
			"example defaultparameter");
	ASSERT(CmdLO_NodeGet("something")->option->defaultparametercount == 1,
			"something defaultparameter");
	ASSERT(CmdLO_NodeGet("test")->option->possibleparametercount == 0,
			"test possibleparameters");
	ASSERT(CmdLO_NodeGet("example")->option->possibleparametercount == 2,
			"example possibleparameters");
	ASSERT(CmdLO_NodeGet("something")->option->possibleparametercount == 0,
			"something possibleparameters");
	ASSERT(CmdLO_NodeGet("test")->option->valuecount == 2, "test value count");
	ASSERT(CmdLO_NodeGet("example")->option->valuecount == 0,
			"example value count");
	ASSERT(CmdLO_NodeGet("something")->option->valuecount == 0,
			"something value count");
	// test 4 producing some errors...
	CmdLO_Destroy();
	configureDefaultSet();
	printf("Test 4: now lets produce some errors...\n");
	myargc = 5;
	myargv[1] = "-tehe";
	myargv[2] = "wtf";
	myargv[3] = "-e";
	myargv[4] = "12345";
	CmdLO_Parse(myargc, myargv);

	ASSERT(CmdLO_NodeGet("test")->option->set == 0, "test set.");
	ASSERT(CmdLO_NodeGet("example")->option->set == 0, "example set.");
	ASSERT(CmdLO_NodeGet("something")->option->set == 0, "something set");
	ASSERT(CmdLO_NodeGet("test")->option->optionscount == 2,
			"test option count");
	ASSERT(CmdLO_NodeGet("example")->option->optionscount == 2,
			"example option count");
	ASSERT(CmdLO_NodeGet("something")->option->optionscount == 1,
			"something option count");
	ASSERT(CmdLO_NodeGet("test")->option->defaultparametercount == 0,
			"test defaultparameter");
	ASSERT(CmdLO_NodeGet("example")->option->defaultparametercount == 0,
			"example defaultparameter");
	ASSERT(CmdLO_NodeGet("something")->option->defaultparametercount == 1,
			"something defaultparameter");
	ASSERT(CmdLO_NodeGet("test")->option->possibleparametercount == 0,
			"test possibleparameters");
	ASSERT(CmdLO_NodeGet("example")->option->possibleparametercount == 2,
			"example possibleparameters");
	ASSERT(CmdLO_NodeGet("something")->option->possibleparametercount == 0,
			"something possibleparameters");
	ASSERT(CmdLO_NodeGet("test")->option->valuecount == 0, "test value count");
	ASSERT(CmdLO_NodeGet("example")->option->valuecount == 0,
			"example value count");
	ASSERT(CmdLO_NodeGet("something")->option->valuecount == 0,
			"something value count");
	return 0;
}

