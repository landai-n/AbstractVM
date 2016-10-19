#ifndef		_OPERAND_HPP
# define	_OPERAND_HPP

#include	<exception>
#include	<string>
#include	"IOperand.hpp"

template <typename T>
class						Operand : public IOperand
{
public:
  Operand(const T&, const IOperand::eOperandType&);
  virtual ~Operand();
  virtual std::string const&			toString() const;
  virtual IOperand::eOperandType		getType() const;
  virtual int					getPrecision() const;
  virtual IOperand				*operator+(const IOperand &p_value) const;
  virtual IOperand				*operator-(const IOperand &p_value) const;
  virtual IOperand				*operator*(const IOperand &p_value) const;
  virtual IOperand				*operator/(const IOperand &p_value) const;
  virtual IOperand				*operator%(const IOperand &p_value) const;

  class		Error : public std::exception
  {
  public:
    Error(const std::string &p_message) throw() : m_message(p_message) {};
    ~Error() throw() {};
    virtual const char *what() const throw() { return (m_message.c_str()); }
  private:
    const std::string &m_message;
  };

private:
  Operand(const std::string&, const IOperand::eOperandType&);
  static std::string				toString(const T &p_value);
  IOperand					*add(const Operand<T> &p_value1, const Operand<T> &p_value2) const;
  IOperand					*sub(const Operand<T> &p_value1, const Operand<T> &p_value2) const;
  IOperand					*mul(const Operand<T> &p_value1, const Operand<T> &p_value2) const;
  IOperand					*div(const Operand<T> &p_value1, const Operand<T> &p_value2) const;
  IOperand					*mod(const Operand<T> &p_value1, const Operand<T> &p_value2) const;
  IOperand					*invertedSub(const IOperand &p_value) const;
  IOperand					*invertedMod(const IOperand &p_value) const;
  IOperand					*invertedDiv(const IOperand &p_value) const;

  T						m_value;
  std::string					m_str;
  IOperand::eOperandType			m_type;
  static int					s_precision[IOperand::Max];
};

#endif
