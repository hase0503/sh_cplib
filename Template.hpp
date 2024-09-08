#include <bits/stdc++.h>

#pragma GCC optimize("O3")

#ifdef LOCAL
#include "./cpp-dump/cpp-dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
namespace cp = cpp_dump;
CPP_DUMP_SET_OPTION_GLOBAL(max_line_width, 80);
CPP_DUMP_SET_OPTION_GLOBAL(log_label_func, cp::log_label::filename());
CPP_DUMP_SET_OPTION_GLOBAL(enable_asterisk, true);
#else
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#endif

using namespace std;
using llong = long long;
using ullong = unsigned long long;
using dbl = double;
using ldbl = long double;
template<typename T> using vec = vector<T>;
using str = string;
template<typename T> using mset = multiset<T>;
template<typename T> using uset = unordered_set<T>;
template<typename T> using umset = unordered_multiset<T>;
template<typename T, typename U> using mmap = multimap<T, U>;
template<typename T, typename U> using umap = unordered_map<T, U>;
template<typename T, typename U> using ummap = unordered_multimap<T, U>;
template <typename T, typename U = std::vector<T>, typename V = std::less<T>> using pque = std::priority_queue<T, U, V>;
template<typename T>struct range{struct I{T l,r,x,step;T operator*(){return x;}bool operator!=(I& _){return step>=0?l<=x&&x<r:r<x&&x<=l;}void operator++(){x+=step;}};I i;range(T r):i({0,r,0,1}){}range(T l,T r):i({l,r,l,1}){}range(T l,T r,T step):i({l,r,l,step}){}I& begin(){return i;}I& end(){return i;}};

const llong linf = LLONG_MAX / 2ll;
const int inf = INT_MAX / 2;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
}
