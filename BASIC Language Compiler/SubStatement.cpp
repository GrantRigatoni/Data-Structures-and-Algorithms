#include "SubStatement.h"
#include <ctype.h>
using namespace std;
//put deconstructor in statement and delete in interpreter

SubStatement::SubStatement(string variableName, string value)
    : m_variableName(variableName), m_sub(value)
{
    //default constructor
}


void SubStatement::execute(ProgramState * state, ostream &outf)
{
    int subing;
    if (isdigit(m_sub[0]))//checks if m_sub is an int and stores m_sub as an int if true
    {
        subing = stoi(m_sub);
    }else if ((m_sub[0] == '-') && (isdigit(m_sub[1])))//checks if m_sub is an int and stores m_sub as an int if true
    {
        subing = stoi(m_sub);
    }else
    {
        subing = state->getVariableValue(m_sub);//stores variable value of m_div
    }
    int newVal;//tracks the new value of the 1st variable passed in
    newVal = state->getVariableValue(m_variableName);
    newVal -= subing;//subtracts
    state->updateVariableValue(m_variableName, newVal);//updates variable
	state->incrementCounter();
}