/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:35:37 by joklein           #+#    #+#             */
/*   Updated: 2025/07/25 10:49:42 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

int rpn_process(std::string arg)
{
	double result;
	double h_value;
	std::stack<int> m_stack;
	
	for (size_t i = 0; i < arg.size(); i += 2)
	{
		if (isdigit(arg[i]))
		{
			m_stack.push(arg[i] - '0');
			continue;
		}
		if (m_stack.size() < 2)
			return (std::cerr << RED << "Error" << RESET << std::endl, 1);
		h_value = m_stack.top();
		m_stack.pop();
		result = m_stack.top();
		m_stack.pop();
		switch (arg[i])
		{
			case ('-'):
				result -= h_value;
				break;
			case ('+'):
				result += h_value;
				break;
			case ('*'):
				result *= h_value;
				break;
			case ('/'):
				if (h_value == 0)
					return (std::cerr << RED << "Error: divided by '0'" << RESET << std::endl, 1);
				result /= h_value;		
		}
		if (result > std::numeric_limits<int>::max())
			return (std::cerr << RED << "Error: int max overflow" << RESET << std::endl, 1);
		if (result < std::numeric_limits<int>::min())
			return (std::cerr << RED << "Error: int min overflow" << RESET << std::endl, 1);
		m_stack.push(result);
	}
	result = m_stack.top();
	return (std::cout << int(result) << std::endl, 0);
}
