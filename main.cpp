// BinaryTreeSerialization.cpp : Defines the entry point for the application.
//

#include "header.h"
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));

    int tree_size = rand() % 20 + 5;

    BinaryTree tree;

    for (int i = 0; i < tree_size; ++i)
    {
        auto tmp = rand() % 20;
        tree.insert(tmp);
        printf("Added: %d\n", tmp);
    }

    cout << endl << tree << endl;

    const auto tmp = tree.serialize();

    for (int i = 0; i < tree_size + 1; ++i)
        cout << tmp[i] << ' ';
    cout << endl;

    tree.deserialize(tmp.get(), tree_size + 1);

    cout << "Deserialized tree:\n" << tree << endl;

    system("pause");
    return 0;
}
