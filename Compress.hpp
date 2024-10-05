template<typename T>
map<T, int> compress(vector<T>& v) {
	map<T, int> cnt;
	for (int i = 0; i < int(v.size()); ++i) ++cnt[v[i]];
	map<T, int> ret;
	for (int sum = 0; auto [i, _]: cnt) {
		ret[i] = sum;
		sum += cnt[i];
	}
	for (int i = 0; i < int(v.size()); ++i) v[i] = ret[v[i]];
	return ret;
}
