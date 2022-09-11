#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class AddStatement: public Statement
{
private:
	std::string m_variableName;
    std::string m_add;
	
	
public:
	AddStatement(std::string variableName, std::string value);
	
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif