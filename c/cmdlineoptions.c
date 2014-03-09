#include "cmdlineoptions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CmdOptions cmdoptions;

void CmdLO_Init(char addhelp) {
	CmdLO_InitCmd(addhelp, 0);
}

void CmdLO_InitCmd(char addhelp, char cmdchar) {
	if (cmdoptions.init == 0) {
		cmdoptions.init = 1;
		if (cmdchar != 0)
			cmdoptions.cmdchar = cmdchar;
		else
			cmdoptions.cmdchar = '-';
		// do we have to init something?
		// add the help option
		if (addhelp != 0) {
			CmdLO_Add("help", "--help");
			CmdLO_Add("help", "-h");
			CmdLO_Add("help", "-?");
			CmdLO_AddDescription("help", "Display the help text.");
		}
	}
}

CONode* CmdLO_Create(char* name) {
	CONode* node = CmdLO_NodeGet(name);
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

CONode* CmdLO_NodeGet(char* name) {
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

CONode* CmdLO_SearchNode(char* cmdlineargument) {
	if (cmdoptions.options != 0) {
		CONode* node = cmdoptions.options;
		while (node != 0) {
			if (node->option->optionscount > 0) {
				int i = 0;
				for (; i < node->option->optionscount; ++i) {
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

int CmdLO_Parse(int argc, char** argv) {
	if (argc > 1) {
		int i = 1;
		CONode* cnode = 0;
		char* carg = 0;
		char failed = 0;
		for (; i < argc; ++i) {
			if (argv[i][0] == cmdoptions.cmdchar) {
				if ((cnode = CmdLO_SearchNode(argv[i])) != 0) {
					cnode->option->set = 1;
					continue;
				} else {
					carg = argv[i];
					fprintf(stderr,
							"CmdLineOptions: Unrecognized option '%s'.\n",
							carg);
					cnode = 0;
					continue;
				}
			}
			if (cnode != 0) {
				if (cnode->option->possibleparametercount == 0) {
					CmdLO_AddElement(&(cnode->option->values),
							&(cnode->option->valuecount), argv[i]);
				} else {
					int j = 0;
					for (; j < cnode->option->possibleparametercount; ++j) {
						if (strcmp(argv[i],
								cnode->option->possibleparameters[j]) == 0) {
							CmdLO_AddElement(&(cnode->option->values),
									&(cnode->option->valuecount), argv[i]);
							break;
						}
					}
					if (cnode->option->possibleparametercount == j) {
						fprintf(stderr,
								"CmdLineOptions: Parameter '%s' is not allowed, parameter not added.\n",
								argv[i]);
					}
				}
			} else {
				fprintf(stderr,
						"CmdLineOptions: Unrecognized option parameter '%s' for unrecognized option '%s'.\n",
						argv[i], carg);
			}
		}
	}
	// parsing done or no arguments -> display help text
	if (CmdLO_IsSet("help") > 0 || argc == 0) {
		// iterate through the list
		printf("-options\n");
		CONode* node = cmdoptions.options;
		unsigned int i = 0;
		while (node != 0) {
			printf("\t%s\t(", node->option->name);
			for (i = 0; i < node->option->optionscount; ++i) {
				printf("%s", node->option->options[i]);
				if (i < node->option->optionscount - 1) {
					printf(", ");
				}
			}
			printf("): default=[");
			for (i = 0; i < node->option->defaultparametercount; ++i) {
				printf("\"%s\"", node->option->defaultparameters[i]);
				if (i < node->option->defaultparametercount - 1) {
					printf(", ");
				}
			}
			printf("]\n");
			printf("\t\t%s\n", node->option->description);
			if (node->option->possibleparametercount > 0) {
				printf("\t\t(possible parameters:");
				for (i = 0; i < node->option->possibleparametercount; ++i) {
					printf("\"%s\"", node->option->possibleparameters[i]);
					if (i < node->option->possibleparametercount - 1) {
						printf(", ");
					}
				}
				printf(")\n");
			}
			if (node->option->set > 0) {
				if (node->option->valuecount > 0) {
					printf("\t\t->> current value: ");
					for (i = 0; i < node->option->valuecount; ++i) {
						printf("\"%s\"", node->option->values[i]);
						if (i < node->option->valuecount - 1) {
							printf(", ");
						}
					}
				} else {
					printf("\t\t->> is set!");
				}
				printf("\n");
			}
			if (node->next != 0)
				printf("\n");
			node = node->next;
		}
		printf("/options\n");
	}
	// no arguments!
	return 1;
}

void CmdLO_Add(char* name, char* option) {
	CONode* node = CmdLO_Create(name);
	CmdLO_AddElement(&(node->option->options), &(node->option->optionscount),
			option);
}

void CmdLO_AddDefaultParameter(char* name, char* defaultparameter) {
	CONode* node = CmdLO_Create(name);
	CmdLO_AddElement(&(node->option->defaultparameters),
			&(node->option->defaultparametercount), defaultparameter);
}

void CmdLO_AddPossibleParameter(char* name, char* possibleParameter) {
	CONode* node = CmdLO_Create(name);
	CmdLO_AddElement(&(node->option->possibleparameters),
			&(node->option->possibleparametercount), possibleParameter);
}

void CmdLO_AddDescription(char* name, char* description) {
	CONode* node = CmdLO_Create(name);
	node->option->description = description;
}

int CmdLO_IsSet(char* name) {
	CONode* node = CmdLO_Create(name);
	return node->option->set;
}

char* CmdLO_Get(char* name) {
	CONode* node = CmdLO_Create(name);
	if (CmdLO_IsSet(name) && node->option->valuecount > 0)
		return node->option->values[0];
	return 0;
}

int CmdLO_GetInt(char* name) {
	return atoi(CmdLO_Get(name));
}

long CmdLO_GetLong(char* name) {
	return atol(CmdLO_Get(name));
}

double CmdLO_GetDouble(char* name) {
	return atof(CmdLO_Get(name));
}

int CmdLO_GetAll(char* name, char** values, unsigned int* count) {
	CONode* node = CmdLO_Create(name);
	if (node == 0)
		return 1;
	values = node->option->values;
	*count = node->option->valuecount;
	return 0;
}

void CmdLO_AddElement(char*** target, unsigned int* counter, char* element) {
	unsigned int cnt = *counter;
	char** old = 0;
	if (*target != 0)
		old = *target;
	*target = malloc((cnt + 1) * sizeof(char*));
	if (old != 0)
		memcpy(*target, old, (cnt) * sizeof(char*));
	*(*target + cnt) = malloc((strlen(element) + 1) * sizeof(char));
	memcpy(*(*target + cnt), element, strlen(element) + 1);
	if (old != 0)
		free(old);
	*counter = cnt + 1;
}

void CmdLO_Destroy() {
	// free everything inside the structures and then the whole tree
	CONode * node = cmdoptions.options;
	int i = 0;
	while (node != 0) {
		if (node->option->optionscount > 0) {
			i = 0;
			for (; i < node->option->optionscount; ++i)
				free(node->option->options[i]);
			free(node->option->options);
		}
		if (node->option->defaultparametercount > 0) {
			i = 0;
			for (; i < node->option->defaultparametercount; ++i)
				free(node->option->defaultparameters[i]);
			free(node->option->defaultparameters);
		}
		if (node->option->possibleparametercount > 0) {
			i = 0;
			for (; i < node->option->possibleparametercount; ++i)
				free(node->option->possibleparameters[i]);
			free(node->option->possibleparameters);
		}
		if (node->option->valuecount > 0) {
			i = 0;
			for (; i < node->option->valuecount; ++i)
				free(node->option->values[i]);
			free(node->option->values);
		}
		free(node->option);
		CONode* old = node;
		node = node->next;
		free(old);
	}
	cmdoptions.options = 0;
	cmdoptions.init = 0;
}
