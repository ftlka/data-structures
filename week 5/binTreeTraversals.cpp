/*
    Implementation of in-order, pre-order and post-order
    traversals of a binary tree.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
    int n;
    vector<int> key;
    vector<int> left;
    vector<int> right;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    void in_order_helper(int idx, vector<int>& res) {
        if (left[idx] != -1) {
            in_order_helper(left[idx], res);
        }
        res.push_back(key[idx]);

        if (right[idx] != -1) {
            in_order_helper(right[idx], res);
        }
    }

    void pre_order_helper(int idx, vector<int>& res) {
        res.push_back(key[idx]);

        if (left[idx] != -1) {
            pre_order_helper(left[idx], res);
        }

        if (right[idx] != -1) {
            pre_order_helper(right[idx], res);
        }
    }

    void post_order_helper(int idx, vector<int>& res) {
        if (left[idx] != -1) {
            post_order_helper(left[idx], res);
        }

        if (right[idx] != -1) {
            post_order_helper(right[idx], res);
        }

        res.push_back(key[idx]);
    }

    vector<int> in_order() {
        vector<int> result;
        in_order_helper(0, result);
        return result;
    }


    vector<int> pre_order() {
        vector<int> result;    
        pre_order_helper(0, result);
        return result;
    }

    vector<int> post_order() {
        vector<int> result;
        post_order_helper(0, result);
        return result;
    }
};

void print(const vector<int>& a) {
    for (int i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << endl;
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

