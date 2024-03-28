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

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()};
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
