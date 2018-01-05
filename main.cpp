#include <iostream>
#include <vector>
#include <cmath>

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
int main()
{
    const size_t n = 200;

    std::vector<bool> a(n + 1, true);
    for (size_t i = 2; i <= std::sqrt(n); i++)
    {
        if (a[i])
        {
            for (size_t j = i * i; j <= n; j += i)
            {
                a[j] = false;
            }
        }
    }

    for (size_t i = 2; i < std::size(a); i++)
    {
        if (a[i])
        {
            std::cout << i << ' ';
        }
    }
}
