#include "ReturnStatement.h"
using namespace std;

ReturnStatement::ReturnStatement()
{
    //default constructor
}

void ReturnStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
    if (state->stackEmpty())//if stack is empty, terminate the program
    {
        state->killCounter();
        return;
    }
    m_Return = state->popFromStack();//stores the value poped from the stack
    state->setCounter(m_Return);//returns the program to most recent GOSUB
    state->incrementCounter();
    
}