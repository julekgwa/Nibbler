NAME = Nibbler
LIBFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@g++ $(LIBFLAG) -shared -fPIC -o ncurseslib.so ncurseslib.cpp -lncurses
	@clang++ sdllib.cpp  -shared -fPIC -o sdllib.so `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf
	@g++ -Wall -Wextra -Werror main.cpp Snake.cpp -o $(NAME)
	@echo "\033[32mMade!. \033[0m"

clean:
	@rm $(NAME)
	@rm ncurseslib.so

fclean: clean

re: fclean all