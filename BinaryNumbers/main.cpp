#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int A{};
    vector<int> bin_A;

    cin >> A;

    while (A != 0) {
        bin_A.push_back(A % 2);
        A /= 2;
    }

    for (int i = static_cast<int>(bin_A.size()) - 1; i >= 0; --i) {
        cout << bin_A[i];
    }

    return 0;
}