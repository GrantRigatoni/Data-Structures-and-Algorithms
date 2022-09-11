#include "EndStatement.h"
using namespace std;

EndStatement::EndStatement()
{
    //default constructor
}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void EndStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	state->killCounter();//sets the program counter to zero, ending the while loop
	
	
}
