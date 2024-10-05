template<typename T>
map<T, int> compress(vec<T>& v) {
	map<T, int> cnt;
	for (int i: range(int(v.size()))) ++cnt[v[i]];
	map<T, int> ret;
	for (int sum = 0; auto [i, _]: cnt) {
		ret[i] = sum;
		sum += cnt[i];
	}
	for (int i: range(int(v.size()))) v[i] = ret[v[i]];
	return ret;
}
