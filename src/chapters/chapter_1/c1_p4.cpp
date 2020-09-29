/// Library Includes
#include <prime.h>

/// STL libraries
#include <map>
#include <numeric>

/// Third party libraries
#include <docopt/docopt.h>
#include <fmt/core.h>

/// Help message
static const char USAGE[] =
        R"(Modern C++ Challenge: Chapter 1 -- Problem 4

    Usage:
      c1_p4 <PosUpperBound>
)";

int main(int argc, char **argv) {
    using ull = unsigned long long;
    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             {argv + 1, argv + argc},
                             true,               // show help if requested
                             "1.0");  // version string

    const ull upperBound = static_cast<ull>(args["<PosUpperBound>"].asLong());
    const std::vector<ull> primes = math::prime_sieve_eratosthenes(upperBound);
    fmt::print("Largest prime less than {}: {}\n", upperBound, primes.back());
    return 0;
}