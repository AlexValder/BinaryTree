#pragma once
#include <iostream>

class BinaryTree
{
    struct Node
    {
        int value;
        struct Node* right = nullptr;
        struct Node* left = nullptr;

        Node(int value = {}) : value(value) {}
    };

    Node* root;
    size_t size = 0;

    struct Node* search(struct Node* local_root, int value) noexcept
    {
        if (local_root == nullptr || local_root->value == value)
            return local_root;
        if (root->value < value)
            return search(local_root->right, value);
        return search(local_root->left, value);
    }

    struct Node* add(struct Node* local_root, int value)
    {
        if (!local_root)
            return new Node(value);
        
        if (value > local_root->value)
            local_root->right = add(local_root->right, value);
        else
            local_root->left = add(local_root->left, value);

        return local_root;
    }

    void delete_branch(struct Node* local_root) noexcept
    {
        if (!local_root)
            return;
        delete_branch(local_root->left);
        delete_branch(local_root->right);
        delete local_root;
    }

public:

    BinaryTree() : root(nullptr) {}
    BinaryTree(int value) : root(new Node(value)), size(1) {}

    struct Node* insert(int value = {})
    {
        this->root = add(root, value);
        ++this->size;
        return search(this->root, value);
    }

    struct Node* find(int value) noexcept
    {
        return search(this->root, value);
    }


    static void print_branch(std::ostream& os, struct Node* local_root, int offset) noexcept
    {
        if (!local_root)
            return;
        for (int i = 0; i < offset; ++i) os << ' ';
        //--offset;
        os << local_root->value << '\n';
        print_branch(os, local_root->left, offset - 1);
        print_branch(os, local_root->right, ++offset + 1);
    }


    friend std::ostream& operator<<(std::ostream& os, BinaryTree& tree)
    {
        print_branch(os, tree.root, tree.size / 2);
        return os;
    }


    ~BinaryTree() noexcept
    {
        delete_branch(this->root);
    }
};