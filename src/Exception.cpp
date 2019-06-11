/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:55:07 by jloro             #+#    #+#             */
/*   Updated: 2019/06/11 11:19:46 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

/*
 *  Constructors/Desctructors
 */	

Exception::Exception(const std::string & msg, int line) throw() : std::exception(), _msg(msg), _line(line)
{
	this->_ret = "";
	if (this->_line != -1)
		this->_ret += "Line " + std::to_string(this->_line) + ": ";
	this->_ret += this->_msg + "\0";
	this->_ptr = this->_ret.c_str();
}

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
	return this->_ptr;
}
