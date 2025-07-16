/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:59:24 by joklein           #+#    #+#             */
/*   Updated: 2025/07/16 15:32:19 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T>
class Array
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

// template <typename T>
// class Array
// {
//     public:
//         Array() : m_size(0) {
// 			this->m_array = new T[this->m_size];  };
            
//         Array(unsigned int n) : m_size(n) {
//             this->m_array = new T[this->m_size];  };

//         Array(const Array &other) : m_size(other.m_size) {
//             this->m_array = NULL;
// 			*this = other;  };
        
//         Array &operator=(const Array &other) {
//             if(this == &other)
//                 return(*this);
//             delete[] this->m_array;
//             this->m_size = other.m_size;
//             this->m_array = new T[this->m_size];
//             for(unsigned int i = 0; i < this->m_size; i++)
//                 this->m_array[i] = other.m_array[i];
//             return(*this);  };
        
//         ~Array() {
//             if(this->m_array != NULL)
//                 delete[] this->m_array;  };

//         T& operator[](unsigned int index) {
//             if (index >= m_size)
//                 throw OutOfBounds();
//             return m_array[index];  };
        
//         class OutOfBounds : public std::exception
//         {
//             public:
//                 const char *what() const noexcept override {
//                     return ("Index out of bounds!");  };
//         };

//         unsigned int size() {
//                 return(this->m_size);  };
            
//     private:
//         T               *m_array;
//         unsigned int    m_size;

// };

// #endif
