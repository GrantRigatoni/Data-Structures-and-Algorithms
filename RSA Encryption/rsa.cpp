#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void encrypt(string filename, long int n, string message);
long int expModNew(long int M, string e, long int n);     // M^e mod n
long int gcd(long int a, long int b);                     // finds gcd between 2 numbers
long int extendedEA(long int a, long int b, long int L);  // runs extended

int main(int argc, char* argv[]) {
    if (argc != 3) {
        throw logic_error("Not correct line arguments");
    }
    long int p = stol(argv[1]);  // stores p and q value for encryption
    long int q = stol(argv[2]);
    string input;//collects user input
    cin >> input;
    long int e = 65537;
    while (input != "EMPTY") {
        if (input == "ENCRYPT") {
            // calls various functions to encrypt and output to file
            long int n;
            string filename, message;//collects user input
            cin >> filename >> n;
            cin.ignore(1, ' ');
            getline(cin, message);
            encrypt(filename, n, message);

        } else if (input == "DECRYPT") {
            // This will DECRYPT our messages
            string input, output;
            cin >> input >> output;
            ifstream ifile(input);
            ofstream ofile(output);
            //calculate L 
            int GCD = gcd((p - 1), (q - 1));
            long int L = (p - 1) * (q - 1) / GCD;
            if (L <= e) {
                throw logic_error("L <= e");
            }
            if (gcd(e, L) != 1) {
                throw logic_error("bad p and q choice");
            }
            // mod the message by d to decryp using mosular exponentiation
            long int d = extendedEA(p - 1, q - 1, L);
            if (d < 0)  // corrects d if it is negative
            {
                d += (p - 1) * (q - 1);
            }
            long int n = p * q;
            long int C;
            long int tempD = d;
            string binaryOfD = "";  // stors the binary of D
            while (tempD > 0)       // stores binary of e in stack backwards
            {
                if (tempD % 2 == 1) {
                    binaryOfD += "1";
                } else {
                    binaryOfD += "0";
                }
                tempD /= 2;
            }
            while (ifile >> C)  // reads in and handles all encrypted numbers
            {
                string notM = "";
                long int M = expModNew(C, binaryOfD, n);
                int onesPlace, tensPlace, letter;
                long int x = 1 + (log(n / 27) / log(100));
                for (int i = 0; i < x; i++)  // translates all letters to words
                {
                    onesPlace = M % 10;
                    M /= 10;
                    tensPlace = (M % 10) * 10;
                    M /= 10;
                    letter = onesPlace + tensPlace + 96;//calculates letter's ASCII value
                    if (onesPlace == 0 && tensPlace == 0) {
                        notM += " ";
                    } else {
                        notM += char(letter);//casts and stores letter
                    }
                }
                long int size = notM.size();
                for (long int i = 0; i < notM.size(); i++)  // reverses string M
                {
                    ofile << notM[size - 1 - i];
                }
            }

        } else if (input == "EXIT") {//ends the program
            return 0;
        }

        cin >> input;
    }

    return 0;
}

void encrypt(string filename, long int n, string message) {
    int e = 65537;
    string binaryOfE = "10000000000000001";
    long int messageSize = message.size();
    long int howMuchWhiteSpace = 0;  // will help with whitespace later
    ofstream ofile(filename);
    if (n < 27) {
        throw logic_error("primes too small");//throws error b/c full range of letters can't be calculated
    }
    long int x = 1 + (log(n / 27) / log(100));  // 1 + (log100(n/27));//log_b(a) = log_2(a)/log_2(b)
    int j = 0;                                  // tracks
    for (; messageSize > 0; messageSize -= x) {
        string notM = "";     // used to store M as string
        if (messageSize < x)  // ensures we access actual data
        {
            howMuchWhiteSpace = x - messageSize;  // calculted when we need it at the end
        }
        for (int i = 0; i < (x - howMuchWhiteSpace); i++) {
            // read in first x letters of message and concatonate their associated values
            if (message[(j * x + i)] == ' ')  // j indicates the current iteration
            {
                notM += to_string(0);
                notM += to_string(0);
            } else {
                int currLetterVal = int(message[j * x + i]) - 96;  // assigns each lowercase letter its proper value
                notM += to_string(currLetterVal / 10);
                notM += to_string(currLetterVal % 10);
            }
        }
        for (long int i = 0; i < howMuchWhiteSpace; i++) {
            // add white space when x doesn't subtract evenly into the message size
            notM += "00";
        }

        long int M = stol(notM);

        // int C = pow(M,e) % n - do this using modular exponentiation Alogorithm
        long int C = expModNew(M, binaryOfE, n);

        if (howMuchWhiteSpace != 0)  // adds appropiate white space
        {
            ofile << C;
        } else {
            ofile << C << " ";
        }
        j++;  // increments up so we start at the j*xth element of the message
    }
}

long int expModNew(long int M, string e, long int n)  // M^e mod n
{

    long int lengthofbinary = e.size();
    long int x = 1;
    long int power = M % n;
    for (int i = 0; i < lengthofbinary; i++)  // iterates through the binary
    {
        if (e[i] == '1')  // multiplies mod when binary matches
        {
            x = (x * power) % n;
        }
        power = (power * power) % n;
    }
    return x;
}

long int gcd(long int a, long int b) {
    if (a < b) {
        long int temp = b;
        b = a;
        a = temp;
    }
    // stores the largest divided by the smallest
    long int r = 1;
    while (r != 0) {
        if (a % b == 0)  // we found gcf if this is true
        {
            return r;
        } else
            r = a % b;
        a = b;
        b = r;
    }
    return r;
}

long int extendedEA(long int a, long int b, long int L) {
    int t = 1;
    int oldt = 0;
    int r = 65537;
    int oldr = L;
    int quotient, temp;
    // stores the largest divided by the smallest
    while (r != 0) {
        quotient = oldr / r;
        temp = r;
        r = oldr - quotient * r;
        oldr = temp;
        temp = t;
        t = oldt - quotient * t;
        oldt = temp;
    }
    return oldt;  // oldt form the instructions b/c we broke
}