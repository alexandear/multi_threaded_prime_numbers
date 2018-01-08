#include "PrimeNumberGenerator.h"

#include <iostream>

using namespace red;

int main()
{
    auto primeNumbers = PrimeNumberGenerator::Generate(200);
    for (auto prime : primeNumbers)
    {
        std::cout << prime << ' ';
    }
}
