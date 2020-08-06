# CMakeList.txt : CMake project for BinaryTreeSerialization, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BinaryTreeSerialization")

# Add source to this project's executable.
add_executable (BinaryTreeSerialization "main.cpp" "header.h" "btree.h" "btree.cpp")

# TODO: Add tests and install targets if needed.
