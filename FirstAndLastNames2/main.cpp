#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string &first_name) {
        firstNames.insert({year, first_name});
    }

    void ChangeLastName(int year, const string &last_name) {
        lastNames.insert({year, last_name});
    }

    [[maybe_unused]] string GetFullName(int year) {
        auto recentFirstName = firstNames.upper_bound(year);
        auto recentLastName = lastNames.upper_bound(year);
        if (recentFirstName != firstNames.cbegin() and recentLastName != lastNames.cbegin()) {
            return (--recentFirstName)->second + ' ' + (--recentLastName)->second;
        } else if (recentFirstName != firstNames.cbegin()) {
            return (--recentFirstName)->second + " with unknown last name";
        } else if (recentLastName != lastNames.cbegin()) {
            return (--recentLastName)->second + " with unknown first name";
        } else {
            return "Incognito";
        }
    }

    string GetFullNameWithHistory(int year) {
        auto firstNamesHistory = getNamesHistory(year, firstNames);
        auto lastNamesHistory = getNamesHistory(year, lastNames);
        if (!firstNamesHistory.empty() and !lastNamesHistory.empty()) {
            return firstNamesHistory + ' ' + lastNamesHistory;
        } else if (!firstNamesHistory.empty()) {
            return firstNamesHistory + " with unknown last name";
        } else if (!lastNamesHistory.empty()) {
            return lastNamesHistory + " with unknown first name";
        } else {
            return "Incognito";
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

    map<int, string> firstNames;
    map<int, string> lastNames;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}