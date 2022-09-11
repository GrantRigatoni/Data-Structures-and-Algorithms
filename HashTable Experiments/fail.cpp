#include "Hashtable.h"


int main ()
{
    int count = 0;
    int probe = 0;
    char alphabet [26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        while(true)
        {
            Hashtable<int> birthday(true, 12);
            for(int i = 0; i < 7; i++)
            {
            //make random string
            std::string randString = "";
            for(int j = 0; j < 3; j++)
            {
                int letter = rand() % 26;
                randString += alphabet[letter];
            }
            std::cout << randString << std::endl;
                birthday.add(randString, i);
            }
            std::cout<< "GOOD" << std::endl;
        }


    return 0;
}

//Fails with strings nwl, rbb, mqb, hcd, arz, owk

//THIS CODE WILL HIT A LOGIC ERROR

// int main()
// {
//     Hashtable<int> agesOfEveryone(true, 12);
//     string me = "grant";
//     agesOfEveryone.add("nwl", 12);
//     agesOfEveryone.add("rbb", 12);
//     agesOfEveryone.add("mqb", 12);
//     agesOfEveryone.add("hcd", 12);
//     agesOfEveryone.add("arz", 12);
//     agesOfEveryone.add("owk", 12);

//     std::cout << "we don't make it here :(" << std::endl;
//     return 0;

// }