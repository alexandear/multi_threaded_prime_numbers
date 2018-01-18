#include <iostream>

#include "PrimeNumberGenerator.h"
#include "Xml.h"
#include "Utils.h"

using namespace red;

int main()
{
    PrimeNumberGenerator generator({PrimeNumberGenerator::Interval{200, 300},
                                    PrimeNumberGenerator::Interval{100, 400},
                                    PrimeNumberGenerator::Interval{250, 600}});
    auto primes = generator.Calculate();
    for (auto prime : primes)
        std::cout << prime << ' ';
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
