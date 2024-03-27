void UpdateIfGreater(const int& a, int& b)
{
    if (a > b)
    {
        b = a;
    }
}

int main()
{
    int a = 4;
    int b = 2;
    UpdateIfGreater(a, b);

    if (b == a)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}