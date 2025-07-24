/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:47:55 by joklein           #+#    #+#             */
/*   Updated: 2025/07/24 10:43:35 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <regex>

class BitcoinExchange
{
	public:
		BitcoinExchange(std::ifstream &data_csv);
		BitcoinExchange(const BitcoinExchange &other) = delete;
		BitcoinExchange &operator=(const BitcoinExchange &other) = delete;
		~BitcoinExchange() = default;

		void process_btc(std::ifstream &input_file);
		void out_put(std::string input_date, double input_num);
		
	private:
		BitcoinExchange() = default;
		std::map<std::string, double> m_data_map;
		
};

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
