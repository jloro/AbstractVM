/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:47:14 by jloro             #+#    #+#             */
/*   Updated: 2019/06/09 13:58:22 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include "IOperand.hpp"

# define INT8 387
# define INT16 434
# define INT32 432
# define FLOAT 534
# define DOUBLE 635

int				strtoint(const char * str);
eOperandType	getTypeFromStr(const std::string & value, bool * error);
bool			isStrDigits(const std::string & str);
std::string		trim(const std::string& str);

#endif
