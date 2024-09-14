template <typename T>
struct Cumsum {
	using F = function<T(T, T)>;

	int n;
	vector<T> vct;

	T id;
	F op, inv_op;

	Cumsum(int n, T id, F op, F inv_op): n(n), id(id), op(op), inv_op(inv_op) {
		vct.resize(n + 1, id);
	}

	Cumsum(vector<T> v, T id, F op, F inv_op): Cumsum(int(v.size()), id, op, inv_op) {
		for (int i = 0; i < n; ++i) {
			set(i, v[i]);
		}
	}

	void set(int pos, T x) {
		vct[pos + 1] = x;
	}

	void setup() {
		for (int i = 0; i < n; ++i) {
			vct[i + 1] = op(vct[i], vct[i + 1]);
		}
	}

	T get(int pos) {
		return prod(pos, pos + 1);
	}

	T prod(int left, int right) {
		return inv_op(vct[right], vct[left]);
	}
};
