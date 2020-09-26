/// Andrue Peters
/// 9/26/2020
/// ModernC++Challenge Chapter 1, Problem 1

/// Project libraries
#include <gen_math.h>

/// STL libraries
#include <map>
#include <string>

/// Third party libraries
#include <docopt/docopt.h>
#include <fmt/core.h>

/// Help message
static const char USAGE[] =
        R"(Modern C++ Challenge: Chapter 1 -- Problem 1

    Usage:
      c1_p1 <limit>
)";

/// Returns multiple of 3 and 5 under some limit
/// Works by factoring out 3, 5, an 15
/// allowing you to use the consecutive sum formula which runs in O(1)
constexpr unsigned long long multipleOf3And5(unsigned long long upperBound) {
    using ull = unsigned long long;
    const ull mult3 = 3 * math::consecutive_sum<ull>(upperBound / 3);
    const ull mult5 = 5 * math::consecutive_sum<ull>(upperBound / 5);
    const ull mult15 = 15 * math::consecutive_sum<ull>(upperBound / 15);

    return mult3 + mult5 - mult15;
}

int main(int argc, char **argv) {
    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             {argv + 1, argv + argc},
                             true,               // show help if requested
                             "1.0");  // version string

    const unsigned long long limit = args["<limit>"].asLong();
    fmt::print("User entered: {}\nMultiple of 3 and 5 is: {}", limit, multipleOf3And5(limit));
    return 0;
}