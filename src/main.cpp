#include <iostream>
#include <thread>
#include <mutex>
#include <set>

#include "PrimeNumberGenerator.h"
#include "Xml.h"
#include "Utils.h"

using namespace red;

std::recursive_mutex mutex;
std::vector<std::size_t> sharedContainer;

void Generate(std::size_t low, std::size_t high)
{
    try
    {
        auto numbers = PrimeNumberGenerator::Generate(low, high);
        for (auto number : numbers)
        {
            std::lock_guard<std::recursive_mutex> lock(mutex);
            sharedContainer.push_back(number);
        }
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

int main()
{
    std::thread t1(&Generate, 200, 180500);
    std::thread t2(&Generate, 100, 130600);
    std::thread t3(&Generate, 200, 180500);
    std::thread t4(&Generate, 100, 130600);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    std::set<std::size_t> uniquePrimeNumbers(std::begin(sharedContainer), std::end(sharedContainer));
    for (auto prime : sharedContainer)
    {
        std::cout << prime << ' ';
    }
    std::cout << '\n';

    try
    {
        xml::File file("simple.xml");
        xml::Document document(file.GetContents());
        auto intervals = document.GetRoot()
                             .GetFirstChild("root")
                             ->GetFirstChild("intervals")
                             ->GetChildren("interval");
        for (const auto* interval : intervals)
        {
            std::cout << "low: " << interval->GetFirstChild("low")->GetValue().ToInt()
                      << " high: " << interval->GetFirstChild("high")->GetValue().ToInt() << '\n';
        }
        auto primesTag =
            std::make_shared<xml::Tag>("primes", xml::Value("101 103 107 149 743 751"));
        document.GetRoot().GetFirstChild("root")->AddChild(primesTag);
        document.OutputAllData(std::cout);
    }
    catch (const IfstreamException& e)
    {
        std::cerr << "IfstreamException: " << e.what() << '\n';
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
