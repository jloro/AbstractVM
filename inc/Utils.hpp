/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:47:14 by jloro             #+#    #+#             */
/*   Updated: 2019/05/06 15:48:40 by jloro            ###   ########.fr       */
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

#endif
