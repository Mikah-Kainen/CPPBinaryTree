// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include "Node.cpp"
#include "Tree.cpp"

int main()
{
    std::function<int(int, int)> compFunc = [](int left, int right) -> int
    {
        if (left > right)
        {
            return 1;
        }
        else if (left == right)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    };

    Tree<int> myTree = Tree<int>(compFunc);

    myTree.Add(5);
    myTree.Add(3);
    myTree.Add(4);
    myTree.Add(5);
    myTree.Remove(5);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
