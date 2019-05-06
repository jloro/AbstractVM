/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:34:32 by jloro             #+#    #+#             */
/*   Updated: 2019/05/06 16:12:29 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include <stdlib.h>
# include "Exception.hpp"
# include <cmath>
# include "Factory.hpp"

template<typename T>
class Operand : public IOperand
{
	public:
		Operand(const std::string value, const eOperandType type) : _str(value), _type(type)
		{
			if (strtod(value.c_str(), NULL) > eLimitsMax[type])
				throw Exception("Overflow", -1);
			else if (strtod(value.c_str(), NULL) < eLimitsMin[type])
				throw Exception("Underflow", -1);
			this->_value = static_cast<T>(strtod(value.c_str(), NULL));
			while (this->_str.back() == '0' && this->_str.size() != 1)
				this->_str.pop_back();
		}

		Operand(const Operand & src) { *this = src; }

		virtual~Operand() {}

		T						getValue(void) const { return this->_value; }
		virtual int				getPrecision(void) const { return static_cast<int>(this->_type); }
		virtual eOperandType	getType(void) const { return this->_type; }
		virtual std::string const &	toString(void) const { return this->_str; }

		Operand &	operator=(const Operand & rhs)
		{
			this->_value = rhs.getValue();
			this->_type = rhs.getType();
			return *this;
		}

		virtual IOperand const *	operator+(IOperand const & rhs) const
		{
			eOperandType	type;
			std::string		value;

			if (rhs.getPrecision() > this->getPrecision())
				type = rhs.getType();
			else
				type = this->getType();
			value = std::to_string(this->_value + strtod(rhs.toString().c_str(), NULL));
			return this->_factory.createOperand(type, value);
		}

		virtual IOperand const *	operator-(IOperand const & rhs) const
		{
			eOperandType	type;
			std::string		value;

			if (rhs.getPrecision() > this->getPrecision())
				type = rhs.getType();
			else
				type = this->getType();
			value = std::to_string(this->_value - strtod(rhs.toString().c_str(), NULL));
			return this->_factory.createOperand(type, value);
		}

		virtual IOperand const *	operator*(IOperand const & rhs) const
		{
			eOperandType	type;
			std::string		value;

			if (rhs.getPrecision() > this->getPrecision())
				type = rhs.getType();
			else
				type = this->getType();
			value = std::to_string(this->_value * strtod(rhs.toString().c_str(), NULL));
			return this->_factory.createOperand(type, value);
		}

		virtual IOperand const *	operator/(IOperand const & rhs) const
		{
			eOperandType	type;
			std::string		value;

			if (rhs.toString().compare("0") == 0)
				throw Exception("Division by 0", -1);
			if (rhs.getPrecision() > this->getPrecision())
				type = rhs.getType();
			else
				type = this->getType();
			value = std::to_string(this->_value / strtod(rhs.toString().c_str(), NULL));
			return this->_factory.createOperand(type, value);
		}

		virtual IOperand const *	operator%(IOperand const & rhs) const
		{
			eOperandType	type;
			std::string		value;

			if (rhs.toString().compare("0") == 0)
				throw Exception("Modulo by 0", -1);
			if (rhs.getPrecision() > this->getPrecision())
				type = rhs.getType();
			else
				type = this->getType();
			value = std::to_string(fmod(this->_value, strtod(rhs.toString().c_str(), NULL)));
			return this->_factory.createOperand(type, value);
		}

	private:
		Operand(void) {}
		std::string		_str;
		T				_value;
		eOperandType	_type;
		Factory			_factory;
};

#endif
