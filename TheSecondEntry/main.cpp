#include <iostream>

using namespace std;

int main()
{
    string word{};
    int entryCount{};

    cin >> word;

    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == 'f')
        {
            if (++entryCount == 2)
            {
                cout << i;
                break;
            }
        }
    }
    if (entryCount == 1)
    {
        cout << -1;
    }
    else if (entryCount == 0)
    {
        cout << -2;
    }

    return 0;
}