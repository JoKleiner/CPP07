/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:49:50 by joklein           #+#    #+#             */
/*   Updated: 2025/08/01 12:42:08 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

int input_check(char **argv)
{
	size_t i;
	for (i = 1; argv[i]; i++)
	{
		try
		{
			int num = std::stoi(argv[i]);
			if (num < 0)
				throw(std::runtime_error("Error: a number is not positiv"));
		}
		catch (const std::exception &e)
		{
			return (std::cerr << e.what() << '\n', -1);
		}
	}
	return (0);
}

void print_before(char **argv)
{
	std::cout << "Before:\t";
	for (size_t i = 1; argv[i]; i++)
		std::cout << " " << argv[i];
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	if (argc <= 1)
		return (std::cerr << "Error: number of arguments incorrect" << std::endl, 1);
	if (input_check(argv))
		return (1);
	print_before(argv);
	vec_sort(argc, argv);
}
