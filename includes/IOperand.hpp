#ifndef IOPERAND_HPP_
# define IOPERAND_HPP_

#include <string>

class IOperand
{
public:
  enum eOperandType { Int8, Int16, Int32, Float, Double, Max };
  virtual int getPrecision() const = 0;
  virtual eOperandType getType() const = 0;
  virtual std::string const &toString() const = 0;
  virtual IOperand* operator+(const IOperand &rhs) const = 0;
  virtual IOperand* operator-(const IOperand &rhs) const = 0;
  virtual IOperand* operator*(const IOperand &rhs) const = 0;
  virtual IOperand* operator/(const IOperand &rhs) const = 0;
  virtual IOperand* operator%(const IOperand &rhs) const = 0;
  virtual ~IOperand() {}
  virtual IOperand* invertedSub(const IOperand &rhs) const = 0;
  virtual IOperand* invertedMod(const IOperand &rhs) const = 0;
  virtual IOperand* invertedDiv(const IOperand &rhs) const = 0;
};

#endif
