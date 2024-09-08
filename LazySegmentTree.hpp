template <typename T, typename U>
struct LazySegmentTree {
        int n;
        vector<T> nodes;
        vector<U> lazy;
        vector<int> sizes;
        T t_id;
        U u_id;
        function<T(T, T)> op;
        function<T(T, U, int)> mapping;
        function<U(U, U)> composition;

        int bit_width(int x) {
                int ret = 0;
                while (x > 0) {
                        x >>= 1;
                        ++ret;
                }
                return ret;
        }

        LazySegmentTree(int size, T ti, U ui, function<T(T, T)> op, function<T(T, U, int)> mapping, function<U(U, U)> composition)
                : t_id(ti), u_id(ui), op(op), mapping(mapping), composition(composition) {
                n = 1 << bit_width(size);
                nodes.resize(n * 2, ti);
                lazy.resize(n * 2, ui);
                sizes.resize(n * 2);
                for (int i = 0; i < size; ++i) {
                        sizes[n + i] = 1;
                }
                for (int i = n - 1; i > 0; --i) {
                        sizes[i] = sizes[i * 2] + sizes[i * 2 + 1];
                }
        }

        LazySegmentTree(vector<T> vec, T ti, U ui, function<T(T, T)> op, function<T(T, U, int)> mapping, function<U(U, U)> composition)
                : LazySegmentTree(vec.size(), ti, ui, op, mapping, composition) {
                build(vec);
        }

        void build(vector<T> vec) {
                for (int i = 0; i < n; ++i) {
                        nodes[n + i] = vec[i];
                }
                for (int i = n - 1; i > 0; --i) {
                        update(i);
                }
        }

        void set(int pos, T x) {
                pos += n;
                for (int i = bit_width(n) - 1; i > 0; --i) {
                        propagate(pos >> i);
                }
                nodes[pos] = x;
                for (int i = 1; i < bit_width(n); ++i) {
                        update(pos >> i);
                }
        }

        T get(int pos) {
                pos += n;
                for (int i = bit_width(n) - 1; i > 0; --i) {
                        propagate(pos >> i);
                }
                return nodes[pos];
        }

        T prod(int l, int r) {
                l += n, r += n;
                for (int i = bit_width(n) - 1; i > 0; --i) {
                        if (((l >> i) << i) != l) {
                                propagate(l >> i);
                        }
                        if (((r >> i) << i) != r) {
                                propagate((r - 1) >> i);
                        }
                }

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

        void apply(int pos, U x) {
                pos += n;
                for (int i = bit_width(n) - 1; i > 0; --i) {
                        propagate(pos >> i);
                }
                nodes[pos] = mapping(nodes[pos], x, sizes[pos]);
                for (int i = 1; i < bit_width(n); ++i) {
                        update(pos >> i);
                }
        }

        void apply(int l, int r, U x) {
                l += n, r += n;
                for (int i = bit_width(n) - 1; i > 0; --i) {
                        if (((l >> i) << i) != l) propagate(l >> i);
                        if (((r >> i) << i) != r) propagate((r - 1) >> i);
                }
                for (int l2 = l, r2 = r; l2 < r2; l2 /= 2, r2 /= 2) {
                        if (l2 % 2 == 1) {
                                all_apply(l2++, x);
                        }
                        if (r2 % 2 == 1) {
                                all_apply(--r2, x);
                        }
                }
                for (int i = 1; i < bit_width(n); ++i) {
                        if (((l >> i) << i) != l) {
                                update(l >> i);
                        }
                        if (((r >> i) << i) != r) {
                                update((r - 1) >> i);
                        }
                }
        }

private:

        void update(int x) {
                nodes[x] = op(nodes[x * 2], nodes[x * 2 + 1]);
        }

        void all_apply(int i, U x) {
                nodes[i] = mapping(nodes[i], x, sizes[i]);
                if (i < n) {
                        lazy[i] = composition(lazy[i], x);
                }
        }

        void propagate(int i) {
                all_apply(i * 2, lazy[i]);
                all_apply(i * 2 + 1, lazy[i]);
                lazy[i] = u_id;
        }
};
