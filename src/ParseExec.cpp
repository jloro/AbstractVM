/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseExec.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:09:37 by jloro             #+#    #+#             */
/*   Updated: 2019/06/11 14:25:35 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseExec.hpp"
#include "Operand.hpp"
#include "Exception.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Utils.hpp"

/*
 *  Constructors/Desctructors
 */

ParseExec::ParseExec(const std::string file) : _stack(), _file(file), _factory(new Factory), _exit(false),
	_nbLine(0)
{
	this->_map = {
		{"push", &ParseExec::push},
		{"dump", &ParseExec::dump},
		{"pop", &ParseExec::pop},
		{"assert", &ParseExec::assertt},
		{"add", &ParseExec::calculate},
		{"sub", &ParseExec::calculate},
		{"mul", &ParseExec::calculate},
		{"div", &ParseExec::calculate},
		{"mod", &ParseExec::calculate},
		{"exit", &ParseExec::exit},
		{"print", &ParseExec::print},
		{"log", &ParseExec::special},
		{"cos", &ParseExec::special},
		{"exp", &ParseExec::special},
		{"sin", &ParseExec::special},
		{"tan", &ParseExec::special},
	};
}

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
			line = line.substr(0, line.find_first_of(';', 0));//remove comments on current line
			instr = line.substr(0, line.find_first_of(' ', 0));//get current instruction
			this->_currentInfo = trim(line.substr(line.find_first_of(' ', 0) + 1, std::string::npos));//get current info for push/print/assert
			if (std::find(instructionString.begin(), instructionString.end(), instr) == instructionString.end())//check if instr exists
			   throw Exception("Instruction unknown.", this->_nbLine);
			this->_currentInstr = static_cast<instruction>(std::distance(instructionString.begin(), std::find(instructionString.begin(), instructionString.end(), instr)));//get key for map
			(this->*_map[instr])();
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

void	ParseExec::special(void)
{
	const IOperand *	top;
	const IOperand *	toAdd;
	double				res = 0.0f;

	if (this->_stack.size() == 0)
		throw Exception("Can't calculate, the stack is empty", this->_nbLine);
	top = this->_stack.front();
	this->_stack.pop_front();
	switch(this->_currentInstr)
	{
		case Log:
			res = ::log(strtod(top->toString().c_str(), NULL));
			break;
		case Exp:
			res = exp(strtod(top->toString().c_str(), NULL));
			break;
		case Cos:
			res = cos(RAD(strtod(top->toString().c_str(), NULL)));
			break;
		case Sin:
			res = sin(RAD(strtod(top->toString().c_str(), NULL)));
			break;
		case Tan:
			res = tan(RAD(strtod(top->toString().c_str(), NULL)));
			break;
		default:
			break;
	}
	toAdd = this->_factory->createOperand(Double, std::to_string(res));
	delete top;
	this->_stack.push_front(toAdd);
}

void	ParseExec::calculate(void)
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
	switch (this->_currentInstr)
	{
		case Add:
			res = *sec + *first;
			break;
		case Sub:
			res = *sec - *first;
			break;
		case Mul:
			res = *sec * *first;
			break;
		case Div:
			res = *sec / *first;
			break;
		case Mod:
			res = *sec % *first;
			break;
		default:
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

void ParseExec::push(void)
{
	eOperandType		type;
	const IOperand *	toAdd;
	bool				err;
	std::string			nb;

	type = getTypeFromStr(this->_currentInfo, &err);
	if (err)
		throw Exception("Unkwown type.", this->_nbLine);
	nb = this->_currentInfo.substr(this->_currentInfo.find_first_of('(', 0) + 1, this->_currentInfo.find_last_of(')', this->_currentInfo.size() - 1) -this->_currentInfo.find_first_of('(', 0) - 1);
	if (nb.compare("") == 0 || !isStrDigits(nb))
		throw Exception("Number error.", this->_nbLine);
	toAdd = this->_factory->createOperand(type, nb);
	this->_stack.push_front(toAdd);
}


void ParseExec::assertt(void)
{
	eOperandType		type;
	const IOperand *	toCheck;
	const IOperand *	tmp;
	bool				err;

	type = getTypeFromStr(this->_currentInfo, &err);
	if (err)
		throw Exception("Unknown type.", this->_nbLine);
	if (this->_stack.size() == 0)
		throw Exception("Stack empty.", this->_nbLine);
	toCheck = this->_stack.front();
	if (toCheck->getType() != type)
		throw Exception("Assert's wrong, wrong type.", this->_nbLine);
	tmp = this->_factory->createOperand(type, this->_currentInfo.substr(this->_currentInfo.find_first_of('(', 0) + 1, this->_currentInfo.find_last_of(')', this->_currentInfo.size() - 1) -this->_currentInfo.find_first_of('(', 0) - 1));
	if (toCheck->toString().compare(tmp->toString()) != 0)
		throw Exception("Assert's wrong, wrong value.", this->_nbLine);
	delete tmp;
}
