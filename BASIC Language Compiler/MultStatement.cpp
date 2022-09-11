#include "MultStatement.h"
#include <ctype.h>
using namespace std;
//put deconstructor in statement and delete in interpreter

MultStatement::MultStatement(string variableName, string value)
    : m_variableName(variableName), m_mult(value)
{
    //default constructor
}


void MultStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
    int multing;
    if (isdigit(m_mult[0]))//checks if m_mult is an int and stores m_mult as an int if true
    {
        multing = stoi(m_mult);
    }else if ((m_mult[0] == '-') && (isdigit(m_mult[1])))//checks if m_mult is an int and stores m_mult as an int if true
    {
        multing = stoi(m_mult);
    }else
    {
        multing = state->getVariableValue(m_mult);//stores the value of m_mult if it is a variable
    }
    int newVal;//tracks value that will update the variable passed in
    newVal = state->getVariableValue(m_variableName);
    newVal *= multing;
    state->updateVariableValue(m_variableName, newVal);
	state->incrementCounter();
}