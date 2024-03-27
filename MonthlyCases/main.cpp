#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<size_t> monthDayCount = {
            31, // Jan
            28, // Feb
            31, // Mar
            30, // Apr
            31, // May
            30, // Jun
            31, // Jul
            31, // Aug
            30, // Sep
            31, // Oct
            30, // Nov
            31, // Dec
    };
    auto currentMonthCountIt = monthDayCount.begin();
    std::vector<std::vector<std::string>> jobVector(*currentMonthCountIt);

    size_t operationCount{};
    std::cin >> operationCount;
    for (size_t i{}; i < operationCount; i++) {
        std::string typeJob;
        std::cin >> typeJob;
        if (typeJob == "ADD") {
            size_t dayNumber{};
            std::string jobName;
            std::cin >> dayNumber >> jobName;
            jobVector.at(dayNumber - 1).emplace_back(std::move(jobName));
        } else if (typeJob == "DUMP") {
            size_t dayNumber{};
            std::cin >> dayNumber;
            auto dayIndex = dayNumber - 1;
            std::cout << jobVector.at(dayIndex).size();
            std::for_each(jobVector.at(dayIndex).cbegin(), jobVector.at(dayIndex).cend(),
                          [](const auto &jobName) {
                              std::cout << ' ' << jobName;
                          }
            );
            std::cout << '\n';
        } else if (typeJob == "NEXT") {
            if (++currentMonthCountIt == monthDayCount.cend()) {
                currentMonthCountIt = monthDayCount.begin();
            }
            auto nextMonthDayCount = *currentMonthCountIt;
            if (nextMonthDayCount < jobVector.size()) {
                for (auto currentDayNumber = jobVector.size();
                     currentDayNumber != nextMonthDayCount; currentDayNumber--) {
                    for (auto &&job: jobVector.at(currentDayNumber - 1)) {
                        jobVector.at(nextMonthDayCount - 1).emplace_back(std::move(job));
                    }
                    jobVector.at(currentDayNumber - 1).clear();
                }
            } else {
                jobVector.resize(nextMonthDayCount);
            }
        }
    }

    return EXIT_SUCCESS;
}