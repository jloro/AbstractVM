/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:56:08 by jloro             #+#    #+#             */
/*   Updated: 2019/05/02 17:03:49 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

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
