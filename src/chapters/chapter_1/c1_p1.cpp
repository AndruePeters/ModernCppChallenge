#include <map>
#include <string>

#include <fmt/core.h>
#include <docopt/docopt.h>

static const char USAGE[] =
        R"(Modern C++ Challenge: Chapter 1 -- Problem 1

    Usage:
      c1_p1 <limit>
)";


template<typename Integer>
unsigned long long partial_sum(Integer upperBound)
{
    using ull = unsigned long long;
    const ull limit = upperBound - 1;
}

int main(int argc, char **argv)
{
    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                 { argv + 1, argv + argc },
                 true,               // show help if requested
                 "1.0");  // version string

    fmt::print("limit: {}\n", args["<limit>"].asString());
    fmt::print("hello world");
    return 0;
}