/// STL libraries
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

/// Third party libraries
#include <docopt/docopt.h>
#include <fmt/core.h>

/// Help message
static const char USAGE[] =
        R"(Modern C++ Challenge: Chapter 1 -- Problem 3

    Usage:
      c1_p2 <PosInt>...
)";

/// Convert vector of strings from docopt::value to vector of unsigned long longs
std::vector<unsigned long long> toULLVector(const std::vector<std::string>& stringVect)
{
    std::vector<unsigned long long> converted;
    converted.reserve(stringVect.size());

    std::transform(begin(stringVect), end(stringVect), std::back_inserter(converted), [](const auto& str) {
        return std::stoul(str);
    });

    return converted;
}

/// Calculate the least common multiple for a container
template<typename InputIt>
unsigned long long lcm(InputIt begin, InputIt end)
{
    unsigned long long lcm_= 1;
    while (begin != end) {
        lcm_ = std::lcm(lcm_, *(begin++));
    }
    return lcm_;
}


int main(int argc, char **argv) {
    using ull = unsigned long long;
    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             {argv + 1, argv + argc},
                             true,               // show help if requested
                             "1.0");  // version string

    const auto posInts = args["<PosInt>"].asStringList();
    const auto ullVector = toULLVector(posInts);
    std::ostringstream stream;
    stream << args["<PosInt>"];

    fmt::print("LCM for ({}): {}\n", stream.str(), lcm(std::begin(ullVector), std::end(ullVector)) );
    return 0;
}