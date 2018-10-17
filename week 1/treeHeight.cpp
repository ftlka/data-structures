/*
    Given a description of a rooted tree compute and output its height.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node* theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int getMaxHeight(Node* currentNode, int maxH) {
    if (currentNode == NULL) {
        return 0;
    }
    maxH++;
    int oldMax = maxH;

    for (auto child : currentNode->children) {
        int currentChildMax = getMaxHeight(child, oldMax);
        maxH = max(maxH, currentChildMax);
    }
    
    return maxH;
}


int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;

    vector<Node> nodes(n);
    Node* root;
    int rootIdx;
    for (int i = 0; i < n; i++) {
        int parent_index;
        cin >> parent_index;
        nodes[i].key = i;
        if (parent_index >= 0) {
            nodes[i].setParent(&nodes[parent_index]);            
        } else {
            rootIdx = i;
        }
    }

    for (Node *v = &nodes[rootIdx]; v != NULL; v = v->parent) {
        if (v->parent == NULL) {
            root = v;
        }
    }
    
    cout << getMaxHeight(root, 0) << endl;
    return 0;
}

int main (int argc, char **argv) {
    
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
      if (rl.rlim_cur < kStackSize) {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0) {
              cerr << "setrlimit returned result = " << result << endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
