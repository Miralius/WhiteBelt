#include <iostream>
#include <string>
#include <vector>
#include <map>

using StopsConstIterator = std::vector<std::string>::const_iterator;

struct BusStops
{
    std::map<std::string /* stop */, std::vector<std::string /* bus */>> busesForStop;
    std::map<std::string /* bus */, std::vector<std::string /* stop */>> stopForBus;
};

std::vector<std::string> GetWordsFromString(std::string&& str, const char delim = ' ')
{
    std::vector<std::string> result;
    size_t begin = 0;
    for (size_t end = 0; (end = str.find(delim, end)) != std::string::npos; end++)
    {
        result.emplace_back(str.substr(begin, end - begin));
        begin = end + 1;
    }
    result.emplace_back(str.substr(begin, str.size()));
    return result;
}

void NewBus(const std::string& bus, const size_t stopCount, const StopsConstIterator& stopIt, BusStops& busStops)
{
    auto stopIterator = stopIt;
    std::vector<std::string> stopForBusVector;
    for (auto number = 0; number < stopCount; ++number)
    {
        busStops.busesForStop[*stopIterator].emplace_back(bus);
        stopForBusVector.emplace_back(*stopIterator);
        ++stopIterator;
    }
    busStops.stopForBus[bus] = std::move(stopForBusVector);
}

void BusesForStop(const std::string& stop, const BusStops& busStops)
{
    if (busStops.busesForStop.find(stop) == busStops.busesForStop.cend())
    {
        std::cout << "No stop\n";
    }
    else
    {
        for (const auto& bus : busStops.busesForStop.at(stop))
        {
            std::cout << bus << ' ';
        }
    }
    std::cout << '\n';
}

void StopForBus(const std::string& bus, const BusStops& busStops)
{
    if (busStops.stopForBus.find(bus) == busStops.stopForBus.cend())
    {
        std::cout << "No bus\n";
    }
    else
    {
        for (const auto& stop : busStops.stopForBus.at(bus))
        {
            std::cout << "Stop " << stop << ':';
            if (busStops.busesForStop.at(stop).size() > 1)
            {
                for (const auto& busOfStop : busStops.busesForStop.at(stop))
                {
                    if (busOfStop != bus)
                    {
                        std::cout << ' ' << busOfStop;
                    }
                }
            }
            else
            {
                std::cout << " no interchange";
            }
            std::cout << '\n';
        }
    }
}

void AllBuses(const BusStops& busStops)
{
    if (!busStops.stopForBus.empty())
    {
        for (const auto& [bus, stops] : busStops.stopForBus)
        {
            std::cout << "Bus " << bus << ':';
            for (const auto& stop : stops)
            {
                std::cout << ' ' << stop;
            }
            std::cout << '\n';
        }
    }
    else
    {
        std::cout << "No buses\n";
    }
}

void ProcessCommand(std::string&& command, BusStops& busStops)
{
    using namespace std::string_literals;

    const auto tokenizedCommand = GetWordsFromString(std::move(command));

    const auto& action = tokenizedCommand.front();

    if (action == "NEW_BUS"s)
    {
        const auto& bus = tokenizedCommand.at(1);
        const auto stopCount = std::stoull(tokenizedCommand.at(2));
        const auto stopIt = tokenizedCommand.cbegin() + 3;
        NewBus(bus, stopCount, stopIt, busStops);
    }
    else if (action == "BUSES_FOR_STOP"s)
    {
        const auto& stop = tokenizedCommand.at(1);
        BusesForStop(stop, busStops);
    }
    else if (action == "STOPS_FOR_BUS"s)
    {
        const auto& bus = tokenizedCommand.at(1);
        StopForBus(bus, busStops);
    }
    else if (action == "ALL_BUSES"s)
    {
        AllBuses(busStops);
    }
}

int main()
{
    size_t count;
    std::string stringCount;
    std::getline(std::cin, stringCount);
    count = std::stoull(stringCount);

    BusStops busStops;

    for (size_t i = 0; i < count; ++i)
    {
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::string command{};
        std::getline(std::cin, command);
        ProcessCommand(std::move(command), busStops);
    }

    return EXIT_SUCCESS;
}