/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:18:58 by jloro             #+#    #+#             */
/*   Updated: 2019/05/06 11:14:14 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"

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
	return (this->*_f[type])(value);
}

IOperand const *	Factory::createInt8(const std::string & value) const { return new Operand<char>(value, Int8); }
IOperand const *	Factory::createInt16(const std::string & value) const { return new Operand<short>(value, Int16); }
IOperand const *	Factory::createInt32(const std::string & value) const { return new Operand<int>(value, Int32); }
IOperand const *	Factory::createFloat(const std::string & value) const { return new Operand<float>(value, Float); }
IOperand const *	Factory::createDouble(const std::string & value) const { return new Operand<double>(value, Double); }

Factory::create		Factory::_f[5] = {&Factory::createInt8, &Factory::createInt16, &Factory::createInt32, &Factory::createFloat, &Factory::createDouble};
