/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:55:07 by jloro             #+#    #+#             */
/*   Updated: 2019/05/10 12:39:36 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"
#include <sstream>

/*
 *  Constructors/Desctructors
 */	

Exception::Exception(const std::string & msg, int line) throw() : std::exception(), _msg(msg), _line(line) {}

Exception::~Exception() throw() {}

Exception::Exception(void) : std::exception() {}

Exception::Exception(const Exception & src) throw() : std::exception()
{
	*this = src;
}

/*
 *  Operators
 */

Exception & Exception::operator=(const Exception &rhs)
{
	this->_msg = rhs.getMsg();
	this->_line = rhs.getLine();
	return *this;
}

/*
 *  Accessors
 */

std::string	Exception::getMsg(void) const { return this->_msg; }
int			Exception::getLine(void) const { return this->_line; }

/*
 *  Utilities
 */

const char *	Exception::what(void) const throw()
{
	std::string			ret;

	ret = "";
	if (this->_line != -1)
		ret += "Line " + std::to_string(this->_line) + ": ";
	ret += this->_msg + "\0";
	return ret.c_str();
}
