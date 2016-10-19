#ifndef OPERANDFACTORY_HPP_
# define OPERANDFACTORY_HPP_

#include <string>
#include "IOperand.hpp"

class OperandFactory
{
private:
  OperandFactory();
  OperandFactory(const OperandFactory&);
  OperandFactory& operator=(const OperandFactory&);
  ~OperandFactory();

  static IOperand* createInt8(const std::string& value);
  static IOperand* createInt16(const std::string& value);
  static IOperand* createInt32(const std::string& value);
  static IOperand* createFloat(const std::string& value);
  static IOperand* createDouble(const std::string& value);

public:
  static IOperand* createOperand(IOperand::eOperandType type, const std::string& value);
  template <typename T>
  static T toPrimaryType(const std::string &p_str);
};

#endif
