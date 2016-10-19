SRCS	=	srcs/main.cpp			\
		srcs/OperandFactory.cpp		\
		srcs/Operand.cpp		\
		srcs/Parser.cpp			\
		srcs/VM.cpp			\

NAME	= 	avm

CXX	= 	g++

INCLUDES=	-I includes/

CXXFLAGS=	-Wall -Wshadow -W $(INCLUDES)

OBJS	= $(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	 $(CXX) -o $(NAME) $(OBJS) $(CXXFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
