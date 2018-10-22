/*
	There are n tables stored in some database. The tables
	are numbered from 1 to n. All tables share the same set
	of columns. Each table contains either several rows with
	real data or a symbolic link to another table. Initially,
	all tables contain data, and i-th table has r_i rows.
	You need to perform m of the following operations:
		1. Consider table number destination_i. Traverse the
		path of symbolic links to get to the data. That is,
		while destination_i contains a symbolic link instead
		of real data do destination_i ← symlink (destination_i).
		2. Consider the table number source_i and traverse the
		path of symbolic links from it in the same manner as
		for destination_i.
		3. Now, destination_i and source_i are the numbers of
		two tables with real data. If destination_i != source_i,
		copy all the rows from table source_i to table
		destination_i, then clear the table source_i and
		instead of real data put a symbolic link to destination_i
		into it.
		4. Print the maximum size among all n tables
		(recall that size is the number of rows in the table).
		If the table contains only a symbolic link, its size
		is considered to be 0.
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector<DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++) {
			sets[i].parent = i;
		}
	}

	int getParent(int table) {
		if (sets[table].parent == table) {
			return table;
		}
		return getParent(sets[table].parent);
	}

	void unite(int rootIdx, int childIdx) {
		DisjointSetsElement root = sets[rootIdx];
		DisjointSetsElement child = sets[childIdx];
		sets[childIdx].parent = rootIdx;
		sets[rootIdx].rank = max(sets[rootIdx].rank,
			sets[childIdx].rank + 1);
		sets[rootIdx].size += sets[childIdx].size;
		if (sets[rootIdx].size > max_table_size) {
			max_table_size = sets[rootIdx].size;
		}
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			if (sets[realDestination].rank >= sets[realSource].rank) {
				unite(realDestination, realSource);
			} else {
				unite(realSource, realDestination);
			}
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto& table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
        --destination;
        --source;
		
		tables.merge(destination, source);
	    cout << tables.max_table_size << endl;
	}

	return 0;
}
