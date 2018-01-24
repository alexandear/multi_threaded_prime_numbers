#include <iostream>

#include "PrimeNumberGenerator.h"
#include "Xml.h"
#include "Utils.h"

int main()
{
    using namespace red;

    try
    {
        xml::Document inDocument = xml::File::Read("in.xml");
        auto xmlIntervals = inDocument.GetRoot()
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

        std::cout << "Input XML data:\n";
        inDocument.OutputAllData(std::cout);

        PrimeNumberGenerator generator(intervals);
        auto primes = generator.Calculate();

        xml::Document outDocument;
        xml::Tag* root = outDocument.GetRoot().AddChild(std::make_shared<xml::Tag>("root"));
        root->AddChild(std::make_shared<xml::Tag>("primes", xml::Value(Join(primes, ' '))));

        std::cout << "Output XML data:\n";
        outDocument.OutputAllData(std::cout);

        xml::File::Write("out.xml", outDocument);
    }
    catch (const FstreamException& e)
    {
        std::cerr << "FstreamException: " << e.what() << '\n';
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
