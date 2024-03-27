#include <string>
#include <iostream>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstNames.insert({year, first_name});
    }
    void ChangeLastName(int year, const string& last_name) {
        lastNames.insert({year, last_name});
    }
    string GetFullName(int year) {
        auto recentFirstName = firstNames.upper_bound(year);
        auto recentLastName = lastNames.upper_bound(year);
        if (recentFirstName != firstNames.cbegin() and recentLastName != lastNames.cbegin())
        {
            return (--recentFirstName)->second + ' ' + (--recentLastName)->second;
        }
        else if (recentFirstName != firstNames.cbegin())
        {
            return (--recentFirstName)->second + " with unknown last name";
        }
        else if (recentLastName != lastNames.cbegin())
        {
            return (--recentLastName)->second + " with unknown first name";
        }
        else
        {
            return "Incognito";
        }
    }
private:
    map<int, string> firstNames;
    map<int, string> lastNames;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}