#include<vector>

struct SegmentTreeMin
{
    int sz;
    std::vector<std::pair<int, int>> tree;
    std::vector<int> tempr;


    SegmentTreeMin() {}

    SegmentTreeMin(int _sz)
    {
        sz = _sz;
        tree.assign(4 * sz, {0, 0});
    }

    inline std::pair<int, int> mergeVal(std::pair<int, int> val1, std::pair<int, int> val2)
    {
        if (val1.first == val2.first)
            return max(val1, val2);
        return min(val1, val2);
    }

    void build(int v, int tl, int tr)
    {
        if (tl == tr)
        {
            tree[v] = {tempr[tl], tl};
            return;
        }

        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = mergeVal(tree[2 * v], tree[2 * v + 1]);
    }

    SegmentTreeMin(const std::vector<int>& dt)
    {
        sz = dt.size();
        tree.assign(4 * sz, {0, 0});
        tempr = dt;
        build(1, 0, sz - 1);
    }

    void Build(const std::vector<int>& dt)
    {
        sz = dt.size();
        tree.assign(4 * sz, {0, 0});
        tempr = dt;
        build(1, 0, sz - 1);
    }

    std::pair<int, int> query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return {INT_MAX, -1};
		if (tl >= l && tr <= r)
            return tree[v];

        int tm = (tl + tr) / 2;

        return mergeVal(query(v * 2, tl, tm, l, std::min(r, tm)),
                        query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }

    inline std::pair<int, int> Query(int l, int r)
    {
        return query(1, 0, sz - 1, l, r);
    }

    void update(int v, int tl, int tr, int id, int val)
    {
        if (tr < id) return;
        if (id < tl) return;
		if (tl == id && tr == id)
        {
			tree[v] = {val, id};
			return;
		}

		int tm = (tl + tr) / 2;
        update (v * 2, tl, tm, id, val);
        update (v * 2 + 1, tm + 1, tr, id, val);
        tree[v] = mergeVal(tree[2 * v], tree[2 * v + 1]);
    }

    inline void Update(int id, int val)
    {
        update(1, 0, sz - 1, id, val);
    }
};
