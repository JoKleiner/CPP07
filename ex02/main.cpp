/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:43:22 by joklein           #+#    #+#             */
/*   Updated: 2025/07/16 15:44:03 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main()
{
    int *a = new int();
    // a[0] = 42;
    std::cout << a[0] << std::endl;

    delete a;

    Array<int> b(5);
    try{
        b[0] = 0;
        b[1] = 1;
        b[2] = 2;
        b[3] = 3;
        b[4] = 4;
        b[5] = 5;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    
    Array<int> c = b;
    std::cout << "b" << b[0] << b[1] << b[2] << b[3] << b[4];
    std::cout << "\nc" << c[0] << c[1] << c[2] << c[3] << c[4] << std::endl;
}
