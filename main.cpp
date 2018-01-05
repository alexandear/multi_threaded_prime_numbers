#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
int main()
{
    const size_t left = 2;
    const size_t n = 200;

    const size_t a_size = n - left + 1;
    std::vector<bool> a(a_size, true);
    std::vector<size_t> natural_numbers(a_size);
    std::iota(std::begin(natural_numbers), std::end(natural_numbers), left);

    for (size_t i = left; i < std::sqrt(n); i++)
    {
        if (a[i])
        {
            for (size_t j = i * i; j <= n; j += i)
            {
                a[j - 2] = false;
            }
        }
    }

    std::vector<size_t> prime_numbers;
    for (size_t i = 0; i < std::size(natural_numbers); i++)
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
