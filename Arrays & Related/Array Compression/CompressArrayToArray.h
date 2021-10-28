#include <vector>
#include <algorithm>

inline std::vector<int> Compress(const std::vector<int>& arr)
{
    const int arraySize = arr.size();
    std::vector<std::pair<int, int>> indexedArr(arraySize);
    std::vector<int> ret(arraySize);

    for (int i = 0; i < arraySize; ++i)
        indexedArr[i] = {arr[i], i};
    sort(indexedArr.begin(), indexedArr.end());

    int curId = 0;
    for (int i = 0; i < arraySize; ++i)
    {
        ret[indexedArr[i].second] = curId;
        if (i+1 < arraySize && indexedArr[i].first != indexedArr[i+1].first)
            ++curId;
    }

    return ret;
}
