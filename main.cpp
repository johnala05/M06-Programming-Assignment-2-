#include <iostream>
#include "BTree.h"

int main() {
    int t = 3; // minimum degree
    BTree tree(t);

    std::cout << "Inserting: 10 20 5 6 12 30 7 17\n";
    int values1[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int v : values1) {
        tree.insert(v);
    }
    std::cout << "B-Tree traversal after first sequence:\n";
    tree.traverse();

    std::cout << "Inserting: 1 2 3 4 8 9\n";
    int values2[] = {1, 2, 3, 4, 8, 9};
    for (int v : values2) {
        tree.insert(v);
    }
    std::cout << "B-Tree traversal after second sequence:\n";
    tree.traverse();

    int key = 12;
    std::cout << "Searching for key " << key << "...\n";
    auto result = tree.search(key);
    if (result) {
        std::cout << "Key " << key << " found in B-Tree.\n";
    } else {
        std::cout << "Key " << key << " not found in B-Tree.\n";
    }

    return 0;
}
