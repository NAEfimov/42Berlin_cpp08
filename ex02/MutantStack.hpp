/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:14:04 by nefimov           #+#    #+#             */
/*   Updated: 2026/10/15 16:04:30 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
  public:
    typedef typename std::stack<T>::container_type::iterator iterator;

    MutantStack() : std::stack<T>() {}

    MutantStack(const MutantStack &other) : std::stack<T>(other) {}

    MutantStack &operator=(const MutantStack &other)
    {
        std::stack<T>::operator=(other);
        return *this;
    }

    ~MutantStack() {}

    iterator begin()
    {
        return this->c.begin();
    }

    iterator end()
    {
        return this->c.end();
    }
};

#endif
