#include <iostream>
#include <string>
#include <vector>
#include <map>

using CapitalMap = std::map<std::string /*country*/, std::string /*capital*/>;

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

void ChangeCapital(const std::string& country, const std::string& capital, CapitalMap& capitalMap)
{
    const auto entryIt = capitalMap.find(country);
    if (entryIt == capitalMap.cend())
    {
        std::cout << "Introduce new country " + country + " with capital " + capital + '\n';
    }
    else
    {
        const auto& oldCapital = entryIt->second;
        if (entryIt->second == capital)
        {
            std::cout << "Country " + country + " hasn't changed its capital\n";
        }
        else
        {
            std::cout << "Country " + country + " has changed its capital from " + oldCapital + " to " + capital + '\n';
        }
    }
    capitalMap[country] = capital;
}

void Rename(const std::string& oldCountry, const std::string& newCountry, CapitalMap& capitalMap)
{
    const auto oldCountryEntryIt = capitalMap.find(oldCountry);
    const auto newCountryEntryIt = capitalMap.find(newCountry);
    if (oldCountryEntryIt == capitalMap.cend() ||
        newCountryEntryIt != capitalMap.cend())
    {
        std::cout << "Incorrect rename, skip\n";
    }
    else
    {
        std::string capital = oldCountryEntryIt->second;
        std::cout << "Country " + oldCountry + " with capital " + capital + " has been renamed to " + newCountry + '\n';
        capitalMap.erase(oldCountryEntryIt);
        capitalMap[newCountry] = std::move(capital);
    }
}

void About(const std::string& country, CapitalMap& capitalMap)
{
    const auto entryIt = capitalMap.find(country);
    if (entryIt != capitalMap.cend())
    {
        const auto& capital = entryIt->second;
        std::cout << "Country " + country + " has capital " + capital + '\n';
    }
    else
    {
        std::cout << "Country " + country + " doesn't exist\n";
    }
}

void Dump(CapitalMap& capitalMap)
{
    if (capitalMap.empty())
    {
        std::cout << "There are no countries in the world\n";
    }
    else
    {
        for (const auto& [country, capital] : capitalMap)
        {
            std::cout << country << '/' << capital << ' ';
        }
        std::cout << '\n';
    }
}

void ProcessCommand(std::string&& command, CapitalMap& capitalMap)
{
    using namespace std::string_literals;

    const auto tokenizedCommand = GetWordsFromString(std::move(command));

    const auto& action = tokenizedCommand.front();

    if (action == "CHANGE_CAPITAL"s)
    {
        const auto& country = tokenizedCommand.at(1);
        const auto& newCapital = tokenizedCommand.at(2);
        ChangeCapital(country, newCapital, capitalMap);
    }
    else if (action == "RENAME"s)
    {
        const auto& oldCountry = tokenizedCommand.at(1);
        const auto& newCountry = tokenizedCommand.at(2);
        Rename(oldCountry, newCountry, capitalMap);
    }
    else if (action == "ABOUT"s)
    {
        const auto& country = tokenizedCommand.at(1);
        About(country, capitalMap);
    }
    else
    {
        Dump(capitalMap);
    }
}

int main()
{
    size_t count;
    std::string stringCount;
    std::getline(std::cin, stringCount);
    count = std::stoull(stringCount);

    CapitalMap capitalMap;

    for (size_t i = 0; i < count; ++i)
    {
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::string command{};
        std::getline(std::cin, command);
        ProcessCommand(std::move(command), capitalMap);
    }

    return EXIT_SUCCESS;
}