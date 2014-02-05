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
void CmdOptions_InitCmd(char addhelp, char cmdchar);
void CmdOptions_Init(char addhelp);

/**
 * The heart of this whole thing, the parsing of all options...
 */
int CmdOptions_Parse(int argc, char** argv);
CONode* CmdOptions_SearchNode(char* cmdlineargument);

/**
 * Add a new option with a new name, or a new option alternative to an existing one.
 */
void CmdOptions_Add(char* name, char* option);
/**
 * Add a defaultparameter to an existing option, specified by name.
 */
void CmdOptions_AddDefaultParameter(char* name, char* defaultparameter);
/**
 * Add a possible parameter to an existing option, specified by name.
 * Keep in mind that you LIMIT that option to all possible parameters (?)
 */
void CmdOptions_AddPossibleParameter(char* name, char* possibleParameter);
/**
 * Add a description to an existing option, specified by name.
 */
void CmdOptions_AddDescription(char* name, char* description);

/**
 * Check if the option specified by name is set.
 */
int 	CmdOptions_IsSet(char* name);
/**
 * Get first parameter of the option specified by name.
 */
char* 	CmdOptions_Get(char* name);
/**
 * Get the first parameter of the option specified by name as integer.
 */
int 	CmdOptions_GetInt(char* name);
/**
 * Get the first parameter of the option specified by name as long.
 */
long 	CmdOptions_GetLong(char* name);
/**
 * Get the first parameter of the option specified by name as double.
 */
double 	CmdOptions_GetDouble(char* name);
/**
 * Get all parameters of the given option name as string array.
 * This is the 'Do It Yourself' retrieve function.
 */
int 	CmdOptions_GetAll(char* name, char** values, unsigned int* count);

CONode*	CmdOptions_Create(char* name);
CONode* CmdOptions_NodeGet(char* name);
void  CmdOptions_AddElement(char*** target,int* counter, char* element);
#endif

