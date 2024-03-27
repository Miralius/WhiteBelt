#include <vector>
#include <algorithm>

using namespace std;

class FunctionPart
{
public:
    FunctionPart(char operation, double value)
            : operation(operation)
            , value(value)
    {}

    [[nodiscard]] double ApplyPart(double new_value) const
    {
        if (operation == '+')
        {
            return new_value + value;
        }
        else
        {
            return new_value - value;
        }
    }

    void InvertPart()
    {
        if (operation == '+')
        {
            operation = '-';
        }
        else
        {
            operation = '+';
        }
    }
private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart(char operation, double value)
    {
        parts.emplace_back(operation, value);
    }
    [[nodiscard]] double Apply(double value) const
    {
        for (const auto& part : parts)
        {
            value = part.ApplyPart(value);
        }
        return value;
    }
    void Invert()
    {
        for (auto& part: parts)
        {
            part.InvertPart();
        }
        reverse(parts.begin(), parts.end());
    }
private:
    vector<FunctionPart> parts;
};

