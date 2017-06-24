NAME = Nibbler
LIBFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@g++ -Wall -Wextra -Werror main.cpp Snake.cpp ncursescolorlib.cpp -lncurses -o $(NAME)
	@echo "\033[32mMade!. \033[0m"

clean:
	@rm $(NAME)

fclean: clean

ncurseslib.so:
	@clang++ $(LIBFLAG) -g -fPIC -c ncurseslib.cpp
	@clang++ -shared -o libncurseslib.so -lncurses ncurseslib.o
	@echo "\033[32mCreated ncurseslib library.\033[0m"

re: fclean all
