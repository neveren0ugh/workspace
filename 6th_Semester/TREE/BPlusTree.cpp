#include "BPlusTree.h"

BPlusTree::BPlusTree() : data(0), first_child(nullptr) {};

BPlusTree::BPlusTree(int val) : data(val), first_child(nullptr) {};

BPlusTree::~BPlusTree() {
    delete first_child;
    //delete[] &next_children;
};

int BPlusTree::get_children_amount() {
    if (!first_child) // no children
        return 0;
    if (!next_children[0]) // next_children array is empty
        return next_children.size();
    else // next_children non-empty
        return next_children.size() + 1;
};

void BPlusTree::add_child(BPlusTree* child) {
    if (!first_child) {
        first_child = child;
    }
    else {
        BPlusTree* current_child = first_child;
        for (size_t i = 0; i < next_children.size(); i++) {
            if (current_child == child) {
                std::cerr << "Child you want to append already exists " << std::endl;
                return;
            }
            current_child = next_children[i];
        }

        next_children.push_back(child);
        if (!next_children[0]) {
            next_children.erase(next_children.begin(), next_children.begin() + 1);
        }
    }
};

void BPlusTree::remove_child(BPlusTree* child) {
    if (!first_child) {
        std::cerr << "There is no such child in the tree" << std::endl;
        return;
    }
    if (first_child == child) {
        first_child = next_children[0];
        delete& (*next_children[0]);
        next_children.erase(next_children.begin());
        return;
    }
    if (std::find(next_children.begin(), next_children.end(), child) != next_children.end()) // check whether there are children in the tree or not
        next_children.erase(std::find(next_children.begin(), next_children.end(), child));
    else        
        std::cerr << "Child you are trying to delete doesn't exist" << std::endl;
};


void BPlusTree::print() {
    printHelper(this, 0);
};


void BPlusTree::printHelper(BPlusTree* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << node->data << std::endl;

    printHelper(node->first_child, depth + 1);
    for (size_t i = 0; i < next_children.size(); i++) {
        printHelper(node->next_children[i], depth);
    }
};
