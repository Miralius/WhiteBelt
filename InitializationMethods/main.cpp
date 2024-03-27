class Incognizable
{
public:
    Incognizable() = default;
    Incognizable(int) // NOLINT(*-explicit-constructor)
    {}
    Incognizable(int, int)
    {}
};

int main() {
    [[maybe_unused]] Incognizable a;
    [[maybe_unused]] Incognizable b = {};
    [[maybe_unused]] Incognizable c = {0};
    [[maybe_unused]] Incognizable d = {0, 1};
    return 0;
}