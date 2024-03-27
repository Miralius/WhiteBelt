#include <iostream>
#include "MapValueSet.h"

int main() {
    set<string> values = BuildMapValuesSet({
                                                   {1, "odd"},
                                                   {2, "even"},
                                                   {3, "odd"},
                                                   {4, "even"},
                                                   {5, "odd"}
                                           });

    for (const string &value: values) {
        cout << value << endl;
    }
    return 0;
}