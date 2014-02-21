#include "cmdlineoptions.h"

void configureOptions() {
	CmdLO_Init(1);
	CmdLO_Add("test","--test");
	CmdLO_Add("test","-t");
	CmdLO_AddDescription("test", "This is a test Option.");

}

int main(int argc, char** argv) {
	configureOptions();
	CmdLO_Parse(argc,argv);

}


