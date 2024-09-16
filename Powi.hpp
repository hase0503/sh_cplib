template <typename T>
T powi(T x, T y) {
	assert(y >= 0);
	T ret = 1;
	while (y) {
		if (y & 1) {
			ret *= x;
		}
		y >>= 1;
		x *= x;
	}
	return ret;
}
