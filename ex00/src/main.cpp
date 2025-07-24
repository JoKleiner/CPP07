/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:10:34 by joklein           #+#    #+#             */
/*   Updated: 2025/07/24 10:38:36 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if(argc != 2)
		return(std::cerr << RED << "Error: could not open file." << std::endl, 1);
		
	try{
		std::ifstream input_file(argv[1]);
		std::ifstream data_csv("data.csv");
		if(!input_file || !data_csv)
			throw(std::runtime_error("Error: could not open file."));
		
		BitcoinExchange btc(data_csv);
		btc.process_btc(input_file);
		input_file.close();
	} catch(const std::exception &e){
		std::cerr << RED << e.what() << std::endl;
		return(1);
	}
}
