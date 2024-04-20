template <typename T>
struct WeightedUnionFind {
	vector<int> parents;
	vector<T> diff_weights;

	WeightedUnionFind(int n) : parents(n, -1), diff_weights(n) {}

	int root(int x) {
		if (parents[x] < 0) return x;
		int root_of_x = root(parents[x]);
		diff_weights[x] += diff_weights[parents[x]];
		return parents[x] = root_of_x;
	}

	void merge(int x, int y, T w) {
		w += weight(x), w -= weight(y);
		x = root(x), y = root(y);
		if (x == y) return;
		if (-parents[x] < -parents[y]) swap(x, y), w *= -1;
		parents[x] += parents[y];
		parents[y] = x;
		diff_weights[y] = w;
	}

	T diff (int x, int y) {
		return weight(y) - weight(x);
	}

	bool connectes(int x, int y) {
		return root(x) == root(y);
	}

	int size(int x) {
		return -parents[root(i)];
	}

private:
	T weight(int x) {
		root(x);
		return diff_weights[x];
	}
};
