#include	<iostream>
#include	<stdint.h>
#include	"OperandFactory.hpp"
#include	"VM.hpp"
#include	"Parser.hpp"

VM::VM()
{
  m_run = false;
  opcode[Parser::PUSH] = &VM::push;
  opcode[Parser::POP] = &VM::pop;
  opcode[Parser::DUMP] = &VM::dump;
  opcode[Parser::ASSERT] = &VM::assert;
  opcode[Parser::ADD] = &VM::add;
  opcode[Parser::SUB] = &VM::sub;
  opcode[Parser::MUL] = &VM::mul;
  opcode[Parser::DIV] = &VM::div;
  opcode[Parser::MOD] = &VM::mod;
  opcode[Parser::PRINT] = &VM::print;
  opcode[Parser::EXIT] = &VM::exit;
}

VM::~VM()
{
  while (!m_stack.empty())
    {
      delete (m_stack.front());
      m_stack.pop_front();
    }
}

void		VM::run(std::queue<struct s_instruction*> &p_data)
{
  m_run = true;

  while (m_run == true && !p_data.empty())
    {
      (this->*opcode[p_data.front()->code])(p_data.front()->operand);
      p_data.pop();
    }
  if (m_run == true)
    throw VM::Error("Missing exit instruction at end of program");
}

void		VM::push(IOperand *value)
{
  m_stack.push_front(value);
}

void		VM::pop(IOperand *)
{
  if (m_stack.empty())
    throw VM::Error("pop instruction on an empty stack");
  m_stack.pop_front();
}

void		VM::dump(IOperand *)
{
  for (unsigned int i = 0; i < m_stack.size(); i++)
    std::cout << m_stack.at(i)->toString() << std::endl;
}

void		VM::assert(IOperand *value)
{
  if (m_stack.empty())
    throw VM::Error("assertion failed: stack empty");
  if (value->toString() != m_stack.front()->toString())
    throw VM::Error("assertion failed: values does not match.");
}

void		VM::add(IOperand *)
{
  IOperand	*op1;
  IOperand	*op2;

  if (m_stack.size() < 2)
    throw VM::Error("not enough element in the stack to perform add operation");
  op1 = m_stack.front();
  pop(NULL);
  op2 = m_stack.front();
  pop(NULL);
  push(*op1 + *op2);
}

void		VM::sub(IOperand *)
{
  IOperand	*op1;
  IOperand	*op2;

  if (m_stack.size() < 2)
    throw VM::Error("not enough element in the stack to perform sub operation");
  op1 = m_stack.front();
  pop(NULL);
  op2 = m_stack.front();
  pop(NULL);
  push(*op1 - *op2);
}

void		VM::mul(IOperand *)
{
  IOperand	*op1;
  IOperand	*op2;

  if (m_stack.size() < 2)
    throw VM::Error("not enough element in the stack to perform mul operation");
  op1 = m_stack.front();
  pop(NULL);
  op2 = m_stack.front();
  pop(NULL);
  push(*op1 * *op2);
}

void		VM::div(IOperand *)
{
  IOperand	*op1;
  IOperand	*op2;

  if (m_stack.size() < 2)
    throw VM::Error("not enough element in the stack to perform div operation");
  op1 = m_stack.front();
  pop(NULL);
  op2 = m_stack.front();
  pop(NULL);
  push(*op1 / *op2);
}

void		VM::mod(IOperand *)
{
  IOperand	*op1;
  IOperand	*op2;

  if (m_stack.size() < 2)
    throw VM::Error("not enough element in the stack to perform mod operation");
  op1 = m_stack.front();
  pop(NULL);
  op2 = m_stack.front();
  pop(NULL);
  push(*op1 % *op2);
}

void		VM::print(IOperand *)
{
  if (m_stack.empty())
    throw VM::Error("print failed: stack empty");
  if (m_stack.front()->getType() != IOperand::Int8)
    throw VM::Error("print failed: top value is not a 8 bit integer");
  std::cout << OperandFactory::toPrimaryType<int8_t>(m_stack.front()->toString()) << std::endl;
}

void		VM::exit(IOperand *)
{
  m_run = false;
}
