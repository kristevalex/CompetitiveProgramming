#include <vector>
#include <assert.h>

template<class T> struct Mat
{
    int r,c;
    std::vector<std::vector<T>> d;
    Mat(int _r, int _c) :
        r(_r),
        c(_c)
    {
        d.assign(r, std::vector<T>(c));
    }

    Mat() :
        Mat(0,0) {}

    Mat(const std::vector<std::vector<T>>& _d) :
        r(_d.size()),
        c(_d[0].size())
    {
        d = _d;
    }

    Mat& operator+= (const Mat& m)
    {
        assert(r == m.r && c == m.c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                d[i][j] += m.d[i][j];

        return *this;
    }

    Mat& operator-= (const Mat& m)
    {
        assert(r == m.r && c == m.c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                d[i][j] -= m.d[i][j];

        return *this;
    }

    Mat operator* (const Mat& m)
    {
        assert(c == m.r);
        Mat x(r, m.c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                for (int l = 0; l < m.c; ++l)
                    x.d[i][l] += d[i][j]*m.d[j][l];

        return x;
    }

    Mat operator+ (const Mat& m)
    {
        return Mat(*this) += m;
    }

    Mat operator- (const Mat& m)
    {
        return Mat(*this) -= m;
    }

    Mat& operator*= (const Mat& m)
    {
        return *this = (*this)*m;
    }

    Mat operator^ (long long arg)
    {
        assert(r == c);
        if (arg == 0)
        {
            Mat neut(r, c);
            for (int i = 0; i < r; ++i)
                neut.d[i][i] = 1;
            return neut;
        }
        if (arg == 1) return *this;

        auto t = *this ^ (arg >> 1);
        t *= t;

        if (arg & 1) t *= *this;

        return t;
    }
};
