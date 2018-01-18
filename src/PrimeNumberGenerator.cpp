#include "PrimeNumberGenerator.h"

#include <cmath>
#include <stdexcept>
#include <iostream>

namespace red
{
PrimeNumberGenerator::PrimeNumberGenerator(std::vector<Interval> intervals) : m_intervals(std::move(intervals))
{
}

std::set<std::size_t> PrimeNumberGenerator::Calculate()
{
    m_generatedNumbers.Clear();
    std::vector<std::thread> threads;
    for (auto interval : m_intervals)
        threads.emplace_back([&] { GenerateIntoSharedContainer(interval); });

    for (auto& th : threads)
        th.join();

    const auto& generatedNumbers = m_generatedNumbers.GetData();
    std::set<std::size_t> uniquePrimeNumbers(std::begin(generatedNumbers), std::end(generatedNumbers));
    return uniquePrimeNumbers;;
}

void PrimeNumberGenerator::GenerateIntoSharedContainer(Interval interval)
{
    try
    {
        auto numbers = Generate(interval.first, interval.second);
        for (auto number : numbers)
            m_generatedNumbers.PushBack(number);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "std::invalid_argument: " << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "std::exception: " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "unknown exception\n";
    }
}

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
std::vector<std::size_t> PrimeNumberGenerator::Generate(std::size_t low, std::size_t high)
{
    if (high > MaxN || low > high || low < 2)
        throw std::invalid_argument("high > MaxN or low > high or low < 2");

    std::vector<bool> a(high + 1, true);
    for (std::size_t i = 2; i <= std::sqrt(high); i++)
    {
        if (a[i])
        {
            for (std::size_t j = i * i; j <= high; j += i)
                a[j] = false;
        }
    }

    std::vector<size_t> result;
    for (std::size_t i = low; i < std::size(a); i++)
    {
        if (a[i])
            result.push_back(i);
    }

    return result;
}
} // namespace red
