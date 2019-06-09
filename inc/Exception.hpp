/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:54:42 by jloro             #+#    #+#             */
/*   Updated: 2019/06/09 15:57:49 by jules            ###   ########.fr       */
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
		std::string		_ret;
		const char*		_ptr;
		int				_line;
};

#endif
