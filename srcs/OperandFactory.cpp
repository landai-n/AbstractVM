#include <string>
#include <sstream>
#include <stdint.h>
#include <cstdlib>
#include <iostream>
#include "OperandFactory.hpp"
#include "Operand.hpp"

template <typename T>
T			OperandFactory::toPrimaryType(const std::string &p_str)
{
  T			val;
  std::stringstream	stream(p_str);

  if (sizeof(val) == 1)
    return (atoi(p_str.c_str()));
  stream >> val;
  return (val);
}

template int8_t OperandFactory::toPrimaryType<int8_t>(const std::string&);
template int16_t OperandFactory::toPrimaryType<int16_t>(const std::string&);
template int32_t OperandFactory::toPrimaryType<int32_t>(const std::string&);
template float OperandFactory::toPrimaryType<float>(const std::string&);
template double OperandFactory::toPrimaryType<double>(const std::string&);

OperandFactory::OperandFactory()
{
}

OperandFactory::OperandFactory(const OperandFactory&)
{
}

OperandFactory& OperandFactory::operator=(const OperandFactory&)
{
  return *this;
}

OperandFactory::~OperandFactory()
{
}

IOperand* OperandFactory::createInt8(const std::string &value)
{
  return (new Operand<int8_t>(toPrimaryType<int8_t>(value), IOperand::Int8));
}

IOperand* OperandFactory::createInt16(const std::string &value)
{
  return (new Operand<int16_t>(toPrimaryType<int16_t>(value), IOperand::Int16));
}

IOperand* OperandFactory::createInt32(const std::string &value)
{
  return (new Operand<int32_t>(toPrimaryType<int32_t>(value), IOperand::Int32));
}

IOperand* OperandFactory::createFloat(const std::string &value)
{
  return (new Operand<float>(toPrimaryType<float>(value), IOperand::Float));
}

IOperand* OperandFactory::createDouble(const std::string &value)
{
  return (new Operand<double>(toPrimaryType<double>(value), IOperand::Double));
}

IOperand* OperandFactory::createOperand(IOperand::eOperandType type, const std::string& value)
{
  static IOperand* (*ptr[5])(const std::string&) =
    {
      &OperandFactory::createInt8,
      &OperandFactory::createInt16,
      &OperandFactory::createInt32,
      &OperandFactory::createFloat,
      &OperandFactory::createDouble
    };
  return (ptr[type](value));
}
