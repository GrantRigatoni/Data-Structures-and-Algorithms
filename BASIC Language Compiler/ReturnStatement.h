#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class ReturnStatement: public Statement
{
private:
    int m_Return;
	
public:
	ReturnStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif