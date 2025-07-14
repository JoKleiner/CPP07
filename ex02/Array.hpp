/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:59:24 by joklein           #+#    #+#             */
/*   Updated: 2025/07/14 15:02:01 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T> class Array
{
  public:
	Array();
	Array(unsigned int n);
	Array(const Array<T> &other);
	Array<T> &operator=(const Array<T> &other);
	~Array();

	T &operator[](unsigned int index);
	unsigned int size() const;

  private:
	T *m_array;
	unsigned int m_size;
};

#include "Array.tpp"
