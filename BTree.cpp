#include "BTree.h"

// ---------------- BTreeNode implementation ----------------

BTreeNode::BTreeNode(int t, bool leaf) : leaf(leaf), t(t) {
    keys.reserve(2 * t - 1);
    children.reserve(2 * t);
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < (int)keys.size(); i++) {
        if (!leaf && i < (int)children.size()) {
            children[i]->traverse();
        }
        std::cout << keys[i] << " ";
    }
    if (!leaf && i < (int)children.size()) {
        children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < (int)keys.size() && k > keys[i]) {
        i++;
    }

    if (i < (int)keys.size() && keys[i] == k) {
        return this;
    }

    if (leaf) {
        return nullptr;
    }

    return children[i]->search(k);
}

void BTreeNode::insertNonFull(int k) {
    int i = (int)keys.size() - 1;

    if (leaf) {
        keys.push_back(0); // temporary
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        i++;

        if ((int)children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);

            if (keys[i] < k) {
                i++;
            }
        }
        children[i]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);

    // Move last t-1 keys from y to z
    for (int j = 0; j < t - 1; j++) {
        z->keys.push_back(y->keys[j + t]);
    }

    // If not leaf, move last t children
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
    }

    // Resize y
    y->keys.resize(t - 1);
    if (!y->leaf) {
        y->children.resize(t);
    }

    // Insert new child z into children
    children.insert(children.begin() + i + 1, z);

    // Move middle key of y up into this node
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// ---------------- BTree implementation ----------------

BTree::BTree(int t) : root(nullptr), t(t) {}

void BTree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
    std::cout << std::endl;
}

BTreeNode* BTree::search(int k) {
    return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
        return;
    }

    if ((int)root->keys.size() == 2 * t - 1) {
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(root);
        s->splitChild(0, root);

        int i = 0;
        if (s->keys[0] < k) {
            i++;
        }
        s->children[i]->insertNonFull(k);

        root = s;
    } else {
        root->insertNonFull(k);
    }
}
