/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:05:47 by nefimov           #+#    #+#             */
/*   Updated: 2026/10/13 21:05:48 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <algorithm>
# include <stdexcept>
# include <vector>

class Span
{
  public:
	explicit Span(unsigned int capacity);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	void addNumber(int number);

	template <typename InputIterator>
	void addNumbers(InputIterator first, InputIterator last)
	{
		const std::size_t count = static_cast<std::size_t>(
			std::distance(first, last));
		if (count > _capacity - _numbers.size())
			throw std::overflow_error("Span capacity exceeded");
		_numbers.insert(_numbers.end(), first, last);
	}

	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

  private:
	std::vector<int> _numbers;
	unsigned int _capacity;
};

#endif
