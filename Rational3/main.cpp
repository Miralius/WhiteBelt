#include <iostream>

using namespace std;

class Rational {
public:
    Rational()
            : _numerator(0), _denominator(1) {
    }

    Rational(int numerator, int denominator) {
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

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Numerator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator(),
            lhs.Denominator() * rhs.Numerator()};
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
