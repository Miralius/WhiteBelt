#include <string>
#include <cstdint>

bool IsPalindrom(std::string word)
{
    for (uint32_t begin = 0, end = word.size() - 1;
         begin < word.size() && end > 0;
         begin++, end--)
    {
        if (word[begin] != word[end])
        {
            return false;
        }
    }
    return true;
}