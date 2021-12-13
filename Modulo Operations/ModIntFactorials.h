template<int m>
struct modint
{
    long long x;

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

std::vector<mint> factorial;
std::vector<mint> invfactorial;

inline mint C(int N, int K)
{
    if (N < K || K < 0)
        return mint();

    return factorial[N] * invfactorial[K] * invfactorial[N-K];
}

inline void SetupFactorial(int sz)
{
    ++sz;
    ::factorial.resize(sz);
    ::invfactorial.resize(sz);

    ::factorial[0] = 1;
    for (int i = 1; i < sz; ++i)
        ::factorial[i] = ::factorial[i-1] * mint(i);

    ::invfactorial[sz-1] = ::factorial[sz-1].inv();
    for (int i = sz-2; i >= 0; --i)
        ::invfactorial[i] = ::invfactorial[i+1]*mint(i+1);
}
