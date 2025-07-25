/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:35:34 by joklein           #+#    #+#             */
/*   Updated: 2025/07/25 10:10:10 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

int main(int argc, char **argv)
{
	if(argc != 2)
		return(std::cerr << RED << "Error: number of arguments incorrect" << RESET << std::endl, 1);
	
	if (!std::regex_match(argv[1], std::regex("(\\d)( [\\d\\+\\-\\*\\/])*")))
		return(std::cerr << RED << "Error" << RESET << std::endl, 1);
	
	return(rpn_process(argv[1]));
}
