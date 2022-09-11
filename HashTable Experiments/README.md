HashTable Experiments

Compilation and Run Instructions

    1.open a file containing all files associated with the program (Hashtable.h, birthday.cpp, fail.cpp)
    2.Run docker or some other linex environment
    3.compile and run code by typing "make"
    4.Run the program with ./*executable*
    5.Make sure to not pre-compile the templated header file

Tests:

Located in birthday.cpp, this program proves the Birthday Paradox. It creates a %value very close to (and sometimes exactly equal to) the expected 50.7% of collisions happening less than or equal to 23 entries in the hashtable.

Located in fail.cpp, this program will eventually run indefinetly - showing why it is imperative to have a hash table of a prime size.  The program failed with the strings: Fails with strings nwl, rbb, mqb, hcd, arz, owk

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

   