#include <iostream>
#include <vector>
#include <algorithm>

class BPlusTree {
private:
    int max_size;
    int data;
    BPlusTree* first_child;
    std::vector<BPlusTree*> next_children{nullptr};

public:
    BPlusTree();
    BPlusTree(int val);
    ~BPlusTree();
    int get_children_amount();
    void add_child(BPlusTree* child);
    void remove_child(BPlusTree* child);
    void print();
    void printHelper(BPlusTree* node, int depth);
    BPlusTree* search(int val);
};

