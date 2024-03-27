#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
    size_t N{};
    std::cin >> N;
    std::vector<unsigned long long> temperatures;

    while (temperatures.size() < N)
    {
        decltype(N) temperature{};
        std::cin >> temperature;
        temperatures.emplace_back(temperature);
    }

    const auto averageTemperature =
            std::accumulate(temperatures.cbegin(), temperatures.cend(), 0ULL) / temperatures.size();

    std::cout << std::count_if(
            temperatures.cbegin(),
            temperatures.cend(),
            [averageTemperature](const auto& value)
            {
                return value > averageTemperature;
            }
    ) << '\n';

    for (size_t i = 0; i < temperatures.size(); i++)
    {
        if (temperatures.at(i) > averageTemperature)
        {
            std::cout << i << ' ';
        }
    }
    return EXIT_SUCCESS;
}