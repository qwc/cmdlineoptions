#ifndef CMDLINEOPTIONS_H
#define CMDLINEOPTIONS_H

typedef struct _Option {
	char* 		name; 	// the name of this option
	char** 		options; 	//dashed option name and alternatives
	unsigned int 	optionscount; 	// count of option alternatives
	char** 		possibleparameters; // possible parameters for this options
	unsigned int 	possibleparametercount; // count of possible parameters
	char* 		description; 	// description of this parameter
	char** 		defaultparameters; 	// default parameters
	unsigned int 	defaultparametercount; 	// count of default parameters
	
	char** 		values; 	// values
	unsigned int 	valuecount; 	// size of the values, if more than one...
	char 		set; 		// boolean if this option has been set
} Option;


typedef struct _CONode {
	//CONode* prev;
	struct _CONode* next;
	Option* option;
} CONode;

typedef struct _CmdOptions {
	char 		init;
	CONode*  	options;
	char		cmdchar;
} CmdOptions;

/**
 * Main structure
 */
extern CmdOptions cmdoptions;

/** Init function.
 */
void CmdLO_InitCmd(char addhelp, char cmdchar);
void CmdLO_Init(char addhelp);

/**
 * The heart of this whole thing, the parsing of all options...
 */
int CmdLO_Parse(int argc, char** argv);
CONode* CmdLO_SearchNode(char* cmdlineargument);

/**
 * Add a new option with a new name, or a new option alternative to an existing one.
 */
void CmdLO_Add(char* name, char* option);
/**
 * Add a defaultparameter to an existing option, specified by name.
 */
void CmdLO_AddDefaultParameter(char* name, char* defaultparameter);
/**
 * Add a possible parameter to an existing option, specified by name.
 * Keep in mind that you LIMIT that option to all possible parameters (?)
 */
void CmdLO_AddPossibleParameter(char* name, char* possibleParameter);
/**
 * Add a description to an existing option, specified by name.
 */
void CmdLO_AddDescription(char* name, char* description);

/**
 * Check if the option specified by name is set.
 */
int 	CmdLO_IsSet(char* name);
/**
 * Get first parameter of the option specified by name.
 */
char* 	CmdLO_Get(char* name);
/**
 * Get the first parameter of the option specified by name as integer.
 */
int 	CmdLO_GetInt(char* name);
/**
 * Get the first parameter of the option specified by name as long.
 */
long 	CmdLO_GetLong(char* name);
/**
 * Get the first parameter of the option specified by name as double.
 */
double 	CmdLO_GetDouble(char* name);
/**
 * Get all parameters of the given option name as string array.
 * This is the 'Do It Yourself' retrieve function.
 */
int 	CmdLO_GetAll(char* name, char** values, unsigned int* count);
/**
 * Get the node with the given name or create a new one with that name.
 */
CONode*	CmdLO_Create(char* name);
/**
 * Just get the node with the given name.
 */
CONode* CmdLO_NodeGet(char* name);
/**
 * Convenience function to add a string to a string array.
 */
void  CmdLO_AddElement(char*** target,unsigned int* counter, char* element);
/**
 * Clean up everything, like nothing ever happened...
 */
void CmdLO_Destroy();


#endif

