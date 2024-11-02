#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    int x;
    Tree<int> t;

    cin >> x;

    while (x != -1)
    {
        t.insert(x);
        cin >> x;
    }

    cin >> x;

    while (x != -1)
    {
        cout << t.member(x) << endl;
        cin >> x;
    }
}
