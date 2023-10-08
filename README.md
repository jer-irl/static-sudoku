# Static Sudoku Solver

C++ template metaprogramming has been notoriously Turing-complete since before C++98, and modern ISO C++ standards have increasingly leaned in to compile-time programming, adding paradigms and syntax for making it more viable for practical software needs.

One of the critical constraints inherent to compile-time programming is that to perform computation at compile-time, any needed input data is also required to be present at compile-time.  I currently lean toward compile-time computation only for readability in generating small constant variables.  More involved computation that can be done at compile-time can reasonably be done in an external code generator, like generating a header with a Python script (or generating a source file with definitions for globals defined `extern` to avoid there being a compile-time dependency on generated files -- nice for clangd etc, and ideally free with LTO).

```C++
// C++20
#include <concepts>

consteval auto simple_exp(std::integral auto n, std::unsigned_integral auto&& exponent) -> decltype(n)
{
  auto result = 1;
  for (auto i = 0; i < exponent; ++i) {
    result *= n;
  }
  return result;
}

// A reasonable use of compile-time programming in my opinion
constexpr static auto MAX_SIDE_LEN = 5;
constexpr static auto MAX_VOLUME = simple_exp(MAX_SIDE_LEN, 3u);
```

In my experience, a more frequently useful application of compile-time utilities is to compose object interfaces or closely control object layouts.  C++17 made much of this simpler with fold expressions, and C++23 "deducing `this`" will make CRTP patterns more ergonomic in many cases.

SFINAE and C++20 constraints+concepts are also useful tools, but still run the risk of making code difficult for humans to statically reason about.  I'm a big fan of Rust and nominally typed traits generally, and I think C++20 constraints and concepts are a pretty flawed iteration in the right direction.

## Sudoku as a toy problem

When starthing this exercise I didn't do much research on actual algorithms to solve sudoku puzzles, and instead dove in with a naive brute-force DFS + backtracking sort of approach.  It turns out this can be computationally expensive, and often different formulations and heuristics can be drastically more effective.  I'm interested in someday making a bot for an open-information board game like Azul, and traversing game theoretic decision trees has some aspects in common with solving sudoku puzzles.  I'm not especially motivated to iterate on the actual solving algorithm for this exercise.

## Status

I had planned to demonstrate several compile-time techniques for solving a sudoku puzzele, but currently there is only one implementation.

### `constepxr` imperative and object-oriented brute force

The existing implementation is a simple brute force approach which works when compiled and run dynamically, but hits compiler limitations when executed at compile-time.  There are ways to improve the algorithm, but there are some fundamental challenges that need addressing.

At the time I did this project, Clang executed constepxr code at compile time by traversing the AST much like a human might compute constexpr results mentally.  My understanding is that since then, Clang has moved to a method much more like how dynamic languages are executed by an interpreter.  Clang will traverse the AST, and compile functions into bytecode which can be used for more efficient computation.

Regardless of the method of compile-time evaluation, Clang will halt its evalution when it hits configurable limits [described in the "Controlling Implementation Limits" section of the docs](https://clang.llvm.org/docs/UsersManual.html#controlling-implementation-limits)

The current brute force evaluation hits these limits, and at the time I didn't pursue tuning and tweaking the implementation or configuration enough to properly demonstrate the result.

### Old-school "functional" TMP

The second implementation I had planned was to use template expansion in a sort of "old-school" way with a functional feel.  Where I've seen this used, iteration is done similarly to how you might do it in a functional language with recursion, but with conditions checked with partial template specialization.  I imagine this would be very expensive for a compiler to evaluate, and of course conditionals can also be evaluated more simply now with constant expressions.

It might look something like this (C++98)

```C++
template <int X, int Div=2, int Remainder = X % Div>
struct IsPrime;

template <int X>
struct IsPrime<X, X, 0>
{
    static const bool result = true;
};

template <int X, int Div>
struct IsPrime<X, Div, 0>
{
    static const bool result = false;
};


template <int X, int Div, int R>
struct IsPrime
{
    static const bool result = IsPrime<X, Div + 1>::result;
};

template <int NthToFind, int Current=2, bool Prime = IsPrime<Current>::result>
struct FindNthPrime;

template <int Current>
struct FindNthPrime<1, Current, true>
{
    static const int result = Current;
};

template <int NthToFind, int Current>
struct FindNthPrime<NthToFind, Current, true>
{
    static const int result = FindNthPrime<NthToFind - 1, Current + 1>::result;
};

template <int NthToFind, int Current>
struct FindNthPrime<NthToFind, Current, false>
{
    static const int result = FindNthPrime<NthToFind, Current + 1>::result;
};

int main()
{
    // Returns 229
    return FindNthPrime<50>::result;
}
```
