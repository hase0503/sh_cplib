struct UnionFind {
	vector<int> parents;

	UnionFind(int n) : parents(n, -1) {}

	int root(int x) {
		return parents[x] < 0 ? x : parents[x] = root(parents[x]);
	}

	void merge(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) {
			return;
		}
		if (-parents[x] < -parents[y]) {
			swap(x, y);
		}
		parents[x] += parents[y];
		parents[y] = x;
	}

	bool connected(int x, int y) {
		return root(x) == root(y);
	}

	int size(int x) {
		return -parents[root(x)];
	}
};
