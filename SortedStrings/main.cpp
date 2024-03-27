#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

class SortedStrings {
public:
    void AddString(const string& s) {
        sortedStrings.insert(s);
    }
    vector<string> GetSortedStrings() {
        return { sortedStrings.cbegin(), sortedStrings.cend() };
    }
private:
    multiset<string> sortedStrings;
};

void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    SortedStrings strings;

    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);

    strings.AddString("second");
    PrintSortedStrings(strings);

    return 0;
}