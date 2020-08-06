// BinaryTreeSerialization.cpp : Defines the entry point for the application.
//

#include "header.h"
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));

    int tree_size = rand() % 20 + 5;
    const char* path = "tree";

    BinaryTree tree;

    for (int i = 0; i < tree_size; ++i)
    {
        auto tmp = rand() % 20;
        tree.insert(tmp);
        printf("Added: %d\n", tmp);
    }

    cout << endl << tree << endl;

    BinaryTree::write(tree, path);

    BinaryTree new_tree;
    BinaryTree::read(new_tree, path);

    cout << "Recovered tree:\n" << new_tree << endl;

    system("pause");
    return 0;
}
