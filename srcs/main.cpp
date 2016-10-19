#include	<iostream>
#include	<string>
#include	"OperandFactory.hpp"
#include	"IOperand.hpp"
#include	"Parser.hpp"
#include	"VM.hpp"

int		main(int argc, char **argv)
{
  std::queue<t_instruction*> data;
  VM	vm;

  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
      return (-1);
    }

  try
    {
      Parser p(argv[1]);

      data = p.run();
    }
  catch (Parser::Error &e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << "Unable to parse " << argv[1] << ". Quit." << std::endl;
      return (-1);
    }
  vm.run(data);

  return (0);
}
