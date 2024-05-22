#include "fib.h"

#include <map>

using std::map;

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long a = 0;
    unsigned long b = 1;
    for (unsigned long i = 2; i <= n; ++i) {
        unsigned long temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    static map<unsigned long, unsigned long> memo = {
        {0, 0},
        {1, 1}
    };

    auto lookup = memo.find(n);
    if (lookup != memo.end()) {
        return lookup->second;
    } else {
        unsigned long result = memoized_fib(n - 1) + memoized_fib(n - 2);
        memo[n] = result;
        return result;
    }
}
