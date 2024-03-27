#include <iostream>
#include "palindrome.h"

int main()
{
    std::string input;
    std::cin >> input;
    std::cout << std::boolalpha << IsPalindrom(input);
    return 0;
}