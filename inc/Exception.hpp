/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:54:42 by jloro             #+#    #+#             */
/*   Updated: 2019/05/06 15:35:11 by jloro            ###   ########.fr       */
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
		virtual~Exception() throw();

		virtual const char *	what(void) const throw();

		std::string		getMsg(void) const;
	private:
		Exception(void);
		//Exception(const Exception & src) throw();

		Exception &	operator=(const Exception & rhs);
		std::string		_msg;
		int				_line;
};

#endif
