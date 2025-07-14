/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:50:51 by joklein           #+#    #+#             */
/*   Updated: 2025/07/14 14:57:28 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
Array<T>::Array() : m_size(0){
	this->m_array = new T[this->m_size];
};

template <typename T>
Array<T>::Array(unsigned int n) : m_size(n){
	this->m_array = new T[this->m_size];
};

template <typename T>
Array<T>::Array(const Array &other) : m_size(other.m_size){
	this->m_array = new T[this->m_size];
	for (unsigned int i = 0; i < this->m_size; i++)
		this->m_array[i] = other.m_array[i];
};

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &other){
	if (this == &other)
		return (*this);
	delete[] this->m_array;
	this->m_size = other.m_size;
	this->m_array = new T[this->m_size];
	for (unsigned int i = 0; i < this->m_size; i++)
		this->m_array[i] = other.m_array[i];
	return (*this);
};

template <typename T>
Array<T>::~Array(){
	if (this->m_array != NULL)
		delete[] this->m_array;
	this->m_array = NULL;
};

template <typename T>
T &Array<T>::operator[](unsigned int index){
	if (index >= m_size)
		throw std::out_of_range("Out of bounds");
	return (m_array[index]);
};

template <typename T>
unsigned int Array<T>::size() const{
	return (this->m_size);
};
