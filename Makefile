NAME = Nibbler
LIBFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@clang++ $(LIBFLAG) -shared -fPIC -o ncurseslib.so ncurseslib.cpp -lncurses
	@clang++ -shared -fPIC -o allegrolib.so allegrolib.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5)
	@clang++ sdllib.cpp -std=c++11 -shared -fPIC -o sdllib.so `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf
	@g++ -Wall -Wextra -Werror main.cpp -ldl Snake.cpp -o $(NAME)
	@echo "\033[32mMade!. \033[0m"

clean:
	@rm $(NAME)
	@rm ncurseslib.so

fclean: clean

re: fclean all