#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
	std::string m_variableName;
    std::string m_operator;
	int m_If;
    int m_Goto;


public:
	IfStatement(std::string variableName, std::string operato, int If, int Goto);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
