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

    for (int i = 0; i < arraySize; ++i)
        ret[indexedArr[i].second] = i;

    return ret;
}
