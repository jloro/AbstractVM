/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:56:08 by jloro             #+#    #+#             */
/*   Updated: 2019/05/03 14:40:18 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>
# define FLOAT_MAX 3.402823466e+38F
# define FLOAT_MIN -3.402823466e+38F
# define DOUBLE_MAX 1.7976931348623158e+308
# define DOUBLE_MIN -1.7976931348623158e+308
enum eOperandType {Int8 , Int16, Int32, Float, Double};

static double eLimitsMax[5] = {INT8_MAX, INT16_MAX, INT32_MAX, FLOAT_MAX, DOUBLE_MAX};
static double eLimitsMin[5] = {INT8_MIN, INT16_MIN, INT32_MIN, FLOAT_MIN, DOUBLE_MIN};

class IOperand
{
	public:
		virtual int					getPrecision(void) const = 0;	//Precision of the type of the instance
		virtual eOperandType		getType(void) const = 0;		//Type of the instance

		virtual IOperand const *	operator+(IOperand const & rhs) const = 0;	//Sum
		virtual IOperand const *	operator-(IOperand const & rhs) const = 0;	//Difference
		virtual IOperand const *	operator*(IOperand const & rhs) const = 0;	//Product
		virtual IOperand const *	operator/(IOperand const & rhs) const = 0;	//Quotient
		virtual IOperand const *	operator%(IOperand const & rhs) const = 0;	//Modulo

		virtual std::string const &	toString(void) const = 0;

		virtual ~IOperand(void) {}
};

#endif
