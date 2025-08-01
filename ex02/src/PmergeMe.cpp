/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:52:27 by joklein           #+#    #+#             */
/*   Updated: 2025/08/01 14:39:47 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

size_t next_jac_num(size_t jac_num_pos)
{
	if (jac_num_pos == 0)
		return (0);
	if (jac_num_pos == 1)
		return (1);

	size_t prev2 = 0;
	size_t prev1 = 1;
	size_t current = 0;
	for (size_t i = 2; i <= jac_num_pos; ++i)
	{
		current = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = current;
	}
	return (current);
}
