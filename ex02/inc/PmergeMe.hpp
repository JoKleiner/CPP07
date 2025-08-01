/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:50:54 by joklein           #+#    #+#             */
/*   Updated: 2025/08/01 15:02:57 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <deque>
#include <vector>

size_t next_jac_num(size_t jac_num_pos);

template <typename T>
long binary(size_t pair_num, int search_b_num, T vec_a_chain, long pos_chain_a)
{
	size_t start = 0;
	size_t end = (pos_chain_a + 1) / pair_num - 1;
	T pair_chain;
	size_t mid;

	for (size_t i = 1; (pair_num * i) - 1 < vec_a_chain.size(); i++)
		pair_chain.push_back(vec_a_chain[(pair_num * i) - 1]);

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
void push_a_b_chain(T &vec_a_chain, T &vec_b_chain, T &index_a, T &index_b, T vec, size_t pair_num)
{
	bool b_chain = true;

	for (size_t i = 0; i < vec.size(); i++)
	{
		if ((i + 1) % (pair_num) == 0)
		{
			if (b_chain)
			{
				for (size_t u = i + 1 - pair_num; u < i + 1; u++)
					vec_b_chain.push_back(vec[u]);
				index_b.push_back(vec_b_chain.size() - 1);
			}
			else
			{
				for (size_t u = i + 1 - pair_num; u < i + 1; u++)
					vec_a_chain.push_back(vec[u]);
				index_a.push_back(vec_a_chain.size() - 1);
			}
			b_chain = !b_chain;
		}
	}
	vec_a_chain.insert(vec_a_chain.begin(), vec_b_chain.begin(), vec_b_chain.begin() + pair_num);
	for (long v = 0; v < (long)index_a.size(); v++)
		index_a[v] += pair_num;
}

template <typename T>
T vec_insert(T vec, size_t pair_num)
{
	T vec_a_chain;
	T vec_b_chain;
	T index_a;
	T index_b;
	push_a_b_chain(vec_a_chain, vec_b_chain, index_a, index_b, vec, pair_num);

	size_t jac_num_pos = 3;
	size_t jac_num = 0;
	size_t jac_num_old = 0;
	for(; jac_num_old < vec_b_chain.size(); jac_num_pos++)
	{
		jac_num_old = jac_num;
		jac_num = next_jac_num(jac_num_pos) - 1;

		for (long i = jac_num; i > (long)jac_num_old; i--)
		{
			if (vec_b_chain.size() > i * pair_num)
			{
				long pos_chain_a = index_a[i - 1];
				size_t pos_chain_b = index_b[i] + 1;
				pos_chain_a = binary(pair_num, vec_b_chain[index_b[i]], vec_a_chain, pos_chain_a);

				size_t pos_index_a = index_a.size();
				for (size_t multip = 0; pos_index_a == index_a.size(); multip++)
					pos_index_a = std::find(index_a.begin(), index_a.end(), pos_chain_a + (pair_num * multip) - 1) - index_a.begin();
					
				vec_a_chain.insert(vec_a_chain.begin() + pos_chain_a, vec_b_chain.begin() + pos_chain_b - pair_num, vec_b_chain.begin() + pos_chain_b);
				for (; pos_index_a < index_a.size(); pos_index_a++)
					index_a[pos_index_a] += pair_num;
			}
		}
	}
	size_t left_over = vec.size() % pair_num;
	vec_a_chain.insert(vec_a_chain.end(), vec.end() - left_over, vec.end());
	return (vec_a_chain);
}

template <typename T>
T vec_presort(T vec, size_t pair_num)
{
	T vec_new;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if ((i + 1) % (pair_num * 2) == 0)
		{
			if (vec[i] > vec[i - pair_num])
			{
				for (size_t u = i - (pair_num * 2) + 1; u - (i - pair_num * 2 + 1) < pair_num * 2; u++)
					vec_new.push_back(vec[u]);
			}
			else
			{
				for (size_t u = i - pair_num; u - (i - pair_num) < pair_num; u++)
					vec_new.push_back(vec[u + 1]);
				for (size_t u = i - (pair_num * 2); u - (i - (pair_num * 2)) < pair_num; u++)
					vec_new.push_back(vec[u + 1]);
			}
		}
	}
	while (vec_new.size() < vec.size())
		vec_new.push_back(vec[vec_new.size()]);
	return (vec_new);
}

template <typename T>
T vec_recurs(T vec, size_t pair_num)
{
	if (vec.size() >= pair_num * 2)
	{
		vec = vec_presort(vec, pair_num);
		vec = vec_recurs(vec, pair_num * 2);
		vec = vec_insert(vec, pair_num);
	}
	return (vec);
}

template <typename T>
T pmm_sort(char **argv)
{
	T vec;
	size_t pair_num = 1;

	for (size_t i = 1; argv[i]; i++)
		vec.push_back(std::stoi(argv[i]));
	vec = vec_recurs(vec, pair_num);
	return(vec);	
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
