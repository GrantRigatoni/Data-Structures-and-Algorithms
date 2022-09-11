#include "PrintallStatement.h"
using namespace std;

PrintallStatement::PrintallStatement()
{
    //default constructor
}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void PrintallStatement::execute(ProgramState * state, ostream &outf)
{
    string toPrint = "";
    toPrint = state->outputAll(toPrint);//passes in empty string and replaces it with an output of all variables and values
    outf << toPrint << endl;//outputs variables and values
	state->incrementCounter();
}