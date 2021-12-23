#include <vector>

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

const int MOD = 998244353;
typedef modint<MOD> mint;
const int root = 31;
const int root_1 = 128805723;
const int root_pw = 1 << 23;
const mint mroot = mint(root);
const mint mroot_1 = mint(root_1);

void fft (std::vector<mint>& a, bool invert)
{
	int n = a.size();

	for (int i = 1, j = 0; i < n; ++i)
    {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			std::swap (a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1)
    {
		mint wlen = invert ? mroot_1 : mroot;
		for (int i = len; i < root_pw; i <<= 1)
			wlen *= wlen;
		for (int i = 0; i < n; i += len)
		{
			mint w(1);
			for (int j = 0; j < len/2; ++j)
			{
				mint u = a[i + j];
				mint v = a[i + j + len/2] * w;
				a[i + j] = u + v;
				a[i + j + len/2] = u - v;
				w *= wlen;
			}
		}
	}

	if (invert)
    {
		mint nrev = mint(n).inv();
		for (int i = 0; i < n; ++i)
			a[i] *= nrev;
	}
}

void multiply (const std::vector<mint>& a, const std::vector<mint>& b, size_t sz, size_t ressz, std::vector<mint>& res)
{
    size_t n = 1;
	while (n < sz)  n <<= 1;
	n <<= 1;

	std::vector<mint> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	fa.resize(n), fb.resize(n);

	for (int i = sz; i < n; ++i)
	{
	    fa[i] = mint();
	    fb[i] = mint();
	}


	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);

	n = std::min(n, ressz);
	if (res.size() < n)
        res.resize(n);
	for (size_t i = 0; i < n; ++i)
		res[i] = fa[i];
}
