/*
	Implement a stack supporting the operations Push(), Pop()
	and Max()
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;
// сделать указатель на элемент с максимумом, если он
// попнулся, то жизнь тлен походу, если добавился, то меняем
// на него


class StackWithMax {
    vector<int> stack;
    vector<int> maxes;

  public:

    void Push(int value) {
        stack.push_back(value);
        if (!maxes.size() || maxes[maxes.size() - 1] <= value) {
        	maxes.push_back(value);
        }
    }

    void Pop() {
        assert(stack.size());
        int elemToBePopped = stack[stack.size() - 1];
        stack.pop_back();
        if (maxes[maxes.size() - 1] == elemToBePopped) {
        	maxes.pop_back();
        }
    }

    int Max() const {
        assert(stack.size());
        return maxes[maxes.size() - 1];
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << endl;
        }
        else {
            assert(0);
        }
    }
    return 0;
}