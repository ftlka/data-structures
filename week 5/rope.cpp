#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

// Vertex of a splay tree
struct Vertex {
  char key;
  long long size;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, long long size, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), size(size), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->size = 1;
  if (v->left != NULL) {
    v->size += v->left->size;
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->size += v->right->size;
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex* root, int x) {
  Vertex* v = root;
  while (v != NULL) {
	  long long s = (v->left != NULL) ? v->left->size : 0;
	  if (x == (s + 1)) {
			break;
		} else if (x < (s + 1)) {
			v = v->left;
		} else if (x > (s + 1)) {
			v = v->right;
			x = x - s - 1;
		}
	}
  splay(root, v);
  return v;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
  right = find(root, key);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

void print_vertex(Vertex* v) {
  cout << endl;
  cout << v->key << " ";
  if (v->left != NULL) {
    cout << ", left: " << v->left->key;
  }
  if (v->right != NULL) {
    cout << ", right: " << v->right->key;
  }
  cout << endl;
}

void print_tree(Vertex*& current) {
  if (current == NULL) {
    return;
  }
  if (current->left != NULL) {
    print_tree(current->left);
  }
  cout << current->key;
  if (current->right != NULL) {
    print_tree(current->right);
  }
}

void insert(Vertex*& root, int x) {
  // insert and then splay
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = NULL;  
  split(root, x, left, right);
  if (right == NULL || right->key != x) {
    new_vertex = new Vertex(x, x, NULL, NULL, NULL);
  }
  root = merge(merge(left, new_vertex), right);
}

class Rope {
	Vertex* root = NULL;
	string str;
public:
	Rope(const string& s) {
		str = s;
		root = new Vertex(s[0], 1, NULL, NULL, NULL);
		for (int i = 1; i < s.size(); i++) {
			Vertex* current = new Vertex(s[i], 1, NULL, NULL, NULL);
			root = merge(root, current);
		}
	}

	void process(int i, int j, int k) {
		Vertex* left = NULL;
		Vertex* right = NULL;
		Vertex* middle = NULL;

		split(root, i + 1, left, middle);
		split(middle, j - i + 2, middle, right);

		update(left);
		update(middle);
		update(right);
		root = merge(left, right);

		Vertex* l  = NULL;
		Vertex* m = NULL;
		split(root, k + 1, l, m);

		Vertex* begin = merge(l, middle);
		root = merge(begin, m);
		cout << endl;
	}

	void result() {
		cout << endl;
		print_tree(root);
		cout << endl;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	Rope rope(s);
	int actions;
	cin >> actions;
    for (int act_idx = 0; act_idx < actions; act_idx++) {
        int i, j, k;
		cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	rope.result();
	cout << endl;
}
