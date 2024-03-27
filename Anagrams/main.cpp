#include <iostream>
#include <string>
#include <map>

std::map<char, unsigned> BuildCharCounters(std::string&& word)
{
    std::map<char, unsigned> result;

    for (const auto letter : word)
    {
        result[letter]++;
    }

    return result;
}

int main()
{
    size_t count{};
    std::cin >> count;

    for (size_t i = 0; i < count; ++i)
    {
        std::string firstWord{};
        std::string secondWord{};
        std::cin >> firstWord >> secondWord;
        if (firstWord.size() == secondWord.size() &&
            BuildCharCounters(std::move(firstWord)) == BuildCharCounters(std::move(secondWord)))
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return EXIT_SUCCESS;
}