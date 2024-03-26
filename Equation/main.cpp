#include <iostream>
#include <cmath>

int main()
{
    constexpr auto epsilon = std::numeric_limits<double>::epsilon();
    double A{};
    double B{};
    double C{};
    std::cin >> A >> B >> C;
    if (std::abs(A) < epsilon)
    {
        if (std::abs(B) > epsilon)
        {
            std::cout << -C / B;
        }
        return 0;
    }
    auto D = B * B - 4 * A * C;
    if (std::abs(D) < epsilon)
    {
        std::cout << -B / (2 * A);
    }
    else if (D > 0)
    {
        auto x1 = (-B + sqrt(D)) / (2 * A);
        auto x2 = (-B - sqrt(D)) / (2 * A);
        std::cout << x1 << ' ' << x2;
    }
    return 0;
}