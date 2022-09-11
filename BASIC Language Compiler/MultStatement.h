#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class MultStatement: public Statement
{
private:
	std::string m_variableName;
    std::string m_mult;
	
public:
	MultStatement(std::string variableName, std::string value);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif