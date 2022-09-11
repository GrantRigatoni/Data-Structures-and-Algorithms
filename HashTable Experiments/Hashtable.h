#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <cmath>
#include <queue>
#include <fstream>

template <class T>
class Hashtable
{
    public:
    Hashtable (bool debug = false, unsigned int size = 11);//constructor
    ~Hashtable ();//deconstructor
    int add (std::string k, const T& val);//checks if k exists, and enters if it doesn't
    const T& lookup (std::string k);//returns value associated with k (returns garbage or a different T if non existant)
    void reportAll (std::ostream & out) const;//outputs every (key, value) pair in the order they appear in hash table
	protected:
	int hash (std::string k) const;

    private:
    void resize ();
	bool debug;
	unsigned int size;
	int rVals[5];//from r5 - r1
	int aConstVals[6] = {1, 27, 729, 19683, 531441, 14348907};//from a6 - a1
	std::string* kVals;//our hashtable
	T* TVals;//also our hashtable
	double totalInserted;
	std::queue<std::string> orderAdded;//tracks order in which items were added to the hashtable
	std::queue<T> orderAdded2;
	T garbageVal;//used in lookup if object not found
};

template <class T>
Hashtable<T>::Hashtable(bool debug, unsigned int size)
{
	this->debug = debug;
	this->size = size;
	kVals = new std::string [size];//initialize the size of the hashtable
	TVals = new T [size];
	totalInserted = 0.0;
	if (debug)
	{
		rVals[4] = 983132572;
		rVals[3] = 1468777056;
		rVals[2] = 552714139;
		rVals[1] = 984953261;
		rVals[0] = 261934300;
	}else
	{
		//assigns random r values 
		srand(rand() ^ time(NULL));
		rVals[4] = rand() % size;
		rVals[3] = rand() % size;
		rVals[2] = rand() % size;
		rVals[1] = rand() % size;
		rVals[0] = rand() % size;
	}
}

template <class T>
Hashtable<T>::~Hashtable()
{
    delete[] TVals;
	delete[] kVals;
}


template <class T>
int Hashtable<T>::add (std::string k, const T& val){//checks if k exists, and enters if it doesn't
	double loadFactor = (totalInserted)/size;
	if (loadFactor > 0.5)//resize if load factor is too big
	{
		resize();
	}
	int hashed = hash(k);//find the hash value
	int spot = hashed;
	int probe = 0;//counts # of probes
	int quadfactor = 1;
	int failedToAdd = 0;
	
	while (true)
	{
		
		if(kVals[spot] == "")
		{
			//insert at newest spot and leave
			kVals[spot] = k;
			TVals[spot] = val;
			orderAdded.push(k);
			orderAdded2.push(val);
			totalInserted++;
			break;

		}else if (kVals[spot] == k)//if already in the hash
		{
			//item exists so we do nothing
			break;
		}
		probe++;
		spot = (hashed + quadfactor*quadfactor) % size;//find next spot
		quadfactor++;
		if(failedToAdd > size)
		{
			throw std::logic_error("Table Size not Prime - cannot add element");
		}
		failedToAdd++;
	}
	
	return probe;
}

template <class T>
int Hashtable<T>::hash (std::string k) const
{
	int tempSize = k.size();//get size of string
	tempSize -= 6;
	long long aVals[6] = {0, 0, 0, 0, 0, 0};//from a6 - a1 letters valued from 1-26
	long long wVals[5] = {0, 0, 0, 0, 0};//from w5 - w1 each initialized to zero
	int currW = 0;//tracks which w we are on
	int tempW = 0;//stores each wValue
	while (tempSize > 0)
	{
		for (int i = 0; i < 6; i++)
		{
			int access = i;
			aVals[i] = int(k[tempSize + 5 - i]) - 96;//converts chars to numbers and stores them
			tempW += aConstVals[i]*aVals[i];//multiply each letter's val by their respective constants
			aVals[i] = 0;//reinitializes aVal to 0
		}
		wVals[currW] = tempW;
		tempW = 0;
		tempSize -= 6;
		currW++;
	}
	int lettersLeftToDo = 6 + tempSize;
	for(int i = 0; i < lettersLeftToDo; i++)
	{
		aVals[i] = int(k[lettersLeftToDo - i - 1]) - 96;//converts chars to numbers and stores them
		tempW += aConstVals[i]*aVals[i];//multiply each letter's val by their respective constants
	}
	wVals[currW] = tempW;

	long long int sum = 0;
	for(int i = 0; i < 5; i++)//adds all w values
	{
		sum = sum + rVals[i]*wVals[i];
	}
	return sum % size;
}

template <class T>
void Hashtable<T>::resize ()//hash values are changing everytime we resize -makes sense
{
	double loadFactor = (totalInserted)/size;
	if(loadFactor > 0.5)
	{ 
		int chooseSize[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
		for (int i = 0; i < 17; i++)
		{
			if(size < chooseSize[i])
			{
				size = chooseSize[i];
					//delete old thing
					//make new with new size
				delete[] TVals;
				delete[] kVals;
				TVals = new T [chooseSize[i]];
				kVals = new std::string [chooseSize[i]];
				break;
			}
		}
	}
	int tempTotalInserted = int(totalInserted);
	totalInserted = 0.0;

	for(int i = 0; i < size; i++)
	{
		kVals[i] = "";//resize all kVals to empty string
	}
	//rehash everything
	for (int i = 0; i < tempTotalInserted; i++)
	{
		add(orderAdded.front(), orderAdded2.front());
		orderAdded.pop();
		orderAdded2.pop();
	}
}

template <class T>
const T& Hashtable<T>::lookup (std::string k)
{
	long long int hashed = hash(k);//find the hash value
	int spot = hashed;
	int quadfactor = 1;
	for (int i = 0; i < size; i++)
	{
		if(kVals[spot] == k)
		{
			//object found
			return TVals[spot];
			break;

		}
		spot = (hashed + quadfactor*quadfactor) % size;//find next spot
		quadfactor++;
	}
	return garbageVal;//object not found - return garbage value

}

template <class T>
void Hashtable<T>::reportAll (std::ostream & out) const
{
	std::queue<std::string> gaypeopleRock = orderAdded;
	std::queue<T> gaypeopleRockHard = orderAdded2;
	//display everything in the order it was added
	for (int i = 0; i < totalInserted; i++)
	{
		out << gaypeopleRock.front() << " " << gaypeopleRockHard.front() << std::endl;
		gaypeopleRock.pop();
		gaypeopleRockHard.pop();
	}

}