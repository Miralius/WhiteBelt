#include <iostream>

int main()
{
    std::string a{}, b{}, c{};
    std::cin >> a >> b >> c;
    auto& minString = std::min(a, std::min(b, c));
    std::cout << minString;
    return 0;
}