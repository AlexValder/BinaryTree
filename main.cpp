// BinaryTreeSerialization.cpp : Defines the entry point for the application.
//

#include "header.h"
#include <ctime>
using namespace std;

int main()
{
    //srand(time(0));

    BinaryTree tree;

    for (int i = 0; i < 10; ++i)
    {
        auto tmp = rand() % 20;
        tree.insert(tmp);
        printf("Added: %d\n", tmp);
    }

    cout << endl << tree << endl;

    const auto tmp = tree.serialize();

    for (int i = 0; i < 11; ++i)
        cout << tmp[i] << ' ';
    cout << endl;

    BinaryTree deser_tree = BinaryTree(tmp.get(), tree.get_size() + 1);

    cout << "Deserialized tree:\n" << deser_tree << endl;

    system("pause");
    return 0;
}
