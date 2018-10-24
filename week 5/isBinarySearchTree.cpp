/*
    You are given a binary tree with integers as its keys.
    You need to test whether it is a correct binary
    search tree.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_helper(int idx, vector<int>& res, const vector<Node>& tree) {
        if (tree[idx].left != -1) {
            in_order_helper(tree[idx].left, res, tree);
        }

        res.push_back(tree[idx].key);

        if (tree[idx].right != -1) {
            in_order_helper(tree[idx].right, res, tree);
        }
    }

bool is_sorted(vector<int>& arr) {
    if (arr.size() < 2) {
        return true;
    }

    int prev = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (prev > arr[i]) {
            return false;
        }
        prev = arr[i];
    }

    return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    if (tree.size() == 0) {
        return true;
    }
    vector<int> res;
    in_order_helper(0, res, tree);

    return is_sorted(res);
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; i++) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }

    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
