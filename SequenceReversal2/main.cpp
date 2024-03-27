#include <vector>
#include <algorithm>

std::vector<int> Reversed(const std::vector<int> &v) {
    std::vector<int> result(v.size());
    std::reverse_copy(v.cbegin(), v.cend(), result.begin());
    return result;
}

int main() {
    std::vector<int> numbers = {1, 5, 3, 4, 2};

    if (Reversed(numbers) == std::vector<int>({2, 4, 3, 5, 1})) {
        return 0;
    } else {
        return 1;
    }
}