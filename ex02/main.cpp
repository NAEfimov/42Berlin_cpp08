/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:13:58 by nefimov           #+#    #+#             */
/*   Updated: 2026/10/15 16:04:23 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

#include <iostream>
#include <stack>

static bool testExerciseExample()
{
    std::stack<int> a;
    std::deque<int> b;
    
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    if (mstack.top() != 17)
        return false;
    mstack.pop();
    if (mstack.size() != 1)
        return false;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    const int expected[] = {5, 3, 5, 737, 0};
    std::size_t index = 0;
    while (it != ite)
    {
        if (index >= 5 || *it != expected[index])
            return false;
        ++it;
        ++index;
    }
    return index == 5;
}

static bool testEmptyBoundaries()
{
    MutantStack<int> mstack;
    return mstack.empty() && mstack.begin() == mstack.end();
}

static bool testCopyAndAssignment()
{
    MutantStack<int> original;
    original.push(1);
    original.push(2);

    MutantStack<int> copied(original);
    MutantStack<int> assigned;
    assigned = original;
    original.top() = 3;

    return copied.top() == 2 && assigned.top() == 2;
}

static bool testStdStackCompatibility()
{
    MutantStack<int> mstack;
    mstack.push(10);
    mstack.push(20);
    std::stack<int> standardStack(mstack);
    return standardStack.size() == 2 && standardStack.top() == 20;
}

static bool reportTest(const char *name, bool passed)
{
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] "
        << name << std::endl;
    return passed;
}

int main()
{
    bool allTestsPassed = true;
    allTestsPassed = reportTest("matches the exercise example",
        testExerciseExample()) && allTestsPassed;
    allTestsPassed = reportTest("handles empty iterator boundaries",
        testEmptyBoundaries()) && allTestsPassed;
    allTestsPassed = reportTest("copies and assigns independently",
        testCopyAndAssignment()) && allTestsPassed;
    allTestsPassed = reportTest("converts to std::stack",
        testStdStackCompatibility()) && allTestsPassed;
    std::cout << "Summary: "
        << (allTestsPassed ? "all tests passed" : "some tests failed")
        << " (4 tests)" << std::endl;
    return allTestsPassed ? 0 : 1;
}
