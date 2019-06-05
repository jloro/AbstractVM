/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:52:59 by jloro             #+#    #+#             */
/*   Updated: 2019/06/05 12:37:17 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEEXEC_HPP
# define PARSEEXEC_HPP

#include <functional>
# include <list>
# include <unordered_map>
# include "IOperand.hpp"
# include "Factory.hpp"
# include <array>

enum instruction {Push, Pop, Dump, Assert, Add, Sub, Mul, Div, Mod, Log, Exp, Cos, Print, Exit, Tan, Sin};
static std::array<std::string, 16> instructionString { {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "log", "exp", "cos", "print", "exit", "tan", "sin"} };
# define RAD(x) (x * M_PI) / 180.0f

class ParseExec
{
	public:
		ParseExec(const std::string file);
		virtual~ParseExec();

		void		parse(void);
		std::string	getFile(void) const;
	private:
		ParseExec(void);
		ParseExec &	operator=(const ParseExec & rhs);
		ParseExec(const ParseExec & src);

		void	pop(void);
		void	test(void);
		void	dump(void);
		void	print(void);
		void	exit(void);
		void	special(void);
		void	calculate(void);
		void	push(void);
		void	assert(void);

		typedef void (ParseExec::*instrTypedef)(void);

		std::list<const IOperand *>		_stack;
		std::unordered_map<std::string, instrTypedef>		_map;
		std::string						_file;
		std::string						_currentInfo;
		instruction						_currentInstr;
		Factory *						_factory;
		bool							_exit;
		int								_nbLine;
};

#endif
