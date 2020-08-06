#include "btree.h"

BinaryTree::BinaryTree(int* values, size_t n)
{
    this->root = new Node(values[1]);
    for (size_t i = 2; i < n; ++i)
        insert(values[i]);
}

struct BinaryTree::Node* BinaryTree::search(struct Node* local_root, int value) const noexcept
{
    if (local_root == nullptr || local_root->value == value)
        return local_root;
    if (root->value < value)
        return search(local_root->right, value);
    return search(local_root->left, value);
}

struct BinaryTree::Node* BinaryTree::add(struct Node* local_root, int value)
{
    if (!local_root)
        return new Node(value);

    if (value > local_root->value)
        local_root->right = add(local_root->right, value);
    else
        local_root->left = add(local_root->left, value);

    return local_root;
}

void BinaryTree::delete_branch(struct Node* local_root) noexcept
{
    if (!local_root)
        return;
    delete_branch(local_root->left);
    delete_branch(local_root->right);
    delete local_root;
    --this->size;
}

struct BinaryTree::Node* BinaryTree::insert(int value)
{
    this->root = add(root, value);
    ++this->size;
    return search(this->root, value);
}

struct BinaryTree::Node* BinaryTree::find(int value) const noexcept
{
    return search(this->root, value);
}


void BinaryTree::print_branch(std::ostream& os, struct Node* local_root, size_t offset) noexcept
{
    if (!local_root)
        return;
    for (int i = 0; i < offset; ++i) os << ' ';
    //--offset;
    os << local_root->value << '\n';
    print_branch(os, local_root->left, offset - 1);
    print_branch(os, local_root->right, ++offset + 1);
}

BinaryTree::~BinaryTree() noexcept
{
    delete_branch(this->root);
}

void BinaryTree::inorder_serial(struct Node* local_root, std::unique_ptr<int[]>& buffer, size_t& pos) const noexcept
{
    if (!local_root)
        return;
    buffer[pos++] = local_root->value;
    inorder_serial(local_root->left, buffer, pos);
    inorder_serial(local_root->right, buffer, pos);
}

std::unique_ptr<int[]> BinaryTree::serialize() const
{
    auto bytes = std::make_unique<int[]>(this->size + 1);
    bytes[0] = this->size;

    size_t size = 1;
    inorder_serial(this->root, bytes, size);

    return bytes;
}

void BinaryTree::deserialize(int* input, size_t n)
{
    if (n < 2)
        throw std::exception("Not enough values for deserealization.");
    if (input[0] != n - 1)
        throw std::exception("Too little values.");

    delete_branch(this->root);
    this->root = new Node(input[1]);
    for (size_t i = 2; i < n; ++i)
        insert(input[i]);
}

void BinaryTree::write(const BinaryTree& tree, const char* path)
{
    std::ofstream file;
    file.open(path, std::ios::binary);
    if (!file.is_open())
        throw std::exception("Failed to open the file.");
    
    // Writing data to file.

    const auto data = tree.serialize();
    for (size_t i = 0; i < tree.size + 1; ++i)
        file.write((char*)&data[i], sizeof(int));
    file.close();
}

void BinaryTree::read(BinaryTree& tree, const char* path)
{
    std::ifstream file;
    file.open(path, std::ios::binary);
    if (!file.is_open())
        throw std::exception("Failed to open the file.");

    // Recovering data from the file.

    size_t size = 0;
    file.read((char*)&size, sizeof(int));

    auto data = std::make_unique<int[]>(size);
    file.read((char*)data.get(), sizeof(int) * size);
    file.close();

    // Creating the tree with this data.

    for (size_t i = 0; i < size; ++i)
        tree.insert(data[i]);
}