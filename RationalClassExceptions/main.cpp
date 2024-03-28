#include <iostream>

using namespace std;

class Rational {
public:
    Rational()
            : _numerator(0), _denominator(1) {
    }

    Rational(int numerator, int denominator)
            : _numerator(0), _denominator(1) {
        if (denominator == 0) {
            throw invalid_argument("");
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

    int _numerator;
    int _denominator;
};

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.Numerator() == rhs.Numerator() and lhs.Denominator() == rhs.Denominator();
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("");
    }
    return {lhs.Numerator() * rhs.Denominator(),
            lhs.Denominator() * rhs.Numerator()};
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "UnusedValue"

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument &) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error &) {
    }

    cout << "OK" << endl;
    return 0;
}

#pragma clang diagnostic pop
