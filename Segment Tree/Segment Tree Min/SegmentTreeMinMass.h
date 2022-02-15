#include<vector>

struct SegmentTreeMin
{
    int sz;
    std::vector<int> tree;
    std::vector<int> adds;
    std::vector<int> tempr;


    SegmentTreeMin() {}

    SegmentTreeMin(int _sz)
    {
        sz = _sz;
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);
    }

    inline int getValue(int v)
    {
        return tree[v] + adds[v];
    }

    inline void push(int v)
    {
        adds[2 * v] += adds[v];
        adds[2 * v + 1] += adds[v];
        adds[v] = 0;
    }

    inline int mergeVal(int val1, int val2)
    {
        return min(val1, val2);
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
        tree[v] = mergeVal(getValue(2 * v), getValue(2 * v + 1));
    }

    SegmentTreeMin(const std::vector<int>& dt)
    {
        sz = dt.size();
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);
        tempr = dt;
        build(1, 0, sz - 1);
    }

    void Build(const std::vector<int>& dt)
    {
        sz = dt.size();
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);
        tempr = dt;
        build(1, 0, sz - 1);
    }

    int query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 1400000000;
		if (tl >= l && tr <= r)
            return getValue(v);

        int tm = (tl + tr) / 2;

        push(v);
        tree[v] = mergeVal(getValue(2 * v), getValue(2 * v + 1));

        return mergeVal(query(v * 2, tl, tm, l, std::min(r, tm)),
                        query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }

    inline int Query(int l, int r)
    {
        return query(1, 0, sz - 1, l, r);
    }

    void update(int v, int tl, int tr, int l, int r, int diff)
    {
        if (tr < l) return;
        if (r < tl) return;
		if (tl == l && tr == r)
        {
			adds[v] += diff;
			return;
		}

		int tm = (tl + tr) / 2;

		push(v);

        update (v * 2, tl, tm, l, std::min(r, tm), diff);
        update (v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, diff);
        tree[v] = mergeVal(getValue(2 * v), getValue(2 * v + 1));
    }

    inline void Update(int l, int r, int diff)
    {
        update(1, 0, sz - 1, l, r, diff);
    }
};
