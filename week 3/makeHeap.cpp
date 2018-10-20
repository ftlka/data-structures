/*
    Heap implementation
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class HeapBuilder {
private:
    vector<int> data_;
    vector<pair<int,int>> swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << endl;
        for (int i = 0; i < swaps_.size(); i++) {
            cout << swaps_[i].first << " " << swaps_[i].second << endl;
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> data_[i];            
        }
    }

    void SiftDown(int idx) {
        int min_idx = idx;
        int min_val = data_[idx];
        if (2 * (idx + 1) - 1 < data_.size() && data_[2 * (idx + 1) - 1] < min_val) {
            min_idx = 2 * (idx + 1) - 1;
            min_val = data_[min_idx];
        }
        if (2 * (idx + 1) < data_.size() && data_[2 * (idx + 1)] < min_val) {
            min_idx = 2 * (idx + 1);
            min_val = data_[min_idx];
        }

        if (idx != min_idx) {
            swap(data_[idx], data_[min_idx]);
            swaps_.push_back(make_pair(idx, min_idx));
            SiftDown(min_idx);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        int nodes_end_idx = int(data_.size() / 2);
        for (int i = data_.size() / 2; i >= 0; i--) {
            SiftDown(i);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
