/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:09:37 by jloro             #+#    #+#             */
/*   Updated: 2019/05/09 16:42:15 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExec.hpp"
#include "Operand.hpp"
#include "Exception.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Utils.hpp"
#include <iomanip>

/*
 *  Constructors/Desctructors
 */

ParseExec::ParseExec(const std::string file) : _stack(), _file(file), _factory(new Factory), _exit(false),
												_nbLine(0) {}

ParseExec::~ParseExec()
{
	const IOperand * tmp;

	while (this->_stack.size() != 0)
	{
		tmp = this->_stack.front();
		this->_stack.pop_front();
		delete tmp;
	}
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

void ParseExec::parse(void)
{
	std::stringstream	ss(this->_file);
	std::string			line;
	std::string			instr;

	while (getline(ss, line) && !this->_exit)
	{
		if (line.c_str()[0] != ';' && line.compare("") != 0)
		{
			line = line.substr(0, line.find_first_of(';', 0));
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
					this->assert(line.substr(line.find_first_of(' ', 0) + 1, std::string::npos));
					break;
				case ADD:
					this->calculate('+');
					break;
				case SUB:
					this->calculate('-');
					break;
				case MUL:
					this->calculate('*');
					break;
				case DIV:
					this->calculate('/');
					break;
				case MOD:
					this->calculate('%');
					break;
				case PRINT:
					this->print();
					break;
				case EXIT:
					this->exit();
					break;
				default:
					throw Exception("Instruction unknown.", this->_nbLine);
					break;
			}
		}
		this->_nbLine++;
	}
	if (!this->_exit)
		throw Exception("No exit found", this->_nbLine);
}

void ParseExec::pop(void)
{
	const IOperand *	tmp;

	if (this->_stack.size() == 0)
		throw Exception("Pop but stack is empty.", this->_nbLine);
	tmp = this->_stack.front();
	this->_stack.pop_front();
	delete tmp;
}


void ParseExec::dump(void)
{
	std::list<const IOperand *>::iterator	beg = this->_stack.begin();
	std::list<const IOperand *>::iterator	end = this->_stack.end();

	for (;beg != end;beg++)
		std::cout << (*beg)->toString() << std::endl;
}

void	ParseExec::calculate(char op)
{
	const IOperand *	first;
	const IOperand *	sec;
	const IOperand *	res;

	if (this->_stack.size() < 2)
		throw Exception("Can't calculate, the stack has less than 2 numbers.", this->_nbLine);
	first = this->_stack.front();
	this->_stack.pop_front();
	sec = this->_stack.front();
	this->_stack.pop_front();
	switch (op)
	{
		case '+':
			res = *sec + *first;
			break;
		case '-':
			res = *sec - *first;
			break;
		case '*':
			res = *sec * *first;
			break;
		case '/':
			res = *sec / *first;
			break;
		case '%':
			res = *sec % *first;
			break;
	}
	delete sec;
	delete first;
	this->_stack.push_front(res);
}


void ParseExec::print(void)
{
	const IOperand *	top;

	if (this->_stack.size() == 0)
		throw Exception("Stack empty.", this->_nbLine);
	top = this->_stack.front();
	if (top->getType() != Int8)
		throw Exception("Top value isn't an 8-bit integer.", this->_nbLine);
	std::cout << static_cast<char>(atoi(top->toString().c_str())) << std::endl;
}


void ParseExec::exit(void)
{
	this->_exit = true;
}

void ParseExec::push(const std::string value)
{
	eOperandType		type;
	const IOperand *	toAdd;
	bool				err;
	std::string			nb;

	type = getTypeFromStr(value, &err);
	if (err)
		throw Exception("Unkwown type.", this->_nbLine);
	nb = value.substr(value.find_first_of('(', 0) + 1, value.size() - value.find_first_of('(', 0) - 2);
	if (nb.compare("") == 0 || !isStrDigits(nb) || value.back() != ')')
		throw Exception("Number error.", this->_nbLine);
	toAdd = this->_factory->createOperand(type, nb);
	this->_stack.push_front(toAdd);
}


void ParseExec::assert(const std::string value)
{
	eOperandType		type;
	const IOperand *	toCheck;
	const IOperand *	tmp;
	bool				err;

	type = getTypeFromStr(value, &err);
	if (err)
		throw Exception("Unknown type.", this->_nbLine);
	if (this->_stack.size() == 0)
		throw Exception("Stack empty.", this->_nbLine);
	toCheck = this->_stack.front();
	if (toCheck->getType() != type)
		throw Exception("Assert's wrong, wrong type.", this->_nbLine);
	tmp = this->_factory->createOperand(type, value.substr(value.find_first_of('(', 0) + 1, value.size() - value.find_first_of('(', 0) - 2));
	if (toCheck->toString().compare(tmp->toString()) != 0)
		throw Exception("Assert's wrong, wrong value.", this->_nbLine);
	delete tmp;
}
