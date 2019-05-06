/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:09:37 by jloro             #+#    #+#             */
/*   Updated: 2019/05/06 12:00:18 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExec.hpp"
#include "Operand.hpp"
#include "Exception.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

/*
 *  Constructors/Desctructors
 */

ParseExec::ParseExec(const std::string file) : _stack(), _file(file), _factory(new Factory) {}

ParseExec::~ParseExec()
{
	delete this->_factory;
}

ParseExec::ParseExec(const ParseExec &src)
{
	*this = src;
}

ParseExec::ParseExec(void) {}

/*
 *  Operators
 */

ParseExec & ParseExec::operator=(const ParseExec &rhs)
{
	this->_file = rhs.getFile();
	return *this;
}

/*
 *  Accessors
 */

std::string ParseExec::getFile(void) const { return this->_file; }

/*
 *  Utilities
 */

int		strtoint(const char * str)
{
	int	ret = 0;

	for (int i = 0; str[i]; i++)
		ret += str[i];
	return ret;
}

void ParseExec::parse(void)
{
	std::stringstream	ss(this->_file);
	std::string			line;
	std::string			instr;
	int					i = 0;

	while (getline(ss, line))
	{
		if (line.c_str()[0] == ';' || line.compare("") == 0)
			;
		else
		{
			instr = line.substr(0, line.find_first_of(' ', 0));
			switch(strtoint(instr.c_str()))
			{
				case PUSH:
					this->push(line.substr(line.find_first_of(' ', 0) + 1, std::string::npos));
					break;
				case POP:
					this->pop();
					break;
				case DUMP:
					this->dump();
					break;
				case ASSERT:
					std::cout << "assert" << std::endl;
					break;
				case ADD:
					this->add();
					break;
				case SUB:
					this->sub();
					break;
				case MUL:
					this->mul();
					break;
				case DIV:
					this->div();
					break;
				case MOD:
					this->mod();
					break;
				case PRINT:
					std::cout << "print" << std::endl;
					break;
				case EXIT:
					std::cout << "exit" << std::endl;
					break;
				default:
					std::stringstream	err;
					err << "Line " << i << ": Instruction unknown.";
					throw Exception(err.str());
					break;
			}
		}
		i++;
	}
}

void ParseExec::pop(void)
{
	if (this->_stack.size() == 0)
		throw Exception("Pop but stack is empty.");
	this->_stack.pop();
}


void ParseExec::dump(void)
{
	std::stack<const IOperand *>	cpy(this->_stack);

	while (cpy.size() != 0)
	{
		std::cout << cpy.top()->toString() << std::endl;
		cpy.pop();
	}
}


void ParseExec::add(void)
{
	const IOperand *	first;
	const IOperand *	sec;
	const IOperand *	res;

	if (this->_stack.size() < 2)
		throw Exception("Add but stack has less than 2 numbers.");
	first = this->_stack.top();
	this->_stack.pop();
	sec = this->_stack.top();
	this->_stack.pop();
	res = *sec + *first;
	this->_stack.push(res);
}


void ParseExec::sub(void)
{
	const IOperand *	first;
	const IOperand *	sec;
	const IOperand *	res;

	if (this->_stack.size() < 2)
		throw Exception("Substract but stack has less than 2 numbers.");
	first = this->_stack.top();
	this->_stack.pop();
	sec = this->_stack.top();
	this->_stack.pop();
	res = *sec - *first;
	this->_stack.push(res);
}


void ParseExec::mul(void)
{
	const IOperand *	first;
	const IOperand *	sec;
	const IOperand *	res;

	if (this->_stack.size() < 2)
		throw Exception("Multiply but stack has less than 2 numbers.");
	first = this->_stack.top();
	this->_stack.pop();
	sec = this->_stack.top();
	this->_stack.pop();
	res = *sec * *first;
	this->_stack.push(res);
}


void ParseExec::div(void)
{
	const IOperand *	first;
	const IOperand *	sec;
	const IOperand *	res;

	if (this->_stack.size() < 2)
		throw Exception("Divide but stack has less than 2 numbers.");
	first = this->_stack.top();
	this->_stack.pop();
	sec = this->_stack.top();
	this->_stack.pop();
	res = *sec / *first;
	this->_stack.push(res);
}


void ParseExec::mod(void)
{
	const IOperand *	first;
	const IOperand *	sec;
	const IOperand *	res;

	if (this->_stack.size() < 2)
		throw Exception("Modulo but stack has less than 2 numbers.");
	first = this->_stack.top();
	this->_stack.pop();
	sec = this->_stack.top();
	this->_stack.pop();
	res = *sec % *first;
	this->_stack.push(res);
}


void ParseExec::print(void)
{
}


void ParseExec::exit(void)
{
}


void ParseExec::push(const std::string value)
{
	eOperandType	type;
	std::string		typeStr;
	const IOperand *		toAdd;

	typeStr = value.substr(0, value.find_first_of('(', 0));
	switch(strtoint(typeStr.c_str()))
	{
		case INT8:
			type = Int8;
			break;
		case INT16:
			type = Int16;
			break;
		case INT32:
			type = Int32;
			break;
		case FLOAT:
			type = Float;
			break;
		case DOUBLE:
			type = Double;
			break;
	}
	toAdd = this->_factory->createOperand(type, value.substr(value.find_first_of('(', 0) + 1, value.size() - value.find_first_of('(', 0) - 2));
	this->_stack.push(toAdd);
}


void ParseExec::assert(const std::string value)
{
	(void)value;
}




