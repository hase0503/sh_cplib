long long inv_mod(long long x, long long mod) {
	return x == 1 ? 1 : mod + (1 - mod * inv_mod(mod % x, x)) / x;
}
