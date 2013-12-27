#include "cmdlineoptions.h"

void configureOptions() {
	CmdOptions_Init(1);
	CmdOptions_Add("test","--test");
	CmdOptions_Add("test","-t");
	CmdOptions_AddDescription("test","This is a test Option.");

}

int main(int argc, char** argv) {
	configureOptions();
	CmdOptions_Parse(argc,argv);

}


