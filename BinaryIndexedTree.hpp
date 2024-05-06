template <typename T>
struct BinaryIndexedTree {
	int n;
	vector<T> nodes;
	function<T(T, T)> op;
	T ti;

	BinaryIndexedTree(int n, function<T(T, T)> op, T ti) : n(n), op(op), ti(ti) {
		nodes.resize(n + 1, ti);
	}

	BinaryIndexedTree(vector<T> vec, function<T(T, T)> op, T ti) : BinaryIndexedTree(vec.size(), op, ti) {
		for (int i = 0; i < n; ++i) apply(i, vec[i]);
	}

	void get(int k) {
		return prod(k, k + 1);
	}

	void apply(int k, T x) {
		for (++k; k <= n; k += k & -k) nodes[k] = op(nodes[k], x);
	}

	T prod(int k) {
		T ret = ti;
		for (; k > 0; k -= k & -k) ret = op(ret, nodes[k]);
		return ret;
	}

	T prod(int k, int l) {
		return prod(l) - prod(k);
	}
};
