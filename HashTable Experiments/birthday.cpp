#include "Hashtable.h"


int main()
{
    int count = 0;
    double countLessThanOrEqual23 = 0;
    double countMoreThan23 = 0;
    int probe = 0;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 10000; i++)
    {
        Hashtable<int> birthday(false, 365);
        probe = 0;
        count = 0;
        while(probe == 0)
        {
            //make random string
            std::string randString = "";
            for(int j = 0; j < 10; j++)
            {
                int letter = rand() % 26;
                randString += alphabet[letter];
            }
                count++;
                probe = birthday.add(randString, i);
        }
        if (count <= 23)
        {
            countLessThanOrEqual23++;
        }

    }
    std::cout << "Probes Collide <= 23 "<< countLessThanOrEqual23/100 << "% of the time." << std::endl;

    return 0;


}