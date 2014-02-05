#include "cmdlineoptions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CmdOptions cmdoptions;

void CmdOptions_Init(char addhelp) {
	CmdOptions_InitCmd(addhelp, 0);
}

void CmdOptions_InitCmd(char addhelp, char cmdchar) {
	if (cmdoptions.init == 0) {
		cmdoptions.init = 1;
		if (cmdchar != 0)
			cmdoptions.cmdchar = cmdchar;
		else
			cmdoptions.cmdchar = '-';
		// do we have to init something?
		// add the help option
		if (addhelp != 0) {
			CmdOptions_Add("help", "--help");
			CmdOptions_Add("help", "-h");
			CmdOptions_Add("help", "-?");
			CmdOptions_AddDescription("help", "Display the help text.");
		}
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

CONode* CmdOptions_SearchNode(char* cmdlineargument) {
	printf("searching\n");
	if (cmdoptions.options != 0) {
		printf("searching further\n");
		CONode* node = cmdoptions.options;
		while (node != 0) {
			if (node->option->optionscount > 0) {
				printf("searching more! %d \n",node->option->optionscount);
				int i = 0;
				for (; i < node->option->optionscount; ++i) {
					printf("addresses 0x%x 0x%x\n",node->option->options, node->option->options[i]);
					if (strcmp(node->option->options[i], cmdlineargument)
							== 0) {
						return node;
					}
				}
			}
			node = node->next;
		}
	}
	return 0;
}

int CmdOptions_Parse(int argc, char** argv) {
	if (argc > 1) {
		int i = 1;
		CONode* cnode = 0;
		char* carg = 0;
		;
		for (; i < argc; ++i) {
			if (argv[i][0] == cmdoptions.cmdchar) {
				if ((cnode = CmdOptions_SearchNode(argv[i])) != 0) {
					cnode->option->set = 1;
				} else {
					carg = argv[i];
					fprintf(stderr, "CmdLineOptions: Unrecognized option '%s'.",
							carg);
				}
			}
			if (cnode != 0) {
				if (cnode->option->possibleparametercount == 0) {
					CmdOptions_AddElement(&cnode->option->values,
							&(cnode->option->valuecount), argv[i]);
				} else {
					int j = 0;
					for (; j < cnode->option->possibleparametercount; ++j) {
						if (strcmp(argv[i],
								cnode->option->possibleparameters[j]) == 0) {
							CmdOptions_AddElement(&cnode->option->values,
									&(cnode->option->valuecount), argv[i]);
							break;
						}
					}
					if (cnode->option->possibleparametercount == j) {
						fprintf(stderr,
								"CmdLineOptions: Parameter '%s' is not allowed, parameter not added.",
								argv[i]);
					}
				}
			} else {
				fprintf(stderr,
						"CmdLineOptions: Unrecognized option parameter '%s' for unrecognized option '%s'.",
						argv[i], carg);
			}
		}
	}
	// no arguments!
	return 1;
}

void CmdOptions_Add(char* name, char* option) {
	CONode* node = CmdOptions_Create(name);
	CmdOptions_AddElement(&node->option->options, &(node->option->optionscount),
			option);
}

void CmdOptions_AddDefaultParameter(char* name, char* defaultparameter) {
	CONode* node = CmdOptions_Create(name);
	CmdOptions_AddElement(&node->option->defaultparameters,
			&(node->option->defaultparametercount), defaultparameter);
}

void CmdOptions_AddPossibleParameter(char* name, char* possibleParameter) {
	CONode* node = CmdOptions_Create(name);
	CmdOptions_AddElement(&node->option->possibleparameters,
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
	return atof(CmdOptions_Get(name));
}

int CmdOptions_GetAll(char* name, char** values, unsigned int* count) {
	CONode* node = CmdOptions_Create(name);
	if (node == 0)
		return 1;
	values = node->option->values;
	*count = node->option->valuecount;
	return 0;
}

void CmdOptions_AddElement(char*** target, int* counter, char* element) {
	int cnt = *counter;
	char** old = 0;
	if (target != 0)
		old = *target;
	*target = malloc((cnt + 1) * sizeof(char*));
	if (old != 0)
		memcpy(target, old, (cnt) * sizeof(char*));
	(*target)[cnt] = element;
	if (old != 0)
		free(old);
	*counter = cnt + 1;
}
