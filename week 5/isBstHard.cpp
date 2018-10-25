/*
    In this problem you are going to solve the same problem as the previous one, but for a more general case,
	when binary search tree may contain equal keys.
	Smaller elements are to the left, bigger elements
	are to the right, and duplicates are always to the right.
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool is_bst(int idx, long long min, long long max, const vector<Node>& tree) {
	if (tree[idx].key >= max || tree[idx].key < min) {
		return false;
	}

	if (tree[idx].left != -1 &&
		!is_bst(tree[idx].left, min, tree[idx].key, tree)) {
		return false;
	}

	if (tree[idx].right != -1 &&
		!is_bst(tree[idx].right, tree[idx].key,
			max, tree)) {
		return false;
	}

	return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    if (tree.size() == 0) {
        return true;
    }

    return is_bst(0, LONG_MIN, LONG_MAX, tree);
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
