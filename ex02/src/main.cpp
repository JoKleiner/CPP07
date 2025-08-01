/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:49:50 by joklein           #+#    #+#             */
/*   Updated: 2025/08/01 15:49:18 by joklein          ###   ########.fr       */
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
			return (std::cerr << e.what() << std::endl, 1);
		}
	}
	return (0);
}

void print_vec(std::vector<int> vec)
{
	for (size_t v = 0; v < vec.size(); v++)
		std::cout << " " << vec[v] ;
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	if (argc <= 1)
		return (std::cerr << "Error: number of arguments incorrect" << std::endl, 1);
	if (input_check(argv))
		return (1);
	std::vector<int> vec;	
	for(size_t i = 1; argv[i]; i++)
		vec.push_back(std::stoi(argv[i]));
	
	std::cout << CYAN << BOLD << "Before:\t" << RESET;
	print_vec(vec);
	
	auto start = std::chrono::high_resolution_clock::now();
	vec = pmm_sort<std::vector<int>>(argv);
	auto end = std::chrono::high_resolution_clock::now();
	double duration = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1000;
	
	std::cout << CYAN << BOLD << "After:\t" << RESET;
	print_vec(vec);
	std::cout << "Time to process a range of: " << argc - 1 << " elements with " << YELLOW << BOLD << "std::vector: " << GREEN << duration << RESET << " us\n";

	start = std::chrono::high_resolution_clock::now();
	pmm_sort<std::deque<int>>(argv);
	end = std::chrono::high_resolution_clock::now();
	duration = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1000;
	std::cout << "Time to process a range of: " << argc - 1 << " elements with " << YELLOW << BOLD << "std::deque:  " << GREEN<< duration << RESET << " us\n";
}
