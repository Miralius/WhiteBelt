#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using Synonyms = std::map<std::string, std::set<std::string>>;

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

void Add(std::string&& firstWord, std::string&& secondWord, Synonyms& synonyms)
{
    synonyms[firstWord].insert(secondWord);
    synonyms[secondWord].insert(firstWord);
}

void Count(std::string&& word, Synonyms& synonyms)
{
    const auto result = synonyms.find(word);
    if (result != synonyms.end())
    {
        std::cout << result->second.size() << '\n';
    }
    else
    {
        std::cout << "0\n";
    }
}

void Check(std::string&& firstWord, std::string&& secondWord, Synonyms& synonyms)
{
    const auto result = synonyms.find(firstWord);
    if (result != synonyms.end())
    {
        if (result->second.find(secondWord) != result->second.end())
        {
            std::cout << "YES\n";
            return;
        }
    }
    std::cout<< "NO\n";
}

void ProcessCommand(std::string&& command, Synonyms& synonyms)
{
    using namespace std::string_literals;

    auto tokenizedCommand = GetWordsFromString(std::move(command));

    const auto& action = tokenizedCommand.front();

    if (action == "ADD"s)
    {
        Add(std::move(tokenizedCommand.at(1)), std::move(tokenizedCommand.at(2)), synonyms);
    }
    else if (action == "COUNT"s)
    {
        Count(std::move(tokenizedCommand.at(1)), synonyms);
    }
    else if (action == "CHECK"s)
    {
        Check(std::move(tokenizedCommand.at(1)), std::move(tokenizedCommand.at(2)), synonyms);
    }
}

int main()
{
    size_t count;
    std::string stringCount;
    std::getline(std::cin, stringCount);
    count = std::stoull(stringCount);

    Synonyms synonyms;

    for (size_t i = 0; i < count; ++i)
    {
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::string command{};
        std::getline(std::cin, command);
        ProcessCommand(std::move(command), synonyms);
    }

    return EXIT_SUCCESS;
}