/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:05:17 by nefimov           #+#    #+#             */
/*   Updated: 2026/10/15 16:03:33 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

static bool reportTest(const char *name, bool passed)
{
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] "
        << name << std::endl;
    return passed;
}

static bool testExerciseExample()
{
    Span span(5);
    span.addNumber(-2);
    span.addNumber(9);
    span.addNumber(17);
    span.addNumber(0);
    span.addNumber(11);
    return span.shortestSpan() == 2 && span.longestSpan() == 19;
}

static bool testCapacityLimit()
{
    Span span(2);
    span.addNumber(1);
    span.addNumber(2);
    try
    {
        span.addNumber(3);
    }
    catch (const std::overflow_error &)
    {
        return true;
    }
    return false;
}

static bool testInsufficientNumbers()
{
    Span empty(2);
    try
    {
        empty.shortestSpan();
        return false;
    }
    catch (const std::runtime_error &)
    {
    }

    empty.addNumber(42);
    try
    {
        empty.longestSpan();
    }
    catch (const std::runtime_error &)
    {
        return true;
    }
    return false;
}

static bool testRangeInsertion()
{
    const int values[] = {6, 3, 17, 9, 11};
    Span span(5);
    span.addNumbers(values, values + 5);
    return span.shortestSpan() == 2 && span.longestSpan() == 14;
}

static bool testRangeInsertionIsAtomic()
{
    const int values[] = {1, 2, 3};
    Span span(2);
    try
    {
        span.addNumbers(values, values + 3);
    }
    catch (const std::overflow_error &)
    {
    }
    try
    {
        span.shortestSpan();
    }
    catch (const std::runtime_error &)
    {
        return true;
    }
    return false;
}

static bool testLargeInput()
{
    std::vector<int> values;
    for (int i = 0; i < 10000; ++i)
        values.push_back(i * 3);

    Span span(10000);
    span.addNumbers(values.begin(), values.end());
    return span.shortestSpan() == 3 && span.longestSpan() == 29997;
}

int main()
{
    bool allTestsPassed = true;
    allTestsPassed = reportTest("matches the exercise example",
        testExerciseExample()) && allTestsPassed;
    allTestsPassed = reportTest("rejects values beyond capacity",
        testCapacityLimit()) && allTestsPassed;
    allTestsPassed = reportTest("rejects spans with fewer than two values",
        testInsufficientNumbers()) && allTestsPassed;
    allTestsPassed = reportTest("adds a range of values",
        testRangeInsertion()) && allTestsPassed;
    allTestsPassed = reportTest("keeps failed range insertion atomic",
        testRangeInsertionIsAtomic()) && allTestsPassed;
    allTestsPassed = reportTest("handles 10,000 values",
        testLargeInput()) && allTestsPassed;
    std::cout << "Summary: "
        << (allTestsPassed ? "all tests passed" : "some tests failed")
        << " (6 tests)" << std::endl;
    return allTestsPassed ? 0 : 1;
}
