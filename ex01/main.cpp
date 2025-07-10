/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:49:35 by joklein           #+#    #+#             */
/*   Updated: 2025/07/10 10:54:48 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

void	put_str(std::string const &c){
    std::cout << c << std::endl;
}

void	print_int(int const &n){
    std::cout << n << std::endl;
}

int	main(void)
{
    std::cout << "Testing with string:" << std::endl;
    std::string array[] = {"Hello", "World", "klo"};
    iter(array, sizeof(array) / sizeof(array[0]), put_str);

    std::cout << "\nTesting with const string:" << std::endl;
    const std::string const_array[] = {"Hello", "World", "klo"};
    iter(const_array, sizeof(const_array) / sizeof(const_array[0]), put_str);


    std::cout << "\nTesting with int array:" << std::endl;
    int int_array[] = {1, 2, 3, 4, 5};
    iter(int_array, sizeof(int_array) / sizeof(int_array[0]), print_int);
	
	std::cout << "\nTesting with const int array:" << std::endl;
    const int const_int_array[] = {1, 2, 3, 4, 5};
    iter(const_int_array, sizeof(const_int_array) / sizeof(const_int_array[0]), print_int);
}
