#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;

    std::vector<int> numbers;
    numbers.reserve(1000);
    for (size_t i = 0; i < N; ++i)
    {
        int number;
        std::cin >> number;
        numbers.push_back(number);
    }

    std::sort(numbers.begin(), numbers.end(), [](const auto first, const auto second)
    {
        return std::abs(first) < std::abs(second);
    });

    std::for_each(numbers.cbegin(), numbers.cend(), [] (const auto number)
    {
        std::cout << number << ' ';
    });

    return EXIT_SUCCESS;
}