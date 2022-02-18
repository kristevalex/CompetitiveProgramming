#include<vector>

template<int m>
struct modint
{
    int x;

    modint() :
        x(0) {}

    modint(long long arg)
    {
        arg%= m;
        if (arg < 0) x = arg + m;
        else x = arg;
    }

    modint& operator+= (const modint& other)
    {
        x += other.x;
        if (x >= m) x -= m;

        return *this;
    }

    modint& operator*= (const modint& other)
    {
        x = (x * 1ll * other.x) % m;
        return *this;
    }

    modint& operator-= (const modint& other)
    {
        x+= m - other.x;
        if (x >= m) x-= m;

        return *this;
    }

    modint operator+ (const modint& other) const
    {
        modint tmp = *this;
        tmp += other;
        return tmp;
    }

    modint operator- (const modint& other) const
    {
        modint tmp = *this;
        tmp -= other;
        return tmp;
    }

    modint operator* (const modint& other) const
    {
        modint tmp = *this;
        tmp *= other;
        return tmp;
    }

    explicit operator int () const
    {
        return x;
    }

    modint& operator++ ()
    {
        ++x;
        if (x == m) x = 0;

        return *this;
    }

    modint& operator-- ()
    {
        if (x == 0) x = m-1;
        else --x;

        return *this;
    }

    modint operator++ (int)
    {
        modint tmp = *this;
        ++*this;

        return tmp;
    }

    modint operator-- (int)
    {
        modint tmp = *this;
        --*this;

        return tmp;
    }

    bool operator== (const modint& other) const
    {
        return x == other.x;
    }

    bool operator!= (const modint& other) const
    {
        return x != other.x;
    }

    template<class T>
    modint operator^ (T arg) const
    {
        if (arg == 0) return 1;
        if (arg == 1) return x;

        auto t = *this ^ (arg >> 1);
        t*= t;

        if (arg & 1) t*= *this;

        return t;
    }

    modint inv() const // works clearly only when 'm' is prime number
    {
        return *this ^ (m-2);
    }
};

const int MOD = 1000000007;
typedef modint<MOD> mint;

struct SegmentTreeSum
{
    int sz;
    mint mult;
    std::vector<mint> tree;
    std::vector<mint> adds;
    std::vector<mint> pws;
    std::vector<mint> pws_sums;

    SegmentTreeSum() {}

    SegmentTreeSum(int _sz, int _mult)
    {
        sz = _sz;
        mult = mint(_mult);
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);

        pws.resize(sz+1);
        pws_sums.resize(sz+1);
        pws[0] = mint(1);
        pws_sums[0] = mint(1);
        for (int i = 1; i <= sz; ++i)
            pws[i] = pws[i-1] * mult;
        for (int i = 1; i <= sz; ++i)
            pws_sums[i] = pws_sums[i-1] + pws[i-1];
    }

    void build(int v, int tl, int tr, const std::vector<long long>& dt)
    {
        if (tl == tr)
        {
            tree[v] = dt[tl];
            return;
        }

        int tm = (tl + tr) / 2;

        build(2*v, tl, tm, dt);
        build(2*v+1, tm+1, tr, dt);

        tree[v] = mergeNodes(getVal(2*v, tl, tm), getVal(2*v+1, tm+1, tr));
    }

    SegmentTreeSum(const std::vector<long long>& dt, int _mult)
    {
        sz = dt.size();
        mult = mint(_mult);
        tree.assign(4 * sz, 0);
        adds.assign(4 * sz, 0);

        pws.resize(sz+1);
        pws_sums.resize(sz+1);
        pws[0] = mint(1);
        pws_sums[0] = mint(1);
        for (int i = 1; i <= sz; ++i)
            pws[i] = pws[i-1] * mult;
        for (int i = 1; i <= sz; ++i)
            pws_sums[i] = pws_sums[i-1] + pws[i];

        build(1, 0, sz-1, dt);
    }

	inline mint getVal(int v, int tl, int tr)
	{
	    return tree[v] + adds[v] * pws_sums[tr - tl];
	}

	inline mint mergeNodes(mint val1, mint val2)
	{
	    return val1 + val2;
	}

	inline void push(int v, int tl, int tr)
	{
	    int tm = (tl + tr) / 2;

	    adds[2*v] += adds[v];
	    adds[2*v+1] += adds[v] * pws[tm-tl+1];
	    adds[v] = 0;
	}

    mint query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return mint(0);
		if (tl >= l && tr <= r)
            return getVal(v, tl, tr);


        int tm = (tl + tr) / 2;

        push(v, tl, tr);
        tree[v] = mergeNodes(getVal(2*v, tl, tm), getVal(2*v+1, tm+1, tr));

        auto nl = query(v*2, tl, tm, l, std::min(r,tm));
        auto nr = query(v*2+1, tm+1, tr, std::max(l,tm+1), r);

        return mergeNodes(nl, nr);
    }

    mint Query(int l, int r)
    {
        return query(1, 0, sz-1, l, r);
    }

    void update(int v, int tl, int tr, int l, int r, mint diff)
    {
        if (tr < l) return;
        if (r < tl) return;
		if (tl == l && tr == r)
        {
			adds[v] += diff;
			return;
		}

		push(v, tl, tr);

		int tm = (tl + tr) / 2;
        update (v*2, tl, tm, l, std::min(r, tm), diff);
        update (v*2+1, tm+1, tr, std::max(l, tm+1), r, diff * pws[std::max(0, tm+1-std::max(tl, l))]);
        tree[v] = mergeNodes(getVal(2*v, tl, tm), getVal(2*v+1, tm+1, tr));
    }

    void Update(int l, int r, mint diff)
    {
        update(1, 0, sz-1, l, r, diff);
    }
};
