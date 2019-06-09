/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:46:13 by jloro             #+#    #+#             */
/*   Updated: 2019/06/09 16:09:23 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "Operand.hpp"

int		strtoint(const char * str)
{
	int	ret = 0;

	for (int i = 0; str[i]; i++)
		ret += str[i];
	return ret;
}

eOperandType	getTypeFromStr(const std::string & value, bool * error)
{
	std::string	typeStr;

	typeStr = value.substr(0, value.find_first_of('(', 0));
	*error = false;
	switch(strtoint(typeStr.c_str()))
	{
		case INT8:
			return Int8;
		case INT16:
			return Int16;
		case INT32:
			return Int32;
		case FLOAT:
			return Float;
		case DOUBLE:
			return Double;
		default:
			*error = true;
			return Int8;
	}
}

bool isStrDigits(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), [](char ch){ return ch == 45 || ch == 46 || (ch > 47 && ch < 58); });
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
