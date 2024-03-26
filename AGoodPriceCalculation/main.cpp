#include <iostream>

int main()
{
    double N{};
    double A{};
    double B{};
    double X{};
    double Y{};
    std::cin >> N >> A >> B >> X >> Y;
    if (N > B) {
        std::cout << (N * (1 - Y / 100));
    }
    else if (N > A) {
        std::cout << (N * (1 - X / 100));
    }
    else
    {
        std::cout << N;
    }
    return 0;
}