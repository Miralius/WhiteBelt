#include <vector>
#include <algorithm>

void Reverse(std::vector<int> &source) {
    std::reverse(source.begin(), source.end());
}

int main() {
    std::vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);

    if (numbers == std::vector<int>({2, 4, 3, 5, 1})) {
        return 0;
    } else {
        return 1;
    }
}