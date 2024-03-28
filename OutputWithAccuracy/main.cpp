#include <fstream>
#include <iostream>
#include <iomanip>

int main()
{
    std::ifstream input("input.txt");
    double number;
    while (!input.eof())
    {
        input >> number;
        std::cout << std::fixed << std::setprecision(3) << number << '\n';
    }
    return 0;
}