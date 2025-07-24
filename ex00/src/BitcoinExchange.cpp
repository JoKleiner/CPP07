/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:47:58 by joklein           #+#    #+#             */
/*   Updated: 2025/07/24 11:18:05 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::ifstream &data_csv){
	std::string line;
	std::regex input_pattern("(\\d{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01]),(\\d+(?:\\.\\d+)?)");
	std::smatch match;
	std::string part_one;
	std::string part_two;
	
	std::getline(data_csv, line);
	if (line != "date,exchange_rate")
		throw(std::invalid_argument("First row not 'date,exchange_rate'"));
	
	while (std::getline(data_csv, line))
	{
		if (!std::regex_match(line, match, input_pattern))
			throw(std::invalid_argument("data.csv not in format: YYYY-MM-DD,<double>"));
		part_one = line.substr(0, 10);
		part_two = line.substr(11);
		m_data_map[part_one] = std::stod(part_two);
	}
	if (m_data_map.empty())
		throw(std::invalid_argument("data.csv not valide"));
}

bool	valide_date(std::string line){
	bool	leap_year = false;
	int		year = std::stoi(line.substr(0, 4));
	int		month = std::stoi(line.substr(5, 2));
	int		day = std::stoi(line.substr(8, 2));

	if (month == 2 && (year % 4 == 0 && ((year % 100 != 0) || (year % 400 == 0))))
		leap_year = true;
	if ((month == 4 || month == 9 || month == 11) && day > 30)
		return (false);
	if (month == 2 && ((leap_year == false && day > 28) || (leap_year == true
				&& day > 29)))
		return (false);
	return (true);
}

bool	error_found(std::string line){
	double	num;
	std::regex input_pattern("(\\d{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01]) \\| (-?\\d+(?:\\.\\d+)?)");
	std::smatch match;
	
	if (!std::regex_match(line, match, input_pattern))
		return (std::cerr << RED << "Error: bad input => " << line << RESET << std::endl, true);
	if (!valide_date(line))
		return (std::cerr << RED << "Error: not a valide date" << RESET << std::endl, true);
	num = std::stod(line.substr(13));
	if (num > std::numeric_limits<int>::max())
		return (std::cerr << RED << "Error: too large a number." << RESET << std::endl, true);
	if (num < 0)
		return (std::cerr << RED << "Error: not a positive number." << RESET << std::endl, true);
	return (false);
}

void BitcoinExchange::out_put(std::string input_date, double input_num){
	auto date = m_data_map.upper_bound(input_date);
	
	if(date == m_data_map.begin())
		std::cerr << RED << "Error: no previous date." << RESET << std::endl;
	else
	{
		--date;
		std::cout << input_date << " => " << input_num << " = " << date->second * input_num << std::endl;
	}
}

void BitcoinExchange::process_btc(std::ifstream &input_file)
{
	double	input_num;
	std::string line;
	std::string input_date;
	
	std::getline(input_file, line);
	if (line != "date | value")
		throw(std::invalid_argument("First row not 'date | value'"));
	while (std::getline(input_file, line))
	{
		if (error_found(line))
			continue ;
		input_date = line.substr(0, 10);
		input_num = std::stod(line.substr(13));
		this->out_put(input_date, input_num);
	}
}
