#include <set>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m)
{
    set<string> result;
    std::transform(m.begin(), m.end(), std::inserter(result, result.begin()), [](const auto& pair)
    {
        return pair.second;
    });
    return result;
}