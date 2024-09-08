template <typename T>
struct BinaryIndexedTree {
        using F = function<T(T, T)>;

        int n;
        vector<T> nodes;
        F op;
        F inv_op;
        T t_id;

        BinaryIndexedTree(int n, F op, F inv_op, T t_id) : n(n), op(op), inv_op(inv_op), t_id(t_id) {
                nodes.resize(n + 1, t_id);
        }

        BinaryIndexedTree(vector<T> vec, F op, F inv_op, T t_id) : BinaryIndexedTree(vec.size(), op, inv_op, t_id) {
                for (int i = 0; i < n; ++i) {
                        apply(i, vec[i]);
                }
        }

        void get(int pos) {
                return prod(pos, pos + 1);
        }

        void apply(int pos, T x) {
                for (++pos; pos <= n; pos += pos & -pos) nodes[pos] = op(nodes[pos], x);
        }

        T prod(int pos) {
                T ret = t_id;
                for (; pos > 0; pos -= pos & -pos) ret = op(ret, nodes[pos]);
                return ret;
        }

        T prod(int left, int right) {
                return inv_op(prod(right), prod(left));
        }
};
