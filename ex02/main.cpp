/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:43:22 by joklein           #+#    #+#             */
/*   Updated: 2025/07/10 17:08:26 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main()
{
    int * a = new int();
    a[0] = 42;
    std::cout << a[0] << std::endl;

    Array<int> b(5);
    try{
        b[0] = 10;
        std::cout << b[0] << std::endl;
        b[6] = 20;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
