#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Person {
public:
    Person(const string& firstName, const string& lastName, const int year)
            : birthYear(year)
    {
        firstNames.insert({year, firstName});
        lastNames.insert({year, lastName});
    }

    void ChangeFirstName(int year, const string &first_name) {
        if (year >= birthYear)
        {
            firstNames.insert({year, first_name});
        }
    }

    void ChangeLastName(int year, const string &last_name) {
        if (year >= birthYear)
        {
            lastNames.insert({year, last_name});
        }
    }

    [[maybe_unused]] [[nodiscard]] string GetFullName(int year) const {
        auto recentFirstName = firstNames.upper_bound(year);
        auto recentLastName = lastNames.upper_bound(year);
        if (recentFirstName != firstNames.cbegin() and recentLastName != lastNames.cbegin()) {
            return (--recentFirstName)->second + ' ' + (--recentLastName)->second;
        } else if (recentFirstName != firstNames.cbegin()) {
            return (--recentFirstName)->second + " with unknown last name";
        } else if (recentLastName != lastNames.cbegin()) {
            return (--recentLastName)->second + " with unknown first name";
        } else {
            return "No person";
        }
    }

    [[nodiscard]] string GetFullNameWithHistory(int year) const {
        auto firstNamesHistory = getNamesHistory(year, firstNames);
        auto lastNamesHistory = getNamesHistory(year, lastNames);
        if (!firstNamesHistory.empty() and !lastNamesHistory.empty()) {
            return firstNamesHistory + ' ' + lastNamesHistory;
        } else if (!firstNamesHistory.empty()) {
            return firstNamesHistory + " with unknown last name";
        } else if (!lastNamesHistory.empty()) {
            return lastNamesHistory + " with unknown first name";
        } else {
            return "No person";
        }
    }

private:
    static vector<string> getNamesHistoryVectorFromMap(const int year, const map<int, string> &names) {
        vector<string> namesVec;
        transform(reverse_iterator(names.upper_bound(year)), names.rend(), back_inserter(namesVec),
                  [](const auto &yearNamePair) {
                      return yearNamePair.second;
                  });
        const auto lastIt = unique(namesVec.begin(), namesVec.end());
        namesVec.erase(lastIt, namesVec.end());
        return namesVec;
    }

    static string getNamesHistoryStringFromVector(vector<string> &&namesVec) {
        string result;
        for (size_t i = 0; i < namesVec.size(); ++i) {
            if (i == 0) {
                result = std::move(namesVec.at(i));
            } else if (i == 1 and i == namesVec.size() - 1) {
                result += " (" + std::move(namesVec.at(i)) + ')';
            } else if (i == 1) {
                result += " (" + std::move(namesVec.at(i));
            } else if (i == namesVec.size() - 1) {
                result += ", " + std::move(namesVec.at(i)) + ')';
            } else {
                result += ", " + std::move(namesVec.at(i));
            }
        }

        return result;
    }

    static string getNamesHistory(const int year, const map<int, string> &names) {
        return getNamesHistoryStringFromVector(getNamesHistoryVectorFromMap(year, names));
    }

    int birthYear;
    map<int, string> firstNames;
    map<int, string> lastNames;
};

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}