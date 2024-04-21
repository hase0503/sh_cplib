template <typename T, typename U>
struct LazySegmentTree {
	int n;
	vector<T> nodes;
	vector<U> lazy;
	T ti;
	U ui;
	function<T(T, T)> op;
	function<T(T, U, int)> mapping;
	function<U(U, U)> composition;

	int bit_width(int x) {
		int ret = 0;
		while (x) x >>= 1, ++ret;
		return ret;
	}

	LazySegmentTree(int size, T ti, U ui, function<T(T, T)> op, function<T(T, U, int)> mapping, function<U(U, U)> composition)
		: ti(ti), ui(ui), op(op), mapping(mapping), composition(composition) {
		n = 1;
		while (n < size) n *= 2;
		nodes.resize(n * 2, ti);
		lazy.assign(n * 2, ui);
	}

	LazySegmentTree(vector<T> vec, T ti, U ui, function<T(T, T)> op, function<T(T, U, int)> mapping, function<U(U, U)> composition)
		: LazySegmentTree(vec.size(), ti, ui, op, mapping, composition) {
		build(vec);
	}

	void build(vector<T> vec) {
		for (int i = 0; i < n; ++i) nodes[n + i] = vec[i];
		for (int i = n - 1; i > 0; --i) update(i);
	}

	void set(int k, T x) {
		k += n;
		for (int i = bit_width((unsigned int)n) - 1; i > 0; --i) propagate(k >> i);
		nodes[k] = x;
		for (int i = 1; i < bit_width((unsigned int)n); ++i) update(k >> i);
	}

	T get(int k) {
		k += n;
		for (int i = bit_width((unsigned int)n) - 1; i > 0; --i) propagate(k >> i);
		return nodes[k];
	}

	T prod(int l, int r) {
		l += n, r += n;
		for (int i = bit_width((unsigned int)n) - 1; i > 0; --i) {
			if (((l >> i) << i) != l) propagate(l >> i);
			if (((r >> i) << i) != r) propagate((r - 1) >> i);
		}
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

	void apply(int k, U x) {
		k += n;
		for (int i = bit_width((unsigned int)n) - 1; i > 0; --i) propagate(k >> i);
		nodes[k] = op(nodes[k], x);
		for (int i = 1; i < bit_width((unsigned int)n); ++i) update(k >> i);
	}

	void apply(int l, int r, U x) {
		l += n, r += n;
		for (int i = bit_width((unsigned int)n) - 1; i > 0; --i) {
			if (((l >> i) << i) != l) propagate(l >> i);
			if (((r >> i) << i) != r) propagate((r - 1) >> i);
		}
		for (int l2 = l, r2 = r; l2 < r2; l2 /= 2, r2 /= 2) {
			if (l2 % 2 == 1) all_apply(l++, x);
			if (r2 % 2 == 1) all_apply(--r, x);
		}
		for (int i = 1; i < bit_width((unsigned int)n); ++i) {
			if (((l >> i) << i) != l) update(l >> i);
			if (((r >> i) << i) != r) update((r - 1) >> i);
		}
	}

private:

	void update(int x) {
		nodes[x] = op(nodes[x * 2], nodes[x * 2 + 1]);
	}

	void all_apply(int i, U x) {
		nodes[i] = mapping(nodes[i], x, 1 << (bit_width((unsigned int)n) - bit_width((unsigned int)(i))));
		if (i < n) lazy[i] = composition(lazy[i], x);
	}

	void propagate(int i) {
		all_apply(i * 2, lazy[i]);
		all_apply(i * 2 + 1, lazy[i]);
		lazy[i] = ui;
	}
};
