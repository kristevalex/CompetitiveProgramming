#include <set>

struct ConSegs
{
    std::set<std::pair<int, int>> segs;

    void Fill(int l, int r) // [l, r)
    {
        auto itl = segs.lower_bound({l, l-1});
        if (itl == segs.begin())
            itl = segs.end();
        else
        {
            itl--;
            if (itl->second >= l)
            {
                l = std::min(l, itl->first);
                r = std::max(r, itl->second);

                segs.erase(itl);
            }
        }

        auto itp = segs.lower_bound({l, -1});
        while(itp != segs.end())
        {
            auto curid = *itp;
            if (curid.second > r)
            {
                if (curid.first > r)
                    break;

                r = curid.second;
                segs.erase(itp);
                break;
            }

            auto it2 = itp;
            ++itp;
            segs.erase(it2);
        }

        segs.insert({l, r});
    }

    bool IsFilled(int l, int r) // [l, r)
    {
        auto itl = segs.lower_bound({l+1, l-1});
        if (itl == segs.begin())
            return false;
        else
        {
            itl--;
            if (itl->first <= l && itl->second >= r)
                return true;
        }

        return false;
    }

    std::pair<int, int> Get(int x) // [l, r)
    {
        auto itl = segs.lower_bound({x+1, x-1});
        if (itl == segs.begin())
            return {x, x};
        else
        {
            itl--;
            if (itl->first <= x && itl->second > x)
                return *itl;
        }

        return {x, x};
    }
};

