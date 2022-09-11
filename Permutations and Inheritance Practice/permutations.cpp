#include <iostream>
using namespace std;

//prototypes
void permutations(string in);
void combos(string *wordStorage, int wordLength, int storageNum);
void swapChar(string &in, int a, int b);


int main () {
    string in = "enyamitc";
    permutations(in);




return 0;
}


void permutations(string in) {
    int wordLength = in.length();
    if ((wordLength == 1) || (wordLength == 0)) {
         cout << in << endl;
         return;
    }
    int nFact = 1;
    int storageNum = 0;//tracks #of Strings in wordStorage
    for(int i = 0; i < wordLength-1; i++){//iterates n-1 times to account for Factorial starting at 1
        nFact *= (nFact + 1); 
    }
    string* wordStorage = new string[nFact];//delete memory in future
    wordStorage[0] = in;//make base case here so that 2 letter words are automatically outputted
    wordStorage[1] = in;
    swapChar(wordStorage[1], 0, 1);
    if (wordLength == 2)
    {
        for (int i = 0; i < storageNum; i++){
            cout << wordStorage[i] << endl;
        }
    }
    storageNum++;
    storageNum++;

    combos(wordStorage, wordLength, storageNum);
    
    delete[] wordStorage;

}

void combos(string *wordStorage, int wordLength, int storageNum){
    int fact = 1;
    for (int i = 2; i < wordLength; i++)//starts at 1 b/c base case is finished
    {
        int inventory = storageNum - 1;
        int k = 0;
        for(int createNew=(storageNum*(i+1)-storageNum); createNew > 0; createNew--){
                //make arrays to be edited this time
                
                wordStorage[storageNum] = wordStorage[k];
                k++;
                if(k > inventory){k = 0;}//duplicates the small shii
                storageNum++;
        }

        fact *= i;
        int j = inventory + 1;
        for (int k = 0; k < i; k++){
            for (int p = 0; p < fact;p++){
                swapChar(wordStorage[j], k, i);
                j++;
            }
        }

    }
    for (int i = 0; i < storageNum; i++){
        cout << wordStorage[i] << endl;
    }
}


void swapChar(string &in, int a, int b) {
    char temp = in[a];
    in[a] = in[b];
    in[b] = temp;
    
}