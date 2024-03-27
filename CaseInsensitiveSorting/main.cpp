#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    size_t N;
    std::cin >> N;

    std::vector<std::string> strings;
    strings.reserve(1000);
    for (size_t i = 0; i < N; ++i)
    {
        std::string str;
        str.reserve(15);
        std::cin >> str;
        strings.emplace_back(std::move(str));
    }

    const auto toLowerString = [](const auto& input)
    {
        std::string result;
        result.reserve(15);
        std::transform(input.cbegin(), input.cend(), std::back_inserter(result), [] (const auto& letter)
        {
            return std::tolower(letter);
        });
        return result;
    };
    std::sort(strings.begin(), strings.end(), [&toLowerString](const auto& first, const auto& second)
    {
        return toLowerString(first) < toLowerString(second);
    });

    std::for_each(strings.cbegin(), strings.cend(), [] (const auto& string)
    {
        std::cout << string << ' ';
    });

    return EXIT_SUCCESS;
}