#include "GotoStatement.h"
using namespace std;

GotoStatement::GotoStatement(int value)
    : m_Goto(value)
{
    //default constructor
}

void GotoStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
    if (m_Goto < 1 || m_Goto >= state->getNumLines())//checks if line jump is invalid
    {
        outf << "Illegal jump instruction" << endl;//error message output
        state->killCounter();//stops program
        return;
    }

    state->setCounter(m_Goto);//changes program output
}