/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:54:42 by jloro             #+#    #+#             */
/*   Updated: 2019/05/10 12:39:13 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <string>
# include <stdexcept>

class Exception : public std::exception
{
	public:
		Exception(const std::string & msg, int line) throw();
		Exception(const Exception & src) throw();
		virtual~Exception() throw();

		virtual const char *	what(void) const throw();

		std::string		getMsg(void) const;
		int				getLine(void) const;
	private:
		Exception(void);

		Exception &	operator=(const Exception & rhs);
		std::string		_msg;
		int				_line;
};

#endif
