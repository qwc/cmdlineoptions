#include "cmdlineoptions.h"


CmdOptions cmdoptions;

void CmdOptions_Init(){
	if (cmdoptions.init == 0) {
		cmdoptions.init = 1;
		// do we have to init something?
		// add the help option
		CmdOptions_Add("help","--help");
		CmdOptions_Add("help","-h");
		CmdOptions_Add("help","-?");
		CmdOptions_AddDescription("help","Display the help text.");
	}
}

int CmdOptions_Parse(int argc, char** argv){

}

int CmdOptions_Add(char* name, char* option){

}

int CmdOptions_AddDefaultParameter(char* name, char* defaultparameter){

}

int CmdOptions_AddPossibleParameter(char* name, char* possibleParameter){

}

int CmdOptions_AddDescription(char* name, char* description) {

}

bool    CmdOptions_IsSet(char* name) {

}

char*   CmdOptions_Get(char* name) {

}

int     CmdOptions_GetInt(char* name) {

}

long    CmdOptions_GetLong(char* name){

}

double  CmdOptions_GetDouble(char* name) {

}

int     CmdOptions_GetAll(char* name, char** values, unsigned int* count) {

}
