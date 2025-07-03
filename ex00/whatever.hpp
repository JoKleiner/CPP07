/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:27:31 by joklein           #+#    #+#             */
/*   Updated: 2025/07/03 17:13:35 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

template <typename T>
void swap(T &in1, T &in2) {
    T temp = in1;
    in1 = in2;
    in2 = temp;
}

template <typename T>
T min(T in1, T in2) {
    return(in1 < in2 ? in1 : in2);
}

template <typename T>
T max(T in1, T in2) {
    return(in1 > in2 ? in1 : in2);
}

#endif
