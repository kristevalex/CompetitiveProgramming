#include <set>
#include <iostream>

struct NOSSegs
{
    std::set<std::pair<int, int>> segs;

    inline std::set<std::pair<int, int>>::iterator Get(int x)
    {
        return segs.lower_bound({x, -1});
    }

    void Fill(int l, int r) // [l, r]
    {
        auto it = Get(l+1);
        if (it == segs.begin())
            it = segs.end();
        else
        {
            --it;

            do
            {
                int l1 = it->first;
                int r1 = it->second;

                if (it != segs.begin())
                    --it;

                if (l1 <= l && r1 >= r)
                    segs.erase({l, r});
                else
                    break;
            }
            while (it != segs.end() && it != segs.begin());
        }


        it = Get(l);
        int l1 = it->first;
        int r1 = it->second;
        if (l <= l1 && r >= r1)
            return;

        segs.insert({l, r});
    }

    void Print()
    {
        std::cout << "struct 'Not Overlaping Small Segments' debug\n";
        std::cout << "size: " << segs.size() << '\n';
        for (auto it = segs.begin(); it != segs.end(); ++it)
            std::cout << " [" << it->first << " - " << it->second << "]\n";
        std::cout << std::endl;
    }
};
