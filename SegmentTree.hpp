template <typename T>
struct SegmentTree {
	using F = function<T(T, T)>;

	int n;
	vector<T> nodes;
	T t_id;
	F op;

	int bit_width(int x) {
		int ret = 0;
		while (x > 0) {
			x >>= 1;
			++ret;
		}
		return ret;
	}

	SegmentTree(int size, T t_id, F op) : t_id(t_id), op(op) {
		n = 1 << bit_width(size);
		nodes.resize(n * 2, t_id);
		for (int i = n - 1; i > 0; --i) {
			update(i);
		}
	}

	SegmentTree(vector<T> vec, T t_id, F op) : t_id(t_id), op(op) {
		int size = vec.size();
		n = 1 << bit_width(size);
		nodes.resize(n * 2, t_id);
		build(vec);
	}

	void build(vector<T> vec) {
		for (int i = 0; i < int(vec.size()); ++i) {
			nodes[n + i] = vec[i];
		}
		for (int i = n - 1; i > 0; --i) {
			update(i);
		}
	}

	void set(int i, T x) {
		i += n;
		nodes[i] = x;
		while (i / 2 > 0) {
			i /= 2;
			update(i);
		}
	}

	void apply(int i, T x) {
		set(i, op(nodes[n + i], x));
	}

	T get(int i) {
		return nodes[n + i];
	}

	T prod(int l, int r) {
		l += n, r += n;
		T l_cum = t_id, r_cum = t_id;
		while (l < r) {
			if (l % 2 == 1) {
				l_cum = op(l_cum, nodes[l++]);
			}
			if (r % 2 == 1) {
				r_cum = op(nodes[--r], r_cum);
			}

			l /= 2;
			r /= 2;
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
