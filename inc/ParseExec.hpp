/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:52:59 by jloro             #+#    #+#             */
/*   Updated: 2019/05/06 15:48:42 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEEXEC_HPP
# define PARSEEXEC_HPP

# include <stack>
# include "IOperand.hpp"
# include "Factory.hpp"

# define PUSH 448
# define POP 335
# define DUMP 438
# define ASSERT 658
# define ADD 297
# define SUB 330
# define MUL 334
# define DIV 323
# define MOD 320
# define PRINT 557
# define EXIT 442

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
		void	add(void);
		void	sub(void);
		void	mul(void);
		void	div(void);
		void	mod(void);
		void	print(void);
		void	exit(void);
		void	push(const std::string value);
		void	assert(const std::string value);

		std::stack<const IOperand *>	_stack;
		std::string						_file;
		Factory *						_factory;
		bool							_exit;
		int								_nbLine;
};

#endif
