#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
int Factorial(int x)
{
    if (x <= 0)
    {
        return 1;
    }
    return x * Factorial(x - 1);
}
#pragma clang diagnostic pop