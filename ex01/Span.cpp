/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:05:43 by nefimov           #+#    #+#             */
/*   Updated: 2026/10/15 14:58:19 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

#include <cstdlib>
#include <limits>

Span::Span(unsigned int capacity) : _numbers(), _capacity(capacity)
{
}

Span::Span(const Span &other) : _numbers(other._numbers), _capacity(other._capacity)
{
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_numbers = other._numbers;
		_capacity = other._capacity;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _capacity)
		throw std::overflow_error("Span capacity exceeded");
	_numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("not enough numbers to calculate a span");

	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	long shortest = std::numeric_limits<unsigned int>::max();
	for (std::vector<int>::const_iterator it = sorted.begin() + 1;
		 it != sorted.end(); ++it)
	{
		const long distance = static_cast<long>(
			static_cast<long>(*it) - static_cast<long>(*(it - 1)));
		if (distance < shortest)
			shortest = distance;
	}
	return static_cast<unsigned int>(shortest);
}

unsigned int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("not enough numbers to calculate a span");

	const int minimum = *std::min_element(_numbers.begin(), _numbers.end());
	const int maximum = *std::max_element(_numbers.begin(), _numbers.end());
	const long distance = static_cast<long>(
		static_cast<long>(maximum) - static_cast<long>(minimum));
	return static_cast<unsigned int>(distance);
}
