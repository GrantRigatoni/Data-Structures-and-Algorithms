// EndStatement.h



#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class EndStatement: public Statement
{
private:
	std::string m_variableName;
	int m_value;


public:
	EndStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif