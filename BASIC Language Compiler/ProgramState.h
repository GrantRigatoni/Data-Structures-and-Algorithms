// ProgramState.h

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED
#include <map>
#include <stack>
#include <string>


class ProgramState
{
public:
	ProgramState(int numLines);//itializes
	int getLineNumber();//used to access current line number (edge cases)
	int getNumLines();//used to get the total number of lines in the program
	void updateVariableValue(std::string variableName, int newVal);//tests if a variable exists and updates it or creates a new variable
	void incrementCounter();//used after a line other than return/GOTO/GOSUB/END/. is executed
	void addToStack(int line);//for GOSUB Function
	int popFromStack();//removes the top integer on the stack and returns it
	bool stackEmpty();//checks if stack is empty
	void killCounter();//sets currline to zero - ending the program
	void setCounter(int line);//sets the current line of execution to int line
	std::string outputAll(std::string toPrint);//takes in an empty string and concatonates the contents of the map to it
	int getVariableValue(std::string variableName);//gets the value of inserted variable


protected:
std::map<std::string, int> variables;//holds and keeps track of all variables
std::stack<int> stag;//stack to hold GOSUB values

private:
	int m_numLines;//total number of program lines
	int lineCount;//represents the current line of execution
	
};

#endif
