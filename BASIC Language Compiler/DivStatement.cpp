#include "DivStatement.h"
using namespace std;

DivStatement::DivStatement(string variableName, string value)
    : m_variableName(variableName), m_div(value)
{
    //default constructor
}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void DivStatement::execute(ProgramState * state, ostream &outf)
{
	// convert string to int or access variable's value
    int diving;
    if (isdigit(m_div[0]))//checks if m_div is a variable or int
    {
        diving = stoi(m_div);
    }else if ((m_div[0] == '-') && (isdigit(m_div[1])))
    {
        diving = stoi(m_div);
    }else
    {
        diving = state->getVariableValue(m_div);
    }

    if (diving == 0)
    {
        outf << "Divide by zero exception" << endl;//checks if we are dividing by zero
        state->killCounter();
        return;
    }
    int newVal;
    newVal = state->getVariableValue(m_variableName);//divide first paramater by the second
    newVal /= diving;
    state->updateVariableValue(m_variableName, newVal);//update variable value
	state->incrementCounter();
}