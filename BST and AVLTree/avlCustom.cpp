#include "avlbst.h"
#include <iostream>

using namespace std;

int main() {

    cout << endl << "Creating AVLTree<int, char>..." << endl << endl;
    AVLTree<int, char> tree;

    cout << "FORMAT: 'i' [key] [value] OR 'r' [key]" << endl;
    cout << "\t'n' for new tree" << endl;
    cout << "\t'e' to exit" << endl;

    char action;
    int key;
    char value;
    while (true) {

        cout << endl;
        cin >> action;

        // insert
        if (action == 'i') {
            cin >> key >> value;
            tree.insert(pair<int, char>(key, value));
        }
        else if (action == 'r') {
            cin >> key;
            tree.remove(key);
        }
        else if (action == 'n') {
            tree.clear();
        }
        else if (action == 'e') {
            return 0;
        }

        tree.print();
    }

    return 0;
}