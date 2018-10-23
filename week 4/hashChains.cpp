/*
	Goal is to implement a hash table with lists chaining.
	Your program should support the following kinds of queries:
		- add string
		- del string
		- find string
		- check i - outputs the content of i-th list in table
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    int idx;
};

class QueryProcessor {
    int bucket_count;
    vector<vector<string>> elems = vector<vector<string>>(bucket_count);
    int hash_func(const string& s) const {
        static const int multiplier = 263;
        static const int prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; i--)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.idx;
        return query;
    }

    bool hasString(string name) const {
    	int hash = hash_func(name);

    	for (int i = 0; i < elems[hash].size(); i++) {
    		if (elems[hash][i] == name) {
    			return true;
    		}
    	}

        return false;
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
        	for (int i = elems[query.idx].size() - 1; i >= 0; i--) {
        		cout << elems[query.idx][i] << " ";
        	}
            cout << endl;
        } else {
            if (query.type == "find") {
            	cout << (hasString(query.s) ? "yes" : "no") << endl;
            } else if (query.type == "add") {
            	if (!hasString(query.s)) {
            		elems[hash_func(query.s)].push_back(query.s);
            	}
            } else if (query.type == "del") {
            	int hash = hash_func(query.s);
            	if (elems[hash].size()) {
            		for (int i = 0; i < elems[hash].size(); i++) {
            			if (elems[hash][i] == query.s) {
            				elems[hash].erase(elems[hash].begin() + i);
                        	break;
            			}
            		}
            	}
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            processQuery(readQuery());
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
