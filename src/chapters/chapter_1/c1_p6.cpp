/// Library Includes
#include <gen_math.h>
#include <prime.h>

/// STL libraries
#include <algorithm>
#include <execution>
#include <map>
#include <numeric>
#include <vector>

/// Third party libraries
#include <docopt/docopt.h>
#include <fmt/core.h>

/// Help message
static const char USAGE[] =
  R"(Modern C++ Challenge: Chapter 1 -- Problem 6

    Usage:
      c1_p6 <PosUpperBound>
)";

struct AbundantNumber {
    long n;
    long abundance;
};

int main(int argc, char **argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               { argv + 1, argv + argc },
                                                               true,// show help if requested
                                                               "1.0");// version string

    const long upperBound = args["<PosUpperBound>"].asLong();
    std::vector<long> values(upperBound);
    std::iota(values.begin(), values.end(), 1);

    std::vector<AbundantNumber> abundantNumbers;
    abundantNumbers.reserve(upperBound);

    std::transform(values.begin(), values.end(), std::back_inserter(abundantNumbers),
      [](long n) -> AbundantNumber{
             return { n, math::abundance(n) };
    });

    std::for_each(std::execution::par_unseq, begin(abundantNumbers), end(abundantNumbers),
      [](const AbundantNumber& an) {
          if (an.abundance >= 2) {
              fmt::print("({}, {})\n", an.n, an.abundance);
          }
      });
    return 0;
}