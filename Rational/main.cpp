#include <iostream>

using namespace std;

class Rational {
public:
    Rational()
            : _numerator(0), _denominator(1) {
    }

    Rational(int numerator, int denominator) {
        if (numerator == 0)
        {
            _numerator = 0;
            _denominator = 1;
            return;
        }
        int GCD = getGreatestCommonDivisor(std::abs(numerator), std::abs(denominator));
        _numerator = numerator / GCD;
        _denominator = denominator / GCD;
        if (_denominator < 0)
        {
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
    static int getGreatestCommonDivisor(int first, int second)
    {
        // Euclid's algorithm
        while (first > 0 and second > 0) {
            if (first > second) {
                first %= second;
            } else {
                second %= first;
            }
        }
        return first + second;
    }
    int _numerator;
    int _denominator;
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "UnreachableCode"
int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
#pragma clang diagnostic pop