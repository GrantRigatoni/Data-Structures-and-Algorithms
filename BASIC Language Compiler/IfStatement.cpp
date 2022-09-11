// IfStatement.cpp:
#include "IfStatement.h"
using namespace std;

IfStatement::IfStatement(std::string variableName, std::string operato, int If, int Goto)
	: m_variableName( variableName ), m_operator(operato), m_If(If), m_Goto(Goto)
{}


// The IfStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void IfStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
    bool logic = false;//determines if the Goto statement should be executed
    if (m_operator == "<")//run each operator and test if it is true
    {
        if(state->getVariableValue(m_variableName) < m_If)
        {
            logic = true;
        }
    }else if(m_operator == "<=")
    {
        if(state->getVariableValue(m_variableName) <= m_If)
        {
            logic = true;
        }
    }else if(m_operator == ">")
    {
        if(state->getVariableValue(m_variableName) > m_If)
        {
            logic = true;
        }
    }else if(m_operator == ">=")
    {
        if(state->getVariableValue(m_variableName) >= m_If)
        {
            logic = true;
        }
        
    }else if(m_operator == "=")
    {
        if(state->getVariableValue(m_variableName) == m_If)
        {
            logic = true;
        }
    }else if(m_operator == "<>")
    {
        if(state->getVariableValue(m_variableName) != m_If)
        {
            logic = true;
        }
    }

	if (logic){//executes Goto if the if statement evaluates true
	if (m_Goto < 1 || m_Goto >= state->getNumLines())//Goto function
    {
        outf << "Illegal jump instruction" << endl;
        state->killCounter();
        return;
    }

    state->setCounter(m_Goto);
    }
}
