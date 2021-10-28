#include <vector>

template <typename T>
class PrefixSums
{
    std::vector<T> prefixSums;

public:

    PrefixSums(const std::vector<T>& arr)
    {
        const int sz = arr.size();
        prefixSums.resize(sz+1);
        prefixSums[0] = 0;
        for (int i = 1; i <= sz; ++i)
        {
            prefixSums[i] = prefixSums[i-1] + arr[i-1];
        }
    }

    inline T getFromTo(int l, int r)
    {
        return prefixSums[r+1] - prefixSums[l];
    }
};
