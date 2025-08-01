/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:50:54 by joklein           #+#    #+#             */
/*   Updated: 2025/08/01 15:43:28 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <deque>
#include <vector>

size_t next_jac_num(size_t jac_num_pos);

template <typename T>
long binary_search(size_t pair_num, int search_b_num, T a_chain_con, long idx_in_a_chain)
{
	size_t start = 0;
	size_t end = (idx_in_a_chain + 1) / pair_num - 1;
	T pair_chain;
	size_t mid;

	for (size_t i = 1; (pair_num * i) - 1 < a_chain_con.size(); i++)
		pair_chain.push_back(a_chain_con[(pair_num * i) - 1]);

	while (start <= end)
	{
		mid = start + (end - start) / 2;
		if (pair_chain[mid] > search_b_num)
		{
			if (mid == 0)
				break;
			end = mid - 1;
		}
		else
			start = mid + 1;
	}
	return (start * pair_num);
}

template <typename T>
void push_a_b_chain(T &a_chain_con, T &b_chain_con, T &a_index_con, T &b_index_con, T con, size_t pair_num)
{
	bool b_chain = true;

	for (size_t i = 0; i < con.size(); i++)
	{
		if ((i + 1) % (pair_num) == 0)
		{
			if (b_chain)
			{
				for (size_t u = i + 1 - pair_num; u < i + 1; u++)
					b_chain_con.push_back(con[u]);
				b_index_con.push_back(b_chain_con.size() - 1);
			}
			else
			{
				for (size_t u = i + 1 - pair_num; u < i + 1; u++)
					a_chain_con.push_back(con[u]);
				a_index_con.push_back(a_chain_con.size() - 1);
			}
			b_chain = !b_chain;
		}
	}
	a_chain_con.insert(a_chain_con.begin(), b_chain_con.begin(), b_chain_con.begin() + pair_num);
	for (long v = 0; v < (long)a_index_con.size(); v++)
		a_index_con[v] += pair_num;
}

template <typename T>
T con_insert(T con, size_t pair_num)
{
	T a_chain_con;
	T b_chain_con;
	T a_index_con;
	T b_index_con;
	push_a_b_chain(a_chain_con, b_chain_con, a_index_con, b_index_con, con, pair_num);

	size_t jac_num_pos = 3;
	size_t jac_num = 0;
	size_t jac_num_old = 0;
	for(; jac_num_old < b_chain_con.size(); jac_num_pos++)
	{
		jac_num_old = jac_num;
		jac_num = next_jac_num(jac_num_pos) - 1;

		for (long i = jac_num; i > (long)jac_num_old; i--)
		{
			if (b_chain_con.size() > i * pair_num)
			{
				long idx_in_a_chain = a_index_con[i - 1];
				idx_in_a_chain = binary_search(pair_num, b_chain_con[b_index_con[i]], a_chain_con, idx_in_a_chain);

				size_t idx_in_a_index = a_index_con.size();
				for (size_t multip = 0; idx_in_a_index == a_index_con.size(); multip++)
					idx_in_a_index = std::find(a_index_con.begin(), a_index_con.end(), idx_in_a_chain + (pair_num * multip) - 1) - a_index_con.begin();
					
				a_chain_con.insert(a_chain_con.begin() + idx_in_a_chain, b_chain_con.begin() + b_index_con[i] + 1 - pair_num, b_chain_con.begin() + b_index_con[i] + 1);
				for (; idx_in_a_index < a_index_con.size(); idx_in_a_index++)
					a_index_con[idx_in_a_index] += pair_num;
			}
		}
	}
	size_t left_over = con.size() % pair_num;
	a_chain_con.insert(a_chain_con.end(), con.end() - left_over, con.end());
	return (a_chain_con);
}

template <typename T>
T con_presort(T con, size_t pair_num)
{
	T con_new;
	for (size_t i = 0; i < con.size(); i++)
	{
		if ((i + 1) % (pair_num * 2) == 0)
		{
			if (con[i] > con[i - pair_num])
			{
				for (size_t u = i - (pair_num * 2) + 1; u - (i - pair_num * 2 + 1) < pair_num * 2; u++)
					con_new.push_back(con[u]);
			}
			else
			{
				for (size_t u = i - pair_num; u - (i - pair_num) < pair_num; u++)
					con_new.push_back(con[u + 1]);
				for (size_t u = i - (pair_num * 2); u - (i - (pair_num * 2)) < pair_num; u++)
					con_new.push_back(con[u + 1]);
			}
		}
	}
	while (con_new.size() < con.size())
		con_new.push_back(con[con_new.size()]);
	return (con_new);
}

template <typename T>
T con_recurs(T con, size_t pair_num)
{
	if (con.size() >= pair_num * 2)
	{
		con = con_presort(con, pair_num);
		con = con_recurs(con, pair_num * 2);
		con = con_insert(con, pair_num);
	}
	return (con);
}

template <typename T>
T pmm_sort(char **argv)
{
	T con;
	size_t pair_num = 1;

	for (size_t i = 1; argv[i]; i++)
		con.push_back(std::stoi(argv[i]));
	con = con_recurs(con, pair_num);
	return(con);	
}

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define DEFAULT "\033[39m"
