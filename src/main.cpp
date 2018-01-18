#include <iostream>

#include "PrimeNumberGenerator.h"
#include "Xml.h"
#include "Utils.h"

int main()
{
    using namespace red;

    try
    {
        xml::File file("simple.xml");
        xml::Document document(file.GetContents());
        auto xmlIntervals = document.GetRoot()
                                .GetFirstChild("root")
                                ->GetFirstChild("intervals")
                                ->GetChildren("interval");
        std::vector<PrimeNumberGenerator::Interval> intervals;
        for (const auto* xmlInterval : xmlIntervals)
        {
            int low = xmlInterval->GetFirstChild("low")->GetValue().ToInt();
            int high = xmlInterval->GetFirstChild("high")->GetValue().ToInt();
            intervals.emplace_back(low, high);
        }

        PrimeNumberGenerator generator(intervals);
        auto primes = generator.Calculate();

        auto primesTag = std::make_shared<xml::Tag>("primes", xml::Value(Join(primes, ' ')));
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
