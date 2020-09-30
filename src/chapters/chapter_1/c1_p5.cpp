/// Library Includes
#include <prime.h>

/// STL libraries
#include <map>
#include <numeric>
#include <vector>

/// Third party libraries
#include <docopt/docopt.h>
#include <fmt/core.h>

/// Help message
static const char USAGE[] =
  R"(Modern C++ Challenge: Chapter 1 -- Problem 5

    Usage:
      c1_p5 <PosUpperBound>
)";

/// Returns vector of pairs, looking for primes with a difference of \p difference
/// So, if you want the sexy primes, then difference = 6; twin primes, difference = 2
/// The input iterator should be for a container of prime numbers.
template<typename InputIt>
std::vector<std::pair<unsigned long long, unsigned long long>> find_primes_distance(InputIt begin, InputIt end, unsigned long long difference)
{
    if (std::distance(begin, end) < 2) {
        fmt::print("Container size is less than 2.\n");
    }
    std::vector<std::pair<unsigned long long, unsigned long long>> pairs;

    // there is no point to looking at the last element, so we look for n-1
    for (; begin != end-1; ++begin) {
        const unsigned long long desiredPrime = *begin + difference;
        auto it = std::find(begin, end, desiredPrime);
        if (it != end) {
            pairs.push_back( {*begin, *it} );
        }
    }
    return pairs;
}

int main(int argc, char **argv)
{
    using ull = unsigned long long;
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
      { argv + 1, argv + argc },
      true,// show help if requested
      "1.0");// version string

    const ull upperBound = static_cast<ull>(args["<PosUpperBound>"].asLong());
    std::vector<ull> primes = math::prime_sieve_eratosthenes(upperBound);
    std::sort(primes.begin(), primes.end()); /// faster time finding the primes if sorted
    const auto pairs = find_primes_distance(begin(primes), end(primes), 6);

    fmt::print("Limit: {}\n", upperBound);
    std::for_each(begin(pairs), end(pairs), [](const auto pair) {
        fmt::print("({}, {})\n", pair.first, pair.second);
    });

    return 0;
}