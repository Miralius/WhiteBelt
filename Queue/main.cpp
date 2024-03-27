#include <iostream>
#include <vector>
#include <algorithm>

void setWorry(std::vector<bool>& vector, const size_t index)
{
    vector.at(index) = true;
}

void setQuiet(std::vector<bool>& vector, const size_t index)
{
    vector.at(index) = false;
}

void addPeople(std::vector<bool>& vector, const int64_t number)
{
    for (int64_t i{}; i < number; i++)
    {
        vector.emplace_back(false);
    }
}

void deletePeople(std::vector<bool>& vector, const int64_t number)
{
    for (int64_t i{}; i < std::abs(number); i++)
    {
        vector.pop_back();
    }
}

size_t worryCount(const std::vector<bool>& vector)
{
    return std::count(vector.cbegin(), vector.cend(), true);
}

int main()
{
    size_t operationNumber{};
    std::cin >> operationNumber;
    std::vector<bool> peopleQueue;
    std::vector<size_t> worryCountVector;
    for (size_t i{}; i < operationNumber; i++)
    {
        std::string operationName;
        std::cin >> operationName;
        if (operationName == "WORRY")
        {
            size_t personIndex{};
            std::cin >> personIndex;
            setWorry(peopleQueue, personIndex);
        }
        else if (operationName == "QUIET")
        {
            size_t personIndex{};
            std::cin >> personIndex;
            setQuiet(peopleQueue, personIndex);
        }
        else if (operationName == "COME")
        {
            int64_t personNumber{};
            std::cin >> personNumber;
            if (personNumber > 0)
            {
                addPeople(peopleQueue, personNumber);
            }
            else
            {
                deletePeople(peopleQueue, personNumber);
            }
        }
        else if (operationName == "WORRY_COUNT")
        {
            worryCountVector.emplace_back(worryCount(peopleQueue));
        }
    }
    std::for_each(worryCountVector.cbegin(), worryCountVector.cend(),
                  [](const auto& value)
                  {
                      std::cout << value << '\n';
                  }
    );

    return EXIT_SUCCESS;
}