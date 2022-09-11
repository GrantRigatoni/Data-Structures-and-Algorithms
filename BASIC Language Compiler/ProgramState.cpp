#include "ProgramState.h"
using namespace std;
ProgramState::ProgramState(int numLines)
    : m_numLines (numLines)
{
    lineCount = 1;//initialize the line # to the first line

}

void ProgramState::updateVariableValue(string variableName, int newVal)
{
	variables[variableName] = newVal;//updates variable if it exist or creates a new variable



}
int ProgramState::getLineNumber()
{
    return lineCount;
}

void ProgramState::addToStack(int line)
{
    stag.push(line);

}

void ProgramState::incrementCounter()
{
    lineCount++;

}

void ProgramState::killCounter()
{
    lineCount = 0;

}
void ProgramState::setCounter(int line)
{
    lineCount = line;

}

int ProgramState::getVariableValue(string variableName)
{
	map<string, int>::iterator it;
	if(variables.count(variableName) > 0)//tests if var has been declared
    {
		it = variables.find(variableName);//it is a pointer to the index
    	int variableValue = it->second;
		return variableValue;
	}

		return 0;
}

string ProgramState::outputAll(string toPrint)
{
	for (map<string, int>::iterator it = variables.begin(); it != variables.end(); it++)
	{
    	toPrint += it->first;
		toPrint += " ";
		toPrint += to_string(it->second);
		toPrint += "\n";

    }
	toPrint.pop_back();
	return toPrint;
}

int ProgramState::getNumLines()
{
	return m_numLines;
}

int ProgramState::popFromStack()
{
	int top = stag.top();
	stag.pop();
	return top;
}

bool ProgramState::stackEmpty()
{
	return stag.empty();
}