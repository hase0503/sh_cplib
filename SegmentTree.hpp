template <typename T>
struct SegmentTree {
	int n;
	vector<T> nodes;
	T ti;
	function<T(T, T)> op;

	SegmentTree(int size, T ti, function<T(T, T)> op) : ti(ti), op(op) {
		n = 1;
		while (n < size) n *= 2;
		nodes.resize(n * 2, ti);
		for (int i = n - 1; i > 0; --i) update(i);
	}

	SegmentTree(vector<T> vec, T ti, function<T(T, T)> op) : ti(ti), op(op) {
		n = 1;
		while (n < size) n *= 2;
		nodes.resize(n * 2, ti);
		build(vec);
	}

	void build(vector<T> vec) {
		for (int i = 0; i < n; ++i) nodes[n + i] = vec[i];
		for (int i = n - 1; i > 0; --i) update(i);
	}

	void set(int i, T x) {
		i += n;
		nodes[i] = x;
		while (i /= 2) update(i);
	}

	void apply(int i, T x) {
		set(i, op(nodes[n + i], x));
	}

	T get(int i) {
		return nodes[n + i];
	}

	T prod(int l, int r) {
		l += n, r += n;
		T l_cum = ti, r_cum = ti;
		for (; l < r; l /= 2, r /= 2) {
			if (l % 2 == 1) l_cum = op(l_cum, nodes[l++]);
			if (r % 2 == 1) r_cum = op(r_cum, nodes[--r]);
		}
		return op(l_cum, r_cum);
	}

	T all_prod() {
		return nodes[1];
	}

private:

	void update(int x) {
		nodes[x] = op(nodes[x * 2], nodes[x * 2 + 1]);
	}
};
