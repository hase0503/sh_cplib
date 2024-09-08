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

	void set(int pos, T x) {
		vct[pos + 1] = x;
	}

	void setup() {
		for (int i = 0; i < n; ++i) {
			vct[i + 1] = op(vct[i], vct[i + 1]);
		}
	}

	T get(int pos) {
		return inv_op(vct[pos + 1], vct[pos]);
	}

	T prod(int left, int right) {
		return inv_op(vct[right], vct[left]);
	}
};
