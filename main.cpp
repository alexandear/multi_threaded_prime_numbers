#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
int main()
{
    const size_t left = 2;
    const size_t n = 200;

    std::vector<bool> a(n + 1, true);
    std::vector<size_t> natural_numbers(std::size(a));
    std::iota(std::begin(natural_numbers), std::end(natural_numbers), 0);

    for (size_t i = 2; i * i < n + 1; i++)
    {
        if (a[i])
        {
            for (size_t j = i * i; j < n + 1; j += i)
            {
                a[j] = false;
            }
        }
    }

    std::vector<size_t> prime_numbers;
    for (size_t i = left; i < std::size(natural_numbers); i++)
    {
        if (a[i])
        {
            prime_numbers.push_back(natural_numbers[i]);
        }
    }

    for (auto prime : prime_numbers)
    {
        std::cout << prime << ' ';
    }
    std::cout << '\n';
}
