#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <map>
#include <string>
#include <stack>
#include <cctype>
#include <cstdlib>
#include "Parser.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

std::map<std::string, Parser::OpCode> Parser::_opcodes = init_opcodes();
std::map<std::string, IOperand::eOperandType> Parser::_types = init_types();

Parser::Parser(const std::string& filename)
{
  _file.open(filename.c_str(), std::ifstream::in);

  if (_file.is_open() == false)
    throw Parser::Error("Unable to open " + filename);
}

Parser::~Parser()
{
  _file.close();
}

std::queue<t_instruction*>	Parser::run()
{
  std::stack<std::string>	tokens;
  std::string			line;
  bool				is_end = false;
  int				count = 1;

  while (getline(_file, line) && !is_end)
    {
      if (line.find(";;") != std::string::npos)
	break;
      line = line.substr(0, line.find_first_of(';'));
      if (!line.empty())
	parseLine(tokenizeLine(line), count);
      count++;
    }
  return _data;
}

std::queue<std::string>		Parser::tokenizeLine(const std::string& line)
{
  std::istringstream		tokenizator(line);
  std::queue<std::string>	tokens;
  std::string			token;

  while (!tokenizator.eof())
    {
      tokenizator >> token >> std::ws;
      tokens.push(token);
    }
  return tokens;
}

void Parser::parseLine(std::queue<std::string> tokens, int line)
{
  t_instruction *instruction = new t_instruction;
  IOperand::eOperandType opType;
  std::string value;

  if (instruction)
    {
      if (_opcodes.count(tokens.front()) == 0)
	throw Parser::Error("Syntax error, unknown instruction", line);
      instruction->code = _opcodes[tokens.front()];
      tokens.pop();
      if (instruction->code == Parser::PUSH || instruction->code == Parser::ASSERT)
	{
	  value = tokens.front();
	  value[0] = tolower(value[0]);
	  opType = getType(value);
	  if (opType != IOperand::Max)
	    instruction->operand = OperandFactory::createOperand(opType, getValue(value));
	  else
	    throw Parser::Error("Syntax error, missing operand", line);
	}
      else
	{
	  instruction->operand = NULL;
	  if (!tokens.empty())
	    throw Parser::Error("Syntax error, unexpected operand", line);
	}
    }
  _data.push(instruction);
}

IOperand::eOperandType Parser::getType(const std::string& value)
{
  std::string typeValue = value.substr(0, value.find_first_of('('));

  for (std::map<std::string, IOperand::eOperandType>::iterator it = _types.begin(); it != _types.end(); it++)
    {
      if (typeValue == it->first)
	return it->second;
    }
  return IOperand::Max;
}

const std::string Parser::getValue(const std::string& value)
{
  const std::string realValue = value.substr(value.find_first_of('(') + 1, value.find_last_of(')'));
  return realValue;
}


Parser::Error::Error(const std::string &p_message, int p_line) throw()
{
  std::ostringstream stream;

  if (p_line > 0)
    {
      stream << p_line;
      m_message = p_message + " line " + stream.str();
    }
  else
    m_message = p_message;
}

const char *Parser::Error::what() const throw()
{
  return (m_message.c_str());
}
