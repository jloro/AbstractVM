/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:52:59 by jloro             #+#    #+#             */
/*   Updated: 2019/05/03 18:00:13 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEEXEC_HPP
# define PARSEEXEC_HPP

# include <stack>
# include "IOperand.hpp"
# include "Factory.hpp"

class ParseExec
{
	public:
		ParseExec(const std::string file);
		virtual~ParseExec();

		void	parse(void);
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

		std::stack<IOperand *>	_stack;
		std::string				_file;
		Factory					_factory;
};

#endif
