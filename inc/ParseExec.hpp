/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:52:59 by jloro             #+#    #+#             */
/*   Updated: 2019/05/10 11:36:46 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEEXEC_HPP
# define PARSEEXEC_HPP

# include <list>
# include <map>
# include "IOperand.hpp"
# include "Factory.hpp"

# define PUSH 0
# define POP 1
# define DUMP 2
# define ASSERT 3
# define ADD 4
# define SUB 5
# define MUL 6
# define DIV 7
# define MOD 8
# define LOG 9
# define EXP 10
# define COS 11
# define PRINT 12
# define EXIT 13
# define TAN 14
# define SIN 15
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
		void	dump(void);
		void	print(void);
		void	exit(void);
		void	special(char op);
		void	calculate(char op);
		void	push(const std::string value);
		void	assert(const std::string value);

		std::list<const IOperand *>		_stack;
		std::map<std::string, int>		_convert;
		std::string						_file;
		Factory *						_factory;
		bool							_exit;
		int								_nbLine;
};

#endif
