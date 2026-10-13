#include "easyfind.hpp"

#include <iostream>
#include <list>
#include <vector>

static void printValues(const std::vector<int> &values)
{
	std::vector<int>::const_iterator it = values.begin();
	while (it != values.end())
	{
		if (it != values.begin())
			std::cout << ", ";
		std::cout << *it;
		++it;
	}
	std::cout << std::endl;
}

static void printValues(const std::list<int> &values)
{
	std::list<int>::const_iterator it = values.begin();
	while (it != values.end())
	{
		if (it != values.begin())
			std::cout << ", ";
		std::cout << *it;
		++it;
	}
	std::cout << std::endl;
}

static bool testFirstMatch()
{
	std::vector<int> values;
	values.push_back(4);
	values.push_back(7);
	values.push_back(7);
	values.push_back(9);

	std::cout << "  Values before easyfind: ";
	printValues(values);
	std::vector<int>::iterator result = easyfind(values, 7);
	if (result != values.begin() + 1)
		return false;

	std::cout << "  First matching value: " << *result << std::endl;
	*result = 8;
	std::cout << "  Values after modifying the match: ";
	printValues(values);
	return values[1] == 8;
}

static bool testConstContainer()
{
	const std::list<int> values(2, 5);
	std::cout << "  Const container values: ";
	printValues(values);
	std::list<int>::const_iterator result = easyfind(values, 5);
	const bool foundFirstValue = result == values.begin();
	std::cout << "  First matching value: " << *result << std::endl;
	return foundFirstValue;
}

static bool testMissingValue()
{
	std::vector<int> values;
	values.push_back(1);
	values.push_back(2);

	std::cout << "  Values before easyfind: ";
	printValues(values);
	bool threwException = false;
	try
	{
		easyfind(values, 3);
	}
	catch (const std::out_of_range &e)
	{
		threwException = true;
        std::cerr << "  ERROR: " << e.what() << std::endl;
	}
	std::cout << "  Search result: "
		<< (threwException ? "value not found, exception thrown" : "unexpected match")
		<< std::endl;
	return threwException;
}

static bool reportTest(const char *name, bool passed)
{
	std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << name << std::endl;
	return passed;
}

int main()
{
	const bool firstMatchPassed = reportTest(
		"returns the first occurrence and allows modification",
		testFirstMatch());
	std::cout << std::endl;

    const bool constContainerPassed = reportTest(
		"works with const containers",
		testConstContainer());
	std::cout << std::endl;

	const bool missingValuePassed = reportTest(
		"throws when the value is not found",
		testMissingValue());
	std::cout << std::endl;

	const bool allTestsPassed = firstMatchPassed
		&& constContainerPassed
		&& missingValuePassed;

	std::cout << "Summary: " 
        << (allTestsPassed ? "all tests passed" : "some tests failed")
		<< " (3 tests)" << std::endl;
	return allTestsPassed ? 0 : 1;
}
