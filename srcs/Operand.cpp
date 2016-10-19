#include	<cmath>
#include	<iostream>
#include	<sstream>
#include	<stdint.h>
#include	<limits>
#include	<stdexcept>
#include	"OperandFactory.hpp"
#include	"Operand.hpp"

template <typename T>
int		Operand<T>::s_precision[IOperand::Max] = {1, 2, 3, 4, 5};

template <typename T>
std::string		Operand<T>::toString(const T &p_value)
{
  std::ostringstream	stream;
  std::string		str;

  if (sizeof(p_value) == 1)
    stream << (short)p_value;
  else
    stream << p_value;
  return (stream.str());
}

template <typename T>
Operand<T>::Operand(const T &p_value, const IOperand::eOperandType &p_type) : m_str(Operand<T>::toString(p_value))
{
  m_value = p_value;
  m_type = p_type;
}

template <typename T>
Operand<T>::Operand(const std::string &p_value, const IOperand::eOperandType &p_type)
{
  m_value = OperandFactory::toPrimaryType<T>(p_value);
  m_type = p_type;
  m_str = p_value;
}

template <typename T>
Operand<T>::~Operand()
{
}

template <typename T>
std::string const	&Operand<T>::toString() const
{
  return (m_str);
}

template <typename T>
IOperand::eOperandType	Operand<T>::getType() const
{
  return (m_type);
}

template <typename T>
int			Operand<T>::getPrecision() const
{
  return (s_precision[m_type]);
}

template <typename T>
IOperand	*Operand<T>::operator+(const IOperand &p_value) const
{
  if (s_precision[p_value.getType()] > s_precision[m_type])
    return (p_value.operator+(*this));
  return (add(*this, Operand<T>(p_value.toString(), p_value.getType())));
}

template <typename T>
IOperand	*Operand<T>::operator-(const IOperand &p_value) const
{
  if (s_precision[p_value.getType()] > s_precision[m_type])
    return (p_value.invertedSub(*this));
  return (sub(*this, Operand<T>(p_value.toString(), p_value.getType())));
}

template <typename T>
IOperand	*Operand<T>::operator*(const IOperand &p_value) const
{
  if (s_precision[p_value.getType()] > s_precision[m_type])
    return (p_value.operator*(*this));
  return (mul(*this, Operand<T>(p_value.toString(), p_value.getType())));
}

template <typename T>
IOperand	*Operand<T>::operator/(const IOperand &p_value) const
{
  if (p_value.toString() == "0")
    throw Operand::Error("Divide by zero");
  if (s_precision[p_value.getType()] > s_precision[m_type])
    return (p_value.invertedDiv(*this));
  return (div(*this, Operand<T>(p_value.toString(), p_value.getType())));
}

template <typename T>
IOperand	*Operand<T>::operator%(const IOperand &p_value) const
{
  if (p_value.toString() == "0")
    throw Operand::Error("Modulo by zero");
  if (s_precision[p_value.getType()] > s_precision[m_type])
    return (p_value.invertedMod(*this));
  return (mod(*this, Operand<T>(p_value.toString(), p_value.getType())));
}

template <typename T>
IOperand	*Operand<T>::add(const Operand<T> &p_value1, const Operand<T> &p_value2) const
{
  if (p_value1.m_value > 0 && p_value2.m_value > std::numeric_limits<T>::max() - p_value1.m_value)
    throw std::overflow_error("Overflow");
  if (p_value1.m_value < 0 && p_value2.m_value < std::numeric_limits<T>::min() - p_value1.m_value)
    throw std::underflow_error("Underflow");
  return (OperandFactory::createOperand(m_type, Operand::toString(p_value1.m_value + p_value2.m_value)));
}

template <typename T>
IOperand	*Operand<T>::sub(const Operand<T> &p_value1, const Operand<T> &p_value2) const
{
  if (p_value1.m_value > 0 && p_value2.m_value > std::numeric_limits<T>::max() - p_value1.m_value)
    throw std::overflow_error("Overflow");
  if (p_value1.m_value < 0 && p_value2.m_value < std::numeric_limits<T>::min() - p_value1.m_value)
    throw std::underflow_error("Underflow");
  return (OperandFactory::createOperand(m_type, Operand::toString(p_value1.m_value - p_value2.m_value)));
}

template <typename T>
IOperand	*Operand<T>::mul(const Operand<T> &p_value1, const Operand<T> &p_value2) const
{
  if (p_value2.m_value > std::numeric_limits<T>::max() / p_value1.m_value)
    throw std::overflow_error("Overflow");
  if (p_value2.m_value < std::numeric_limits<T>::min() / p_value1.m_value)
    throw std::underflow_error("Underflow");
  return (OperandFactory::createOperand(m_type, Operand::toString(p_value1.m_value * p_value2.m_value)));
}

template <typename T>
IOperand	*Operand<T>::div(const Operand<T> &p_value1, const Operand<T> &p_value2) const
{
  return (OperandFactory::createOperand(m_type, Operand::toString(p_value1.m_value / p_value2.m_value)));
}

template <typename T>
IOperand	*Operand<T>::mod(const Operand<T> &p_value1, const Operand<T> &p_value2) const
{
  if (getType() == IOperand::Double || getType() == IOperand::Float)
    return (OperandFactory::createOperand(m_type, Operand::toString(T(fmod(p_value1.m_value, p_value2.m_value)))));
  return (OperandFactory::createOperand(m_type, Operand::toString(T((int)p_value1.m_value % (int)p_value2.m_value))));
}

template <typename T>
IOperand	*Operand<T>::invertedSub(const IOperand &p_value) const
{
  return (sub(Operand<T>(p_value.toString(), p_value.getType()), *this));
}

template <typename T>
IOperand	*Operand<T>::invertedDiv(const IOperand &p_value) const
{
  return (div(Operand<T>(p_value.toString(), p_value.getType()), *this));
}

template <typename T>
IOperand	*Operand<T>::invertedMod(const IOperand &p_value) const
{
  return (mod(Operand<T>(p_value.toString(), p_value.getType()), *this));
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<double>;
template class Operand<float>;
