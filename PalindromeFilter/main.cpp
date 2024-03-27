#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

bool IsPalindrom(const std::string& word)
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

std::vector<std::string> PalindromFilter(const std::vector<std::string>& words, int minLength)
{
    std::vector<std::string> filteredPalindromes{};
    for (const auto& word : words)
    {
        if (word.size() >= minLength && IsPalindrom(word))
        {
            filteredPalindromes.emplace_back(word);
        }
    }
    return filteredPalindromes;
}

int main()
{
    std::string word(" ");
    std::vector<std::string> words;
    words.reserve(100);

    int minLength;
    std::cin >> minLength;

    while(word != ".")
    {
        std::cin >> word;
        words.push_back(word);
    }

    for (const auto& palindrome : PalindromFilter(words, minLength))
    {
        std::cout << palindrome << ", ";
    }

    return 0;
}