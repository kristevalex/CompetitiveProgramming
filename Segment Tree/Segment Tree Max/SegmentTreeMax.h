#include<vector>

struct SegmentTreeMax
{
    int sz;
    std::vector<long long> tree;
    std::vector<int> tempr;


    SegmentTreeMax() {}

    SegmentTreeMax(int _sz)
    {
        sz = _sz;
        tree.assign(4 * sz, 0);
    }

    void build(int v, int tl, int tr)
    {
        if (tl == tr)
        {
            tree[v] = tempr[tl];
            return;
        }

        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }

    SegmentTreeMax(const std::vector<int>& dt)
    {
        sz = dt.size();
        tree.assign(4 * sz, 0);
        tempr = dt;
        build(1, 0, sz - 1);
    }

    long long query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return LLONG_MIN;
		if (tl >= l && tr <= r)
            return tree[v];

        int tm = (tl + tr) / 2;

        return max(query(v * 2, tl, tm, l, std::min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }

    inline long long Query(int l, int r)
    {
        return query(1, 0, sz - 1, l, r);
    }

    void update(int v, int tl, int tr, int id, int val)
    {
        if (tr < id) return;
        if (id < tl) return;
		if (tl == id && tr == id)
        {
			tree[v] = val;
			return;
		}

		int tm = (tl + tr) / 2;
        update (v * 2, tl, tm, id, val);
        update (v * 2 + 1, tm + 1, tr, id, val);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }

    inline void Update(int id, int val)
    {
        update(1, 0, sz - 1, id, val);
    }
};
