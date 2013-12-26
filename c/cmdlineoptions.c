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

CONode* CmdOptions_Create(char* name) {
	CONode* node = CmdOptions_NodeGet(name);
	if (node == 0) {
		node = malloc(sizeof(CONode));
		if (cmdoptions.options == 0) {
			cmdoptions.options = node;
		} else {
			CONode* last = cmdoptions.options;
			while (last->next != 0)
				last = last->next;
			last->next = node;
		}
		node->next = 0;
		node->option = malloc(sizeof(Option));
		node->option->name = name;
		// init the option parts
		node->option->defaultparametercount = 0;
		node->option->defaultparameters = 0;
		node->option->description = 0;
		node->option->options = 0;
		node->option->optionscount = 0;
		node->option->possibleparametercount = 0;
		node->option->possibleparameters = 0;
		node->option->set = 0;
		node->option->values = 0;
		node->option->valuecount = 0;
	}
	return node;
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

void CmdOptions_Add(char* name, char* option) {
	CONode* node = CmdOptions_Create(name);
	CmdOptions_AddElement(node->option->options, &(node->option->optionscount),
			option);
}

void CmdOptions_AddDefaultParameter(char* name, char* defaultparameter) {
	CONode* node = CmdOptions_Create(name);
	CmdOptions_AddElement(node->option->defaultparameters,
			&(node->option->defaultparametercount), defaultparameter);
}

void CmdOptions_AddPossibleParameter(char* name, char* possibleParameter) {
	CONode* node = CmdOptions_Create(name);
	CmdOptions_AddElement(node->option->possibleparameters,
			&(node->option->possibleparametercount), possibleParameter);
}

void CmdOptions_AddDescription(char* name, char* description) {
	CONode* node = CmdOptions_Create(name);
	node->option->description = description;
}

int CmdOptions_IsSet(char* name) {
	CONode* node = CmdOptions_Create(name);
	return node->option->set;
}

char* CmdOptions_Get(char* name) {
	CONode* node = CmdOptions_Create(name);
	if (CmdOptions_IsSet(name) && node->option->valuecount > 0)
		return node->option->values[0];
	return 0;
}

int CmdOptions_GetInt(char* name) {
	return atoi(CmdOptions_Get(name));
}

long CmdOptions_GetLong(char* name) {
	return atol(CmdOptions_Get(name));
}

double CmdOptions_GetDouble(char* name) {
	return atod(CmdOptions_Get(name));
}

int CmdOptions_GetAll(char* name, char** values, unsigned int* count) {
	CONode* node = CmdOptions_Create(name);
	if(node == 0)
		return 1;
	values = node->option->values;
	*count = node->option->valuecount;
	return 0;
}

void CmdOptions_AddElement(char** target, int* counter, char* element) {
	int cnt = *counter;
	char** old = 0;
	if (target != 0)
		old = target;
	target = malloc((cnt + 1) * sizeof(char*));
	if (old != 0)
		memcpy(target, old, (cnt) * sizeof(char*));
	target[cnt] = element;
	if (old != 0)
		free(old);
	*counter = cnt + 1;
}
