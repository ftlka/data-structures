/*
	Implementation of Rabin-Karp's algorithm
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

int hash_func(const string& s) {
    	static const int prime = 1000000007;
        static const int multiplier = 31;
        long long hash = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            hash = (long long)(multiplier * hash + s[i]) % prime;
        }
        return hash;
}

void print_occurrences(const std::vector<int>& output) {
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    cout << endl;
}

vector<long long> precomputeHashes(const string& t, const string& p, int prime, int mult) {
		vector<long long> h(t.size() - p.size() + 1);
		h[t.size() - p.size()] = hash_func(t.substr(t.size() - p.size(), t.size() - 1));
		long long y = 1;
		for (int i = 1; i <= p.size(); i++) {
			y = (y * mult) % prime;
		}

		for (int i = t.size() - p.size() - 1; i >= 0; i--) {
			h[i] = ((long long)(mult * h[i + 1] + t[i] - y * t[i + p.size()])
				% prime + prime) % prime;
		}
		return h;
	}

vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    if (s.size() == t.size() && s == t) {
    	cout << 0;
    }
    static const int prime = 1000000007;
    static const int multiplier = 31;
    
    vector<int> res;
    int pHash = hash_func(s);
    vector<long long> h = precomputeHashes(t, s, prime, multiplier);

    for (int i = 0; i <= t.size() - s.size(); i++) {
    	if (pHash == h[i] && s == t.substr(i, s.size())) {
    		res.push_back(i);
    	}
    }
    return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
