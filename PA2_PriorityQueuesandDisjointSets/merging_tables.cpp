#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
	int size, parent, rank;
    // constructor
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;
    // size = number of tables
	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++){
			sets[i].parent = i;
		}
	}
	int getParent(int table) {
		// find parent and compress path
		// Path Compression
        if(table != sets[table].parent)
            sets[table].parent = getParent(sets[table].parent);
        return sets[table].parent;
	}
	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);

		if (realDestination != realSource) {
			// merge two components
            // update max_table_size
            sets[realSource].parent = realDestination;
            sets[realDestination].size += sets[realSource].size;
            sets[realSource].size = 0;
            max_table_size = max(sets[realDestination].size, max_table_size);
		}
	}
};

int main() {
	int n, m;
	cin >> n >> m;
    // number of tables
	DisjointSets tables(n);
	for (int i = 0; i < n; i++) {
        int tableSize;
		cin >> tableSize;
		tables.sets[i].size = tableSize;
		tables.max_table_size = max(tables.max_table_size, tableSize);
	}
    // merge query
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
