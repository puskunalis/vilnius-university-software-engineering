#include <iostream>

void calculate(double a, double b)
{
    std::cout << a + b << std::endl;

    if (b != 0)
    {
        std::cout << a / b << std::endl;
    }
    else
    {
        std::cout << "Division by zero!" << std::endl;
    }
}
