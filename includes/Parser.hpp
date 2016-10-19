#ifndef PARSER_HPP_
# define PARSER_HPP_

#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include "IOperand.hpp"

typedef struct s_instruction t_instruction;

class Parser
{
public:

  enum OpCode { PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT };
  typedef std::map<std::string, Parser::OpCode> OpCodeMap;
  typedef std::map<std::string, IOperand::eOperandType> TypeMap;
  static OpCodeMap _opcodes;
  static TypeMap _types;

  Parser(const std::string& filename);
  std::queue<t_instruction*> run();
  ~Parser();

  class		Error : public std::exception
  {
  public:
    Error(const std::string &p_message, int p_line = -1) throw();
    ~Error() throw() {};
    virtual const char *what() const throw();
  private:
    std::string m_message;
  };

private:
  IOperand::eOperandType getType(const std::string& value);
  const std::string getValue(const std::string& value);
  std::queue<std::string> tokenizeLine(const std::string& line);
  void parseLine(std::queue<std::string> tokens, int line);

  std::ifstream				_file;
  std::queue<t_instruction*>		_data;

  static std::map<std::string, IOperand::eOperandType> init_types()
  {
    std::map<std::string, IOperand::eOperandType> _types;
    _types["int8"] = IOperand::Int8;
    _types["int16"] = IOperand::Int16;
    _types["int32"] = IOperand::Int32;
    _types["float"] = IOperand::Float;
    _types["double"] = IOperand::Double;
    return _types;
  }

  static std::map<std::string, Parser::OpCode> init_opcodes()
  {
    std::map<std::string, Parser::OpCode> _opcodes;
    _opcodes["push"] = Parser::PUSH;
    _opcodes["pop"] = Parser::POP;
    _opcodes["dump"] = Parser::DUMP;
    _opcodes["assert"] = Parser::ASSERT;
    _opcodes["add"] = Parser::ADD;
    _opcodes["sub"] = Parser::SUB;
    _opcodes["mul"] = Parser::MUL;
    _opcodes["div"] = Parser::DIV;
    _opcodes["mod"] = Parser::MOD;
    _opcodes["print"] = Parser::PRINT;
    _opcodes["exit"] = Parser::EXIT;
    return _opcodes;
  }
};

struct			s_instruction
{
  Parser::OpCode	code;
  IOperand*		operand;
};

#endif
