#include <iostream>

#include "node.h"
#include "codegen.h"

using namespace std;

extern int yyparse();
extern NBlock* programBlock;
extern FILE* yyin;

void createCoreFunctions(CodeGenContext& context);


int main(int argc, char **argv)
{
	++argv, --argc;
	
	if (argc > 0)
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;	

	if(yyparse())
		return 0;

	InitializeNativeTarget();
	CodeGenContext context;
	createCoreFunctions(context);
	context.generateCode(*programBlock);
	context.runCode();

	context.writeToFile();
	
	return 0;
}


