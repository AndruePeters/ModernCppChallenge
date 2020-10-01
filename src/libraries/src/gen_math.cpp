///
/// \author Andrue Peters
/// \date 3/21/20
/// \brief Implementation of math functions

/// Library includes
#include <gen_math.h>
#include <prime.h>

/// 3rd Party Includes
#include <fmt/core.h>
#include <unsupported/Eigen/MatrixFunctions>

namespace math {


 ///
 /// \brief  Calculates the nth Fibonacci number
 /// Fast and efficient implementation to generate Fibonacci number
 ///
 /// | 1 1 | ^ n = | F(n+1)  Fn     |
 /// | 1 0 |       | F(n)    F(n-1) |
 ///
 /// This method uses 1 less calculation than needed by returning the top left element
 /// This means for F(n), I only need to exponentiate the matrix (n - 1) times
 ///
 /// Assumptions: n > 0
unsigned fibonacci(const unsigned n)
{
    using namespace Eigen;

    // Base matrix, used to multiply fibMatrix
    static const Matrix2f baseMatrix = (Matrix2f() << 1, 1, 1, 0).finished();

    // This matrix will give us the fibonacci results
    // its initial state is the same as baseMatrix
    static Matrix2f fibMatrix = baseMatrix;

    // the previous exponent multiplied by
    static unsigned lastExp = 1;

    // the number of times to multiply fibMatrix by baseMatrix
    unsigned timesToMultiply = 0;

    // case lastExp < n: since n is less than lastExp, we can make use fibMatrix's saved state
    //                   and calculate how many more times we need to multiply fibMatrix by baseMatrix
    if (lastExp < n) {
        // the -1 comes from the optimization mentioned in the description
        timesToMultiply = (n - 1) - lastExp;
    } else if (lastExp > n) {
        // if lastExp > n, then we just need to reset and start from the beginning
        fibMatrix = baseMatrix;
        timesToMultiply = n - 1;
    } else if (lastExp == n) {
        return fibMatrix(0,0);
    }

    // multiply the matrix by the base, timesToMultiply times
    // simulates exponentiating the base matrix, but saves the state
    for (unsigned i = 0; i < timesToMultiply; ++i) {
        fibMatrix = fibMatrix * baseMatrix;
    }
    
    lastExp = n-1;
    return fibMatrix(0, 0);
}

///
/// \brief A different way of calculating the nth Fibonacci number
/// Uses boost::flat_map to cache results via memoization
/// I've kept this method mostly for benchmarking and a reminder for the future.
unsigned fib_memoization(const unsigned n)
{
    static boost::container::flat_map<unsigned, unsigned> fib_map {{0, 0}, {1, 1}, {2, 1}};

    auto it = fib_map.find(n);
    if (it == fib_map.end()) {
        fib_map[n] = fib_memoization(n - 1) + fib_memoization(n - 2);
        return fib_map[n];
    } else {
        return it->second;
    }
}

/// \return Sum of the factors of \p n
long divisor_sum(long n)
{
    // retrieve all factors
    auto factors = math::prime_factorization(n);

    // for this formula, you need to remove 1 and n
    factors.erase(1);
    factors.erase(n);

    // if the size is 0 after removing 1 and n, then this is a prime number
    // so return its divisor sum which is n + 1
    if (factors.size() == 0) {
        return n + 1;
    }

    // first stage of calculating the divisor sum
    // don't know a mathematical term or good name
    auto evaluateFactor = [](std::pair<unsigned long, unsigned long> pair ) {
        return (math::pow(pair.first, pair.second+1) - 1) / (pair.first - 1);
    };

    // evaluate every factor and multiply them together
    // order does not matter
    return  std::transform_reduce(
        std::execution::par_unseq,
        factors.begin(), factors.end(),
        1ul,
        std::multiplies<>(),
        evaluateFactor
    );
}

/// \return Abundance of n
long abundance(long n)
{
    const auto divisorSum = divisor_sum(n);
    return divisorSum - 2 *n;
}

} // namespace math