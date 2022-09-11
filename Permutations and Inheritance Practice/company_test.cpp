#include <iostream>
#include "company.hpp"
using namespace std;

int main () {
    CompanyTracker CompanyTest(5);
    CompanyTest.split(0);//split doesn't do anything to a base company
    CompanyTest.merge(0, 1);
    if (CompanyTest.inSameCompany(0, 1))//merging everything together and test till line 42
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
    CompanyTest.merge(2, 3);
        if (CompanyTest.inSameCompany(2, 3))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
    CompanyTest.merge(3, 4);
        if (CompanyTest.inSameCompany(3, 4))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
    CompanyTest.merge(4, 0);
        if (CompanyTest.inSameCompany(4, 0))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
    if (CompanyTest.inSameCompany(0, 2))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;

        if (CompanyTest.inSameCompany(1, 2))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;

        if (CompanyTest.inSameCompany(3, 1))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
    CompanyTest.split(0);//splits every company down and tests till line 75
    CompanyTest.split(1);
    CompanyTest.split(2);
    CompanyTest.split(3);
    CompanyTest.merge(1, 1);//merging the same company shouldn't make any new companies
    CompanyTest.merge(2, 2);

    if (!(CompanyTest.inSameCompany(0, 1)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
        if (!(CompanyTest.inSameCompany(2, 3)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
        if (!(CompanyTest.inSameCompany(3, 4)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
        if (!(CompanyTest.inSameCompany(4, 0)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
    if (!(CompanyTest.inSameCompany(0, 2)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;

        if (!(CompanyTest.inSameCompany(1, 2)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;

        if (!(CompanyTest.inSameCompany(3, 1)))
    {
        cout << "good" << endl;
    }else cout << "bad" << endl;
//testing out of range to make sure it doesn't seg fault
CompanyTest.merge(-1, 3);
CompanyTest.merge(3, -1);
CompanyTest.split(-1);
CompanyTest.inSameCompany(-1, 3);
CompanyTest.inSameCompany(3, -1);
    return 0;
}