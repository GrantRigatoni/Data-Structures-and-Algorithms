#include "GosubStatement.h"
using namespace std;

GosubStatement::GosubStatement(int value)
    : m_Gosub(value)
{
    //default constructor
}

void GosubStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
    if (m_Gosub < 1 || m_Gosub >= state->getNumLines())
    {
        outf << "Illegal jump instruction" << endl;
        state->killCounter();
        return;
    }
    state->addToStack(state->getLineNumber());//adds current line number to stack
    state->setCounter(m_Gosub);//goes to m_Gosub line
    
}