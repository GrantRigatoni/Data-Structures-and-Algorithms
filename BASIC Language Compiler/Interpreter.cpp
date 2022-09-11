// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "EndStatement.h"
#include "PrintStatement.h"
#include "PrintallStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "GotoStatement.h"
#include "GosubStatement.h"
#include "ReturnStatement.h"
#include "IfStatement.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <iostream>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns a vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	string var;
	string operato;
	string then;
	int lineNum;
	int val;

	ss << line;

	ss >> lineNum;//reads in line number
	ss >> type;//reads in type
	
	if ( type == "LET" )//tests for each possible line of code
	{
		ss >> var;
		ss >> val;
		statement = new LetStatement(var, val);
	} 
	else if (type == "PRINT")
	{
		ss >> var;
		statement = new PrintStatement(var);

	}
	else if (type == "END" || type == ".")
	{
		statement = new EndStatement();
	}
	else if (type == "PRINTALL")
	{
		statement = new PrintallStatement();
		
	}else if (type == "ADD")
	{
		ss >> var;
		ss >> operato;
		statement = new AddStatement(var, operato);
		


	}else if (type == "SUB")
	{
		ss >> var;
		ss >> operato;
		statement = new SubStatement(var, operato);

	}else if (type == "MULT")
	{
		ss >> var;
		ss >> operato;
		statement = new MultStatement(var, operato);

	}else if (type == "DIV")
	{
		ss >> var;
		ss >> operato;
		statement = new DivStatement(var, operato);

	}else if (type == "GOTO")
	{
		ss >> val;
		statement = new GotoStatement(val);
	}
	else if (type == "GOSUB")
	{
		ss >> val;
		statement = new GosubStatement(val);
	}else if (type == "RETURN")
	{
		statement = new ReturnStatement();
	}else if (type == "IF")
	{
		ss >> var;
		ss >> operato;
		ss >> val;
		ss >> then;
		ss >> lineNum;
		statement = new IfStatement(var, operato, val, lineNum);
	}
		
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );
	int numberOfLines = program.size();
	ProgramState* state = new ProgramState(numberOfLines);
	//make program state that changes the counter
	// Incomplete;  TODO:  Finish this function!
	int currLine = 1;//starts at the beginning of the program
	//while (program[currLine] != NULL)
	while (currLine != 0)
	{
		program[currLine]->execute(state, outf);//executes each line
		currLine = state->getLineNumber();//access current line number
	}
	for (int i = 1; i < numberOfLines; i++)//deltetes memory allocated in parseProgram
	{
		delete program[i];
	}
	delete state;//deletes memory allocated for program state

}
