#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::string line;
    while (getline(input, line))
    {
        output << line << '\n';
    }
    return 0;
}