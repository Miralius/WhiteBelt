#include <iostream>

using namespace std;

class Rational {
public:
    Rational()
            : _numerator(0), _denominator(1) {
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
        }
        if (numerator == 0) {
            _numerator = 0;
            _denominator = 1;
            return;
        }
        auto GCD = getGreatestCommonDivisor(numerator, denominator);
        _numerator = numerator / GCD;
        _denominator = denominator / GCD;
        if (_denominator < 0) {
            _numerator = -_numerator;
            _denominator = -_denominator;
        }
    }

    [[nodiscard]] int Numerator() const {
        return _numerator;
    }

    [[nodiscard]] int Denominator() const {
        return _denominator;
    }

private:
    static int getGreatestCommonDivisor(int lhs, int rhs) {
        // Euclid's algorithm
        lhs = std::abs(lhs);
        rhs = std::abs(rhs);
        while (lhs > 0 and rhs > 0) {
            if (lhs > rhs) {
                lhs %= rhs;
            } else {
                rhs %= lhs;
            }
        }
        return lhs + rhs;
    }

    int _numerator{};
    int _denominator{};
};

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.Numerator() == rhs.Numerator() and lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Numerator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    return {lhs.Numerator() * rhs.Denominator(),
            lhs.Denominator() * rhs.Numerator()};
}

std::ostream &operator<<(std::ostream &out, const Rational &obj) {
    out << obj.Numerator() << '/' << obj.Denominator();
    return out;
}

std::istream &operator>>(std::istream &in, Rational &obj) {
    int num;
    int den;
    in >> num;
    in.ignore(1);
    in >> den;
    if (!in) {
        return in;
    }
    obj = Rational(num, den);
    return in;
}

int main() {
    Rational lhs;
    Rational rhs;
    char operation;
    try {
        cin >> lhs >> operation >> rhs;
        if (operation == '+') {
            cout << lhs + rhs;
        } else if (operation == '-') {
            cout << lhs - rhs;
        } else if (operation == '*') {
            cout << lhs * rhs;
        } else if (operation == '/') {
            cout << lhs / rhs;
        }
    } catch (invalid_argument &ex) {
        cout << ex.what();
    }
    catch (domain_error &ex) {
        cout << ex.what();
    }
    return 0;
}
