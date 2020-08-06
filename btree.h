#pragma once
#include <iostream>
#include <fstream>

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

    struct Node* search(struct Node* local_root, int value) const noexcept;
    struct Node* add(struct Node* local_root, int value);

    void delete_branch(struct Node* local_root) noexcept;
    void inorder_serial(struct Node* local_root, std::unique_ptr<int[]>&, size_t& pos) const noexcept;

public:

    BinaryTree() : root(nullptr) {}
    BinaryTree(int value) : root(new Node(value)), size(1) {}
    BinaryTree(int* values, size_t n);
    ~BinaryTree() noexcept;

    struct Node* insert(int value = {});
    struct Node* find(int value) const noexcept;
    static void print_branch(std::ostream& os, struct Node* local_root, size_t offset) noexcept;

    friend std::ostream& operator<<(std::ostream& os, BinaryTree& tree)
    {
        print_branch(os, tree.root, tree.size);
        return os;
    }

    size_t get_size() const noexcept { return size; }

    std::unique_ptr<int[]> serialize() const;
    void deserialize(int* input, size_t n);

    static void write(const BinaryTree& tree, const char* path);
    static void read(BinaryTree& tree, const char* path);
};