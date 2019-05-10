/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:06:54 by jloro             #+#    #+#             */
/*   Updated: 2019/05/10 12:09:07 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Exception.hpp"
#include <dirent.h>
#include "ParseExec.hpp"

std::string	readStdin(void)
{
	std::string			input_line;
	std::stringstream	ss;

	while (input_line.compare(";;") != 0 && std::cin)
	{
		getline(std::cin, input_line);
		ss << input_line << '\n';
	}
	return ss.str();
}

std::string	readFile(char * file)
{
	std::ifstream		ifs;
	std::stringstream	ss;
	std::string			tmp;

	ifs.open(file, std::ifstream::in);
	if ((ifs.rdstate() & std::ifstream::failbit) != 0)
		throw Exception("File not found", -1);
	if (opendir(file) != NULL)
		throw Exception("Is a directory", -1);
	getline(ifs, tmp);
	while (ifs.good())
	{
		ss << tmp << '\n';
		getline(ifs, tmp);
	}
	return ss.str();
}

int main(int argc, char **argv)
{
	std::string	file;
	ParseExec	*parse;

	if (argc > 2)
	{
		std::cout << "Usage: ./avm or ./avm file" << std::endl;
		return 1;
	}
	try
	{
		if (argc == 1)
			file = readStdin();
		else
			file = readFile(argv[1]);
		parse = new ParseExec(file);
		parse->parse();
		delete parse;
	}
	catch (std::exception & e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
