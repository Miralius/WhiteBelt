#include <fstream>
#include <iostream>
#include <iomanip>

int main()
{
    std::ifstream input("input.txt");
    size_t N;
    size_t M;
    input >> N >> M;
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            int number;
            input >> number;
            input.ignore(1);
            std::cout << std::setw(10) << number;
            if (j < M - 1) std::cout << ' ';
        }
        if (i < N - 1) std::cout << '\n';
    }
    return 0;
}