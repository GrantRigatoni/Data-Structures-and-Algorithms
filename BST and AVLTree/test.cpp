#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include "bst.h"
#include "avlbst.h"

int main ()
{
    AVLTree<int, double> work;
    std::pair<int, double> foo;
    foo = std::make_pair(24, 10);
    work.insert(foo);
    work.print();
    std::pair<int, double> foo1;
    foo1 = std::make_pair(24, 9.5);
    work.insert(foo1);
    work.print();
    foo1 = std::make_pair(50, 9.89);
    work.insert(foo1);
    work.print();
    
    std::pair<int, double> foo2;
    foo2 = std::make_pair(55, 20.5);
    work.insert(foo2);
    work.print();
    std::pair<int, double> foo3;
    foo3 = std::make_pair(32, 0.5);
    work.insert(foo3);
    work.print();
    std::pair<int, double> foo4;
    foo4 = std::make_pair(145, 290.5);
    work.insert(foo4);
    work.print();
    std::pair<int, double> foo5;
    foo5 = std::make_pair(775, 29.5);
    work.insert(foo5);
    work.print();
    
    //here we fuck up in right
    // //work.print();
    
    // std::cout << "HERE" << std::endl;
    //work.remove(12);
    //work.remove(2);
    //work.print();
    // std::pair<int, double> doo;
    // doo = std::make_pair(40, 10);
    // work.insert(doo);
    //work.print();
    std::pair<int, double> doo1;
    doo1 = std::make_pair(30, 9.5);
    work.insert(doo1);
    work.print();
    //work.remove(25);
    //work.print();
     std::pair<int, double> doo2;
     doo2 = std::make_pair(351, 20.5);
     work.insert(doo2);
     work.print();
    std::pair<int, double> doo3;
     doo3 = std::make_pair(269, 0.5);
     work.insert(doo3);
     work.print();
    std::pair<int, double> doo4;
     doo4 = std::make_pair(354, 290.5);
     work.insert(doo4);
     work.print();
    std::pair<int, double> doo5;
    doo5 = std::make_pair(518, 29.5);
    work.insert(doo5);
    work.print();
    std::pair<int, double> doo6;
    doo6 = std::make_pair(828, 29.5);//no no no left right
    work.insert(doo6);
    work.print();

    std::pair<int, double> goo;
    goo = std::make_pair(296, 10);
    work.insert(goo);
    work.print();
    std::pair<int, double> goo1;
    goo1 = std::make_pair(339, 9.5);
    work.insert(goo1);
    work.print();


    std::cout << "removes" << std::endl;
    work.remove(50);
    work.print();
    work.remove(828);
    work.print();
    work.remove(50);
    work.print();
    work.remove(269);
    work.print();
    work.remove(30);
    work.print();
    work.remove(45);
    work.print();
    work.remove(40);//break here
    work.print();
    work.remove(828);
    work.print();
    work.remove(775);
    work.print();
    work.remove(354);
    work.print();
    if(work.isBalanced())
    {
        std::cout<< "is balanced" << std::endl;
    }else std::cout<< "not balanced" << std::endl;

    return 0;
}