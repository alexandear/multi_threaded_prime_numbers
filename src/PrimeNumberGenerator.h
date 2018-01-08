#include <vector>

namespace red
{
class PrimeNumberGenerator
{
public:
    static constexpr unsigned int MaxN = 10000;

    static std::vector<size_t> Generate(unsigned int n);
};
}
