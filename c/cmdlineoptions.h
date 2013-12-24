#ifndef CMDLINEOPTIONS_H
#define CMDLINEOPTIONS_H


struct Option {
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
	bool 		set; 		// boolean if this option has been set
};

struct CmdOptions {
	bool 		init;
	Option** 	options;
};

/** Init function dummy.
 */
void CmdOptions_Init();

/**
 * The heart of this whole thing, the parsing of all options...
 */
int CmdOptions_Parse(int argc, char** argv);

/**
 * Add a new option with a new name, or a new option alternative to an existing one.
 */
int CmdOptions_Add(char* name, char* option);
/**
 * Add a defaultparameter to an existing option, specified by name.
 */
int CmdOptions_AddDefaultParameter(char* name, char* defaultparameter);
/**
 * Add a possible parameter to an existing option, specified by name.
 * Keep in mind that you LIMIT that option to all possible parameters (?)
 */
int CmdOptions_AddPossibleParameter(char* name, char* possibleParameter);
/**
 * Add a description to an existing option, specified by name.
 */
int CmdOptions_AddDescription(char* name, char* description);

/**
 * Check if the option specified by name is set.
 */
bool 	CmdOptions_IsSet(char* name);
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

#endif

