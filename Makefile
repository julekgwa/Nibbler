NAME = Nibbler

all: $(NAME)

$(NAME):
	@g++ -Wall -Wextra -Werror main.cpp -lncurses -o $(NAME)
	@echo Made!

clean:
	rm $(NAME)

fclean: clean

re: fclean all
