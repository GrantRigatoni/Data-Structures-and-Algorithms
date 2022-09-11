// PrintStatement.cpp:
#include "PrintStatement.h"


PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	int variableValue;
	variableValue = state->getVariableValue(m_variableName);
	outf << variableValue << std::endl;
	state->incrementCounter();
}
