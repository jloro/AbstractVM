/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:18:58 by jloro             #+#    #+#             */
/*   Updated: 2019/05/09 13:52:44 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"
#include <stdlib.h>

/*
 *  Constructors/Desctructors
 */

Factory::Factory(void) {}

Factory::Factory(const Factory &src)
{
	*this = src;
}

Factory::~Factory() {}

/*
 *  Operators
 */

Factory & Factory::operator=(const Factory &rhs)
{
	static_cast<void>(rhs);
	return *this;
}

/*
 *  Utilities
 */

IOperand const *	Factory::createOperand(eOperandType type, const std::string & value) const
{
	if (strtod(value.c_str(), NULL) > eLimitsMax[type])
		throw Exception("Overflow", -1);
	else if (strtod(value.c_str(), NULL) < eLimitsMin[type])
		throw Exception("Underflow", -1);
	return (this->*_f[type])(value);
}

IOperand const *	Factory::createInt8(const std::string & value) const { return new Operand<char>(static_cast<char>(atoi(value.c_str())), Int8); }
IOperand const *	Factory::createInt16(const std::string & value) const { return new Operand<short>(static_cast<short>(atoi(value.c_str())), Int16); }
IOperand const *	Factory::createInt32(const std::string & value) const { return new Operand<int>(static_cast<int>(atoi(value.c_str())), Int32); }
IOperand const *	Factory::createFloat(const std::string & value) const { return new Operand<float>(static_cast<float>(strtod(value.c_str(), NULL)), Float); }
IOperand const *	Factory::createDouble(const std::string & value) const { return new Operand<double>(static_cast<double>(strtod(value.c_str(), NULL)), Double); }

Factory::create		Factory::_f[5] = {&Factory::createInt8, &Factory::createInt16, &Factory::createInt32, &Factory::createFloat, &Factory::createDouble};
