#include <iostream>
#include <string>
#include <set>

int main()
{
    size_t count;
    std::cin >> count;
    std::set<std::string> lines;

    for (size_t i = 0; i < count; ++i)
    {
        std::string line;
        std::cin >> line;
        lines.insert(line);
    }
    std::cout << lines.size();

    return EXIT_SUCCESS;
}