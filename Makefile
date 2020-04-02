SRC					=	./src/Core.cpp \
						./src/lib/ncurses/NCurseTexture.cpp \
						./src/games/Game.cpp \
						./src/main.cpp

export CC			=	g++
export RM			=	rm -f
export SFMLFLAGS	=	-lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio
CXXFLAGS			=	-Wall -Wextra -Wno-delete-non-virtual-dtor -pedantic -I./src -I./src/games -I./src/lib -I./src/lib/ncurses -ldl

export LIB_PREFIX	=	lib_arcade_
GAMES_DIR			=	./src/games
GRAPHICALS_DIR		=	./src/lib
EXEC				=	arcade

all: core games graphicals

core:
	@printf "\e[1m\e[38;2;21;124;214mCompiling and linking $(EXEC)...\033[0m\n"
	@$(CC) -o $(EXEC) $(SRC) $(CXXFLAGS) $(SFMLFLAGS)
	@printf "\e[1m> Done.\033[0m\n"

games:
	@printf "\e[1m\e[38;2;21;124;214m> Compiling and linking game libraries...\033[0m\n"
	@(cd $(GAMES_DIR) && $(MAKE) --no-print-directory)
	@printf "\e[1m> Done.\033[0m\n"

graphicals:
	@printf "\e[1m\e[38;2;21;124;214m> Compiling and linking graphical libraries...\033[0m\n"
	@(cd $(GRAPHICALS_DIR) && $(MAKE) --no-print-directory)
	@printf "\e[1m> Done.\033[0m\n"

clean:
	@printf "\e[1m\e[38;2;21;124;214m> Cleaning all object files...\033[0m\n"
	@(cd $(GAMES_DIR) && $(MAKE) $@ --no-print-directory)
	@(cd $(GRAPHICALS_DIR) && $(MAKE) $@ --no-print-directory)
	@$(RM) $(OBJ)
	@printf "\e[1m> Done.\033[0m\n"

fclean:
	@printf "\e[1m\e[38;2;21;124;214m> Cleaning all object files and libraries...\033[0m\n"
	@(cd $(GAMES_DIR) && $(MAKE) $@ --no-print-directory)
	@(cd $(GRAPHICALS_DIR) && $(MAKE) $@ --no-print-directory)
	@printf "\e[38;2;21;124;214m>\tCleaning $(EXEC)...\033[0m  "
	@$(RM) $(EXEC)
	@printf "Done.\n"
	@printf "\e[1m> Done.\033[0m\n"

re_core: fclean core

re:	fclean all

.PHONY: core games graphicals
