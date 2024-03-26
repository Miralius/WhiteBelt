#include <iostream>

bool isEven(int number)
{
    return !(number % 2);
}

int main()
{
    int A{};
    int B{};

    std::cin >> A >> B;

    for (auto i = A; i <= B; i++) {
        if (isEven(i)) {
            std::cout << i << ' ';
        }
    }

    return 0;
}