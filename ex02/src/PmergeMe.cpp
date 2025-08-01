/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:52:27 by joklein           #+#    #+#             */
/*   Updated: 2025/08/01 12:47:43 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"
#include <vector>

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

void push_a_b_chain(std::vector<int> &vec_a_chain, std::vector<int> &vec_b_chain, std::vector<int> &index_a, std::vector<int> &index_b, std::vector<int> vec, size_t pair_num)
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

long binary(size_t pair_num, int search_b_num, std::vector<int> vec_a_chain, long pos_chain_a)
{
	size_t start = 0;
	size_t end = (pos_chain_a + 1) / pair_num - 1;
	std::vector<int> pair_chain;
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
	pos_chain_a = start * pair_num;
	return (pos_chain_a);
}

std::vector<int> vec_insert(std::vector<int> vec, size_t pair_num)
{
	std::vector<int> vec_a_chain;
	std::vector<int> vec_b_chain;
	std::vector<int> index_a;
	std::vector<int> index_b;
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

				size_t multip = 0;
				size_t pos_index_a = index_a.size();
				while (pos_index_a == index_a.size())
				{
					pos_index_a = std::find(index_a.begin(), index_a.end(), pos_chain_a + (pair_num * multip) - 1) - index_a.begin();
					multip++;
				}
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

std::vector<int> vec_presort(std::vector<int> vec, size_t pair_num)
{
	std::vector<int> vec_new;
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

std::vector<int> vec_recurs(std::vector<int> vec, size_t pair_num)
{
	if (vec.size() >= pair_num * 2)
	{
		vec = vec_presort(vec, pair_num);
		vec = vec_recurs(vec, pair_num * 2);
		vec = vec_insert(vec, pair_num);
	}
	return (vec);
}

void vec_sort(int argc, char **argv)
{
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<int> vec;
	for (size_t i = 1; argv[i]; i++)
	{
		int num = std::stoi(argv[i]);
		vec.push_back(num);
	}
	size_t pair_num = 1;
	vec = vec_recurs(vec, pair_num);

	std::cout << "After:	 ";
	for (size_t v = 0; v < vec.size(); v++)
		std::cout << vec[v] << " ";
	std::cout << std::endl;

	auto end = std::chrono::high_resolution_clock::now();

	double duration = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1000;
	std::cout << "Time to process a range of: " << argc - 1 << " elements with std::vector: "<< duration << " us\n";
}
