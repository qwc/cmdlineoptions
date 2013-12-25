#include "cmdlineoptions.h"
#include <string.h>
#include <stdlib.h>

CmdOptions cmdoptions;

void CmdOptions_Init() {
	if (cmdoptions.init == 0) {
		cmdoptions.init = 1;
		// do we have to init something?
		// add the help option
		CmdOptions_Add("help", "--help");
		CmdOptions_Add("help", "-h");
		CmdOptions_Add("help", "-?");
		CmdOptions_AddDescription("help", "Display the help text.");
	}
}

int CmdOptions_Create(char* name) {
	if (CmdOptions_NodeGet(name) == 0) {
		CONode* newnode = 0;
		newnode = malloc(sizeof(CONode));
		if (cmdoptions.options == 0) {
			cmdoptions.options = newnode;
		} else {
			CONode* last = cmdoptions.options;
			while (last->next != 0)
				last = last->next;
			last->next = newnode;
		}
		newnode->next = 0;
		newnode->option = malloc(sizeof(Option));
		newnode->option->name = name;
	}
}

CONode* CmdOptions_NodeGet(char* name) {
	if (cmdoptions.options != 0) {
		CONode* node = cmdoptions.options;
		while (node != 0) {
			if (strcmp(name, node->option->name) == 0) {
				return node;
			}
			node = node->next;
		}
	}
	return 0;
}

int CmdOptions_Parse(int argc, char** argv) {

}

int CmdOptions_Add(char* name, char* option) {

}

int CmdOptions_AddDefaultParameter(char* name, char* defaultparameter) {

}

int CmdOptions_AddPossibleParameter(char* name, char* possibleParameter) {

}

int CmdOptions_AddDescription(char* name, char* description) {

}

int CmdOptions_IsSet(char* name) {

}

char* CmdOptions_Get(char* name) {

}

int CmdOptions_GetInt(char* name) {

}

long CmdOptions_GetLong(char* name) {

}

double CmdOptions_GetDouble(char* name) {

}

int CmdOptions_GetAll(char* name, char** values, unsigned int* count) {

}
