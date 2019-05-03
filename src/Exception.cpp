/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:55:07 by jloro             #+#    #+#             */
/*   Updated: 2019/05/03 14:23:41 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

/*
 *  Constructors/Desctructors
 */	

Exception::Exception(const std::string & msg) throw() : std::exception(), _msg(msg) {}

Exception::~Exception() throw() {}

Exception::Exception(void) : std::exception() {}

/*Exception::Exception(const Exception & src) throw() : std::exception()
{
	*this = src;
}*/

/*
 *  Operators
 */

Exception & Exception::operator=(const Exception &rhs)
{
	this->_msg = rhs.getMsg();
	return *this;
}

/*
 *  Accessors
 */

std::string	Exception::getMsg(void) const { return this->_msg; }

/*
 *  Utilities
 */

const char *	Exception::what(void) const throw() { return this->_msg.c_str(); }
