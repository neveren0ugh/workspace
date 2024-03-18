#include "BPlusTree.h"

int main() {
    BPlusTree* root = new BPlusTree(1);
    BPlusTree* child1 = new BPlusTree(2);
    BPlusTree* child2 = new BPlusTree(3);
    BPlusTree* child3 = new BPlusTree(4);
    BPlusTree* child4 = new BPlusTree(5);
    BPlusTree* child5 = new BPlusTree(6);

    root->add_child(child1);
    root->add_child(child2);
    child2->add_child(child4);
    root->print();
    delete root;
    delete child3;
    delete child4;
    delete child5;
    return 0;
}
