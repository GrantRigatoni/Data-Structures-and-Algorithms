#include "AddStatement.h"
#include <ctype.h>
using namespace std;
//put deconstructor in statement and delete in interpreter

AddStatement::AddStatement(string variableName, string value)
    : m_variableName(variableName), m_add(value)
{
    //default constructor
}


void AddStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
    int adding;
    if (isdigit(m_add[0]))//checks if m_add is a variable or int
    {
        adding = stoi(m_add);
    }else if ((m_add[0] == '-') && (isdigit(m_add[1])))
    {
        adding = stoi(m_add);
    }else
    {
        adding = state->getVariableValue(m_add);//gets value of m_add if it is a variable
    }
    int newVal;//stores new variable value
    newVal = state->getVariableValue(m_variableName);
    newVal += adding;
    state->updateVariableValue(m_variableName, newVal);//updates the old variable
	state->incrementCounter();
}