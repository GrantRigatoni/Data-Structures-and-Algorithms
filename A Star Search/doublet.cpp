#include "MinHeap.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

int findFValue(int gvalue, const string &currWord, const string &tail);

int main (int argc, char* argv[])
{
    //read file in
    if (argc != 4)
    {
        throw logic_error("Not Correct Command Line Inputs");
        return -1;
    }
    ifstream file(argv[3]);//add.c_string
    if (file.fail())
    {
        throw logic_error("File failed to open.");
        return -1;
    }

    /*take in each line and build the graph*/
	string head = argv[1];
	string tail = argv[2];
	int properWordLength = head.size();
    set<string> visitedNodes;
    set<string> allNodes;
    map<string, vector<string>> graph;//each word(node) as key and its outgoing edges as value
    map<string, bool> exploredStatus;//each node as a key and whether or not its been explored
	map<string, string> predecessor;//stores the predecessor of a node
	map<string, int> fvalueMap;
	map<string, int> gvalueMap;
    int numberOfWords;
	int numberOfProperWords;
	int expansion = 0;
	int steps = 1;
	bool transformationFound = false;
    file >> numberOfWords;

	for(int j = 0; j < properWordLength; j++)
	{
				//makes all start and end word lowercase
				head[j] = tolower(head[j]);
				tail[j] = tolower(tail[j]);
	}
    
	//reads in all words of length equal to head
	for (int i = 0; i < numberOfWords; i++)
    {
        //add all words to set
        string currWord;
        file >> currWord;
		if (currWord.size() == properWordLength)//ignores words of improper length
		{
			for(int j = 0; j < properWordLength; j++)
			{
				//makes all words lowercase
				currWord[j] = tolower(currWord[j]);
			}
			numberOfProperWords++;
        	allNodes.insert(currWord);
		}

    }

	for(set<string>::iterator itr = allNodes.begin(); itr != allNodes.end(); itr++)
	{
		//map each node's outgoing edges
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		string currWord = *itr;//stores a word
		string tempCurrWord = currWord;
		vector<string> tempOutgoingEdges;//stores all outgoing edges of *itr
		/*change each letter in each string to each letter a-z (except for when it equals itself)
		and add those to the temporary string*/
		for(int i = 0; i < alphabet.size(); i++)
		{
			/*finds all 1-letter variations of a word and
			tests to see if they are a node*/
			for(int j = 0; j < properWordLength; j++)
			{
				tempCurrWord = currWord;
				tempCurrWord[j] = alphabet[i];
				if(tempCurrWord != currWord && allNodes.count(tempCurrWord))
				{
					/*adds an outgoing edge to node if a one-letter variation of the
					word is present in the set of all nodes	and isn't itself*/
					tempOutgoingEdges.push_back(tempCurrWord);
				}
			}
		}
		//now that we have all outgoing edges of node *itr we store it in map
		graph.insert(pair<string, vector<string>>(currWord, tempOutgoingEdges));
		exploredStatus.insert(pair<string, bool>(currWord, false));
		fvalueMap.insert(pair<string, int>(currWord, INT_MAX));//initializes f so that any heuristic will override it later
		gvalueMap.insert(pair<string,int>(currWord, -1));
		predecessor.insert(pair<string,string>(currWord, head));
	}

	//start of A*
	MinHeap<string> heap(2);
	int currFvalue = findFValue(0, head, tail);
	heap.add(head, currFvalue);
	while (!(heap.isEmpty()))
	{
		string currNode = heap.peek();
		if (currNode == tail)//word found so we find steps and break
		{
			transformationFound = true;
			while (predecessor[currNode] != head)
			{
				currNode = predecessor[currNode];
				steps++;
			}
			break;
		}
		heap.remove();//each remove increments the expansion by 1
		expansion++;
		vector<string> outEdgesOfcurrNode = graph[currNode];//stores outgoing edges of currNode
		int gvalue = 1;
		string tempcurrNode = currNode;
		if (currNode == head) 
		{
			//makes head node explored and gvalue 0
			gvalue = 0;
			fvalueMap[currNode] = findFValue(gvalue, currNode, tail); //store f value of node if it 1.is being discovered or 2.found a better path
			gvalueMap[currNode] = gvalue;
			exploredStatus[currNode] = true;//edge i of currNode marked as explored
		}
		while (predecessor[tempcurrNode] != head)//calculates gvalue by iterating through the total # of predecessors
		{
			//cout << "finding predecessors" << endl;
			tempcurrNode = predecessor[tempcurrNode];
			gvalue++;
		}

		for (int i = 0; i < outEdgesOfcurrNode.size(); i++)
		{
			//cout << "in for loop" << endl;
			currFvalue = findFValue(gvalue, outEdgesOfcurrNode[i], tail);
			if ((currFvalue == fvalueMap[outEdgesOfcurrNode[i]] && gvalue >= gvalueMap[outEdgesOfcurrNode[i]]) || !(exploredStatus[outEdgesOfcurrNode[i]]) || currFvalue < fvalueMap[outEdgesOfcurrNode[i]])
			//if f values are the same and the incomming node has a bigger g, continue
			{
			//has edge i of currNode been explored? or is the f value on this new path better than when we discovered this node before?
				if(!(exploredStatus[outEdgesOfcurrNode[i]]))
				{
					heap.add(outEdgesOfcurrNode[i], currFvalue);
				}
					fvalueMap[outEdgesOfcurrNode[i]] = currFvalue; //store f value of node if it 1.is being discovered or 2.found a better path
					gvalueMap[outEdgesOfcurrNode[i]] = gvalue;
					exploredStatus[outEdgesOfcurrNode[i]] = true;//edge i of currNode marked as explored
					predecessor[outEdgesOfcurrNode[i]] = currNode;//sets prev Node of new node to currNode
			}else if (currFvalue == fvalueMap[outEdgesOfcurrNode[i]])
			{
				heap.add(outEdgesOfcurrNode[i], currFvalue);//adds the node with same currFvalue
			}
		}
	}
	//cout << "end of while" << endl;
	if (transformationFound){
	//cout << "steps: " << steps<< endl;
	cout << steps << endl;
	}else
	{
		cout << "No transformation" << endl;
	}
	//cout << "expansions: " << expansion << endl;
	cout << expansion << endl;
    return 0;
}


int findFValue(int gvalue, const string &currWord, const string &tail)
{
	int f = 0;
	int p;

	for (int i = 0; i <= tail.size(); i++)//calculates heuristic
	{
		if (currWord[i] != tail[i])
		{
			f++;
		}
	}
	p = (gvalue + f)*(currWord.size() + 1) + f;
	return p;
}