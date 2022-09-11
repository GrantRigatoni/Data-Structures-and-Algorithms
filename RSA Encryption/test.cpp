#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

int main()
{
    long int a;
    long int b;
    cin >> a >> b;
if (a < b)
    {
        long int temp = b;
        b = a;
        a = temp;
    }
    //stores the largest divided by the smallest
    long int r = 1;
    while (r != 0)
    {
        cout << r << endl;
        if(a % b == 0)//we found gcf if this is true
        {
            cout << "The answer is " << r << endl;
            return 0;
        }else r = a % b;
        a = b;
        b = r;
    }
    cout << "The answer is " << r << endl;
    return 0;

}