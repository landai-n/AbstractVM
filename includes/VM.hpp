#ifndef		VM_HPP
# define	VM_HPP

#include	<string>
#include	<exception>
#include	<queue>
#include	<deque>
#include	"IOperand.hpp"

class		VM
{
public:
  VM();
  ~VM();
  void		push(IOperand *value);
  void		pop(IOperand *value);
  void		dump(IOperand *value);
  void		assert(IOperand	*value);
  void		add(IOperand *value);
  void		sub(IOperand *value);
  void		mul(IOperand *value);
  void		div(IOperand *value);
  void		mod(IOperand *value);
  void		print(IOperand *value);
  void		exit(IOperand *value);
  void		run(std::queue<struct s_instruction*> &p_data);

  class		Error : public std::exception
  {
  public:
    Error(const std::string &p_message) throw() : m_message(p_message) {}
    ~Error() throw() {}
    const char *what() const throw() { return (m_message.c_str()); }
  private:
    const std::string &m_message;
  };
private:
  std::deque<IOperand *>		m_stack;
  bool					m_run;
  void					(VM::*opcode[13])(IOperand *);
};

#endif
