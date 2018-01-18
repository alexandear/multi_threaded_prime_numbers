#include <iostream>

#include "PrimeNumberGenerator.h"
#include "Xml.h"

using namespace red;

int main()
{
    auto primeNumbers = PrimeNumberGenerator::Generate(200);
    for (auto prime : primeNumbers)
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
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "unknown exception\n";
    }
}
