#include<vector>

struct SegmentTreeSum
{
    int sz;
    std::vector<long long> tree;
    std::vector<long long> adds;
    std::vector<long long> tempr;

    SegmentTreeSum() {}

    SegmentTreeSum(int _sz)
    {
        sz = _sz;
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);
    }

    void build(int v, int tl, int tr)
    {
        if (tl == tr)
        {
            tree[v] = tempr[tl];
            return;
        }

        int tm = (tl + tr) / 2;
        build(2*v, tl, tm);
        build(2*v+1, tm+1, tr);
        tree[v] = mergeNodes(getVal(2*v, tl, tm), getVal(2*v+1, tm+1, tr));
    }

    SegmentTreeSum(std::vector<long long> dt)
    {
        sz = dt.size();
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);
        tempr = dt;
        build(1, 0, sz-1);
    }

	inline long long getVal(int v, int tl, int tr)
	{
	    return tree[v] + adds[v] * (tr - tl + 1);
	}

	inline long long mergeNodes(long long val1, long long val2)
	{
	    return val1 + val2;
	}

	inline void push(int v)
	{
	    adds[2*v] += adds[v];
	    adds[2*v+1] += adds[v];
	    adds[v] = 0;
	}

    long long query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
		if (tl >= l && tr <= r)
            return getVal(v, tl, tr);


        int tm = (tl + tr) / 2;

        push(v);
        tree[v] = mergeNodes(getVal(2*v, tl, tm), getVal(2*v+1, tm+1, tr));

        auto nl = query(v*2, tl, tm, l, std::min(r,tm));
        auto nr = query(v*2+1, tm+1, tr, std::max(l,tm+1), r);

        return mergeNodes(nl, nr);
    }

    long long Query(int l, int r)
    {
        return query(1, 0, sz-1, l, r);
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

		push(v);

		int tm = (tl + tr) / 2;
        update (v*2, tl, tm, l, std::min(r, tm), diff);
        update (v*2+1, tm+1, tr, std::max(l, tm+1), r, diff);
        tree[v] = mergeNodes(getVal(2*v, tl, tm), getVal(2*v+1, tm+1, tr));
    }

    void Update(int l, int r, int diff)
    {
        update(1, 0, sz-1, l, r, diff);
    }
};

