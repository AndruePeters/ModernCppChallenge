/// STL libraries
#include <array>
#include <map>
#include <numeric>

/// Third party libraries
#include <docopt/docopt.h>
#include <fmt/core.h>

/// Help message
static const char USAGE[] =
        R"(Modern C++ Challenge: Chapter 1 -- Problem 2

    Usage:
      c1_p2 <PosInt1> <PosInt2>
)";

int main(int argc, char **argv) {
    using ull = unsigned long long;
    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             {argv + 1, argv + argc},
                             true,               // show help if requested
                             "1.0");  // version string

    const ull posInt1 = static_cast<ull>(args["<PosInt1>"].asLong());
    const ull posInt2 = static_cast<ull>(args["<PosInt2>"].asLong());
    const ull gcd = std::gcd(posInt1, posInt2);

    fmt::print("GCD({}, {}) = {}\n", posInt1, posInt2, gcd);
    return 0;
}