#include <iostream>
#include <string>
#include <vector>

struct Student
{
    std::string firstName;
    std::string lastName;
    unsigned dayBirth;
    unsigned monthBirth;
    unsigned yearBirth;
};

int main()
{
    std::vector<Student> students;

    unsigned short N;
    std::cin >> N;

    for (unsigned short i = 0; i < N; ++i)
    {
        std::string firstName;
        std::string lastName;
        unsigned dayBirth;
        unsigned monthBirth;
        unsigned yearBirth;
        std::cin >> firstName >> lastName >> dayBirth >> monthBirth >> yearBirth;
        students.push_back({firstName, lastName, dayBirth, monthBirth, yearBirth});
    }

    unsigned short M;
    std::cin >> M;

    for (unsigned short i = 0; i < M; ++i)
    {
        std::string request;
        unsigned K;
        std::cin >> request >> K;
        if (K >= 1 and K <= 10000 and K <= students.size() and (request == "name" or request == "date"))
        {
            const auto& student = students.at(K - 1);
            if (request == "name")
            {
                std::cout << student.firstName << ' ' << student.lastName << '\n';
            }
            else
            {
                std::cout << student.dayBirth << '.' << student.monthBirth << '.' << student.yearBirth << '\n';
            }
        }
        else
        {
            std::cout << "bad request\n";
        }
    }

    return 0;
}