#include <iostream>
#include <string>
#include <vector>
#include <map>

using BusStops = std::map<std::vector<std::string>, size_t>;
using StopsConstIt = std::vector<std::string>::const_iterator;

std::vector<std::string> GetWordsFromString(std::string &&str, const char delim = ' ') {
    std::vector<std::string> result;
    size_t begin = 0;
    for (size_t end = 0; (end = str.find(delim, end)) != std::string::npos; end++) {
        result.emplace_back(str.substr(begin, end - begin));
        begin = end + 1;
    }
    result.emplace_back(str.substr(begin, str.size()));
    return result;
}

decltype(auto) PutRoute(size_t stopCount, const StopsConstIt &stopIt, BusStops &busStops) {
    return busStops.insert(
            {std::vector<std::string>(stopIt, stopIt + static_cast<long>(stopCount)), busStops.size() + 1});
}

void ProcessCommand(std::string &&command, BusStops &busStops) {
    using namespace std::string_literals;

    const auto tokenizedCommand = GetWordsFromString(std::move(command));

    const auto stopCount = std::stoull(tokenizedCommand.at(0));
    const auto stopIt = tokenizedCommand.cbegin() + 1;
    const auto result = PutRoute(stopCount, stopIt, busStops);
    if (result.second) {
        std::cout << "New bus " << result.first->second << '\n';
    } else {
        std::cout << "Already exists for " << result.first->second << '\n';
    }
}

int main() {
    size_t count;
    std::string stringCount;
    std::getline(std::cin, stringCount);
    count = std::stoull(stringCount);

    BusStops busStops;

    for (size_t i = 0; i < count; ++i) {
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::string command{};
        std::getline(std::cin, command);
        ProcessCommand(std::move(command), busStops);
    }

    return EXIT_SUCCESS;
}