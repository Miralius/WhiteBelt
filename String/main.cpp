#include <string>
#include <algorithm>
#include <iostream>

class ReversibleString
{
public:
    ReversibleString() = default;

    ReversibleString(const std::string& str)
            : _str(str)
    {}

    void Reverse()
    {
        std::reverse(_str.begin(), _str.end());
    }

    [[nodiscard]] std::string ToString() const
    {
        return _str;
    }

private:
    std::string _str;
};

using namespace std;

int main() {
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;

    s.Reverse();
    const ReversibleString& s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;

    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}