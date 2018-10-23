/*
    Implement a simple phone book manager. It should be able
    to process the following types of user’s queries:
        - add number name
        - del number
        - find number
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; i++) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;
}

int get_hash(long long phone_number) {
    return ((31 * phone_number) % 10000019) % 1000;
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<vector<Query>> contacts(1000);
    for (int i = 0; i < queries.size(); i++) {
        int hash = get_hash(queries[i].number);

        if (queries[i].type == "add") {
            bool was_found = false;
            if (contacts[hash].size()) {
                for (int j = 0; j < contacts[hash].size(); j++) {
                    if (contacts[hash][j].number == queries[i].number) {
                        contacts[hash][j].name = queries[i].name;
                        was_found = true;
                        break;
                    }
                }
            }

            if (!was_found) {
                contacts[hash].push_back(queries[i]);
            }
        } else if (queries[i].type == "del") {
            if (contacts[hash].size()) {
                for (int j = 0; j < contacts[hash].size(); j++) {
                    if (contacts[hash][j].number == queries[i].number) {
                        contacts[hash].erase(contacts[hash].begin() + j);
                        break;
                    }
                }
            }
        } else {
            string response = "not found";
            if (contacts[hash].size()) {
                for (int j = 0; j < contacts[hash].size(); j++) {
                    if (contacts[hash][j].number == queries[i].number) {
                        response = contacts[hash][j].name;
                        break;
                    }
                }
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
