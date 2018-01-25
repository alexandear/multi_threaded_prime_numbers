#include "PrimeNumberGenerator.h"

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <thread>

namespace red
{
PrimeNumberGenerator::PrimeNumberGenerator(std::vector<Interval> intervals)
    : m_intervals(std::move(intervals))
{
}

std::set<std::size_t> PrimeNumberGenerator::Calculate()
{
    m_generatedNumbers.clear();
    std::vector<std::thread> threads;
    for (auto interval : m_intervals)
        threads.emplace_back([=] { GenerateIntoSharedContainer(interval); });

    for (auto& th : threads)
        th.join();

    std::set<std::size_t> uniquePrimeNumbers(std::cbegin(m_generatedNumbers),
                                             std::cend(m_generatedNumbers));
    return uniquePrimeNumbers;
}

void PrimeNumberGenerator::GenerateIntoSharedContainer(Interval interval)
{
    try
    {
        auto numbers = Generate(interval);
        for (auto number : numbers)
            m_generatedNumbers.push_back(number);
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

std::vector<std::size_t> PrimeNumberGenerator::Generate(Interval interval)
{
    std::size_t low = interval.GetLow();
    std::size_t high = interval.GetHigh();
    if (high > MaxN || low < 2)
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

    std::vector<std::size_t> result;
    for (std::size_t i = low; i < std::size(a); i++)
    {
        if (a[i])
            result.emplace_back(i);
    }

    return result;
}
} // namespace red
