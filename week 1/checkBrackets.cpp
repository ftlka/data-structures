/*
    If brackets are placed correctly, output “Success".
    Otherwise, output the 1-based index of the first unmatched
    closing bracket, and if there are no unmatched closing
    brackets, output the 1-based index of the first unmatched
    opening bracket.
    Input can contain other symbols. For example foo(bar[i]);
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool checkStackTop(const stack<char>& bracketStack, char bracket) {
    if (bracketStack.empty()) {
        return false;
    }

    if (bracket == ')') {
        return bracketStack.top() == '(';
    } else if (bracket == '}') {
        return bracketStack.top() == '{';
    } else {
        return bracketStack.top() == '[';
    }
}

void bracketIndex(string text) {
    stack<char> bracketStack;
    int idx;
    for (int pos = 0; pos < text.size(); pos++) {
        char next = text[pos];

        if (next == '(' || next == '[' || next == '{') {
            idx = pos;
            bracketStack.push(next);
        } else if (next == ')' || next == ']' || next == '}') {
            idx--;
            if (checkStackTop(bracketStack, next)) {
                bracketStack.pop();
            } else {
                cout << pos + 1 << endl;
                return;
            }
        }
    }

    if (bracketStack.empty()) {
        cout << "Success" << endl;
    } else {
        cout << idx + 1 << endl;
    }
}

int main() {
    string text;
    getline(cin, text);
    bracketIndex(text);

    return 0;
}
