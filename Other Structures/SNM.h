#include <vector>


struct SNM
{
    std::vector<int> groupID;
    std::vector<std::vector<int>> group;
    std::vector<int> vls;

    SNM(int sz)
    {
        group.resize(sz);
        groupID.resize(sz);
        vls.assign(sz, 1);

        for (int i = 0; i < sz; ++i)
        {
            group[i] = {i};
            groupID[i] = i;
        }
    }

    int Get(int id)
    {
        return vls[groupID[id]];
    }

    void Merge(int id1, int id2)
    {
        id1 = groupID[id1];
        id2 = groupID[id2];

        if (id1 == id2) return;

        if (group[id1].size() < group[id2].size())
            std::swap(id1, id2);

        vls[id1] = <merge(val1, val2)>;

        for (int i = 0; i < group[id2].size(); ++i)
        {
            int nt2 = group[id2][i];
            groupID[nt2] = id1;
            group[id1].push_back(nt2);
        }

        group[id2] = std::vector<int>();
    }
};
