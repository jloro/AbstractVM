/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:01:17 by jloro             #+#    #+#             */
/*   Updated: 2019/05/03 15:34:36 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "IOperand.hpp"
# include <vector>

class Factory
{
	public:
		Factory(void);
		virtual~Factory();


		IOperand const * createOperand(eOperandType type, const std::string & value) const;
	private:
		Factory &	operator=(const Factory & rhs);
		Factory(const Factory & src);
		IOperand const * createInt8(const std::string & value) const;
		IOperand const * createInt16(const std::string & value) const;
		IOperand const * createInt32(const std::string & value) const;
		IOperand const * createFloat(const std::string & value) const;
		IOperand const * createDouble(const std::string & value) const;

		typedef IOperand const * (Factory::*create)(const std::string &) const;
		static create		_f[5];
};

#endif
