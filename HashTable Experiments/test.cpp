#include "Hashtable.h"

using namespace std;

int main()
{
    Hashtable<int> agesOfEveryone(true, 12);
    string me = "grant";
    agesOfEveryone.add("nwl", 12);
    agesOfEveryone.add("rbb", 12);
    agesOfEveryone.add("mqb", 12);
    agesOfEveryone.add("hcd", 12);
    agesOfEveryone.add("arz", 12);
    agesOfEveryone.add("owk", 12);

    std::cout << "we don't make it :(" << std::endl;
    return 0;

}

