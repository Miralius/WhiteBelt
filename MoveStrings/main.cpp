#include <vector>
#include <string>
#include <cassert>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination)
{
    std::move(source.begin(), source.end(), std::back_inserter(destination));
    source.clear();
}

int main()
{
    std::vector<std::string> source = {"a", "b", "c"};
    std::vector<std::string> destination = {"z"};
    MoveStrings(source, destination);
    assert(source.empty());
    assert(destination.at(0) == "z");
    assert(destination.at(1) == "a");
    assert(destination.at(2) == "b");
    assert(destination.at(3) == "c");
    return 0;
}