SRC_NCURSES			=	./ncurses/NCurseModule.cpp \
						./Object.cpp \
						./Module.cpp
OBJ_NCURSES			=	$(SRC_NCURSES:.cpp=.o)

SRC_SFML			=	./sfml/SFMLModule.cpp \
						./Object.cpp \
						./Module.cpp
OBJ_SFML			=	$(SRC_SFML:.cpp=.o)

SRC_SDL				=	./sdl/SDLModule.cpp \
						./Object.cpp \
						./Module.cpp
OBJ_SDL				=	$(SRC_SDL:.cpp=.o)

CXXFLAGS			=	-g3 -Wall -Wextra -Wno-reorder -Wno-implicit-fallthrough -Wno-deprecated-declarations -Wno-delete-non-virtual-dtor -pedantic -I./ -I../ -I./ncurses -I./sfml -c -fpic
LDFLAGS				=	-shared

BUILD_DIR			=	../../build
TARGET_DIR			=	../../lib
LIB_NCURSES_NAME	=	$(LIB_PREFIX)ncurses.so
LIB_SFML_NAME		=	$(LIB_PREFIX)sfml.so
LIB_SDL_NAME		=	$(LIB_PREFIX)sdl.so

ncurses: $(OBJ_NCURSES)
	@printf "\e[38;2;21;124;214m>\tLinking $(LIB_NCURSES_NAME)...\033[0m  "
	@$(CC) -o $(LIB_NCURSES_NAME) $(OBJ_NCURSES) $(LDFLAGS)
	@printf "Done.\n"
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@mv $(OBJ_NCURSES) $(BUILD_DIR)
	@mv $(LIB_NCURSES_NAME) $(TARGET_DIR)

sdl: $(OBJ_SDL)
	@printf "\e[38;2;21;124;214m>\tLinking $(LIB_SDL_NAME)...\033[0m  "
	@$(CC) -o $(LIB_SDL_NAME) $(OBJ_SDL) $(LDFLAGS)
	@printf "Done.\n"
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@mv $(OBJ_SDL) $(BUILD_DIR)
	@mv $(LIB_SDL_NAME) $(TARGET_DIR)

sfml: $(OBJ_SFML)
	@printf "\e[38;2;21;124;214m>\tLinking $(LIB_SFML_NAME)...\033[0m  "
	@$(CC) -o $(LIB_SFML_NAME) $(OBJ_SFML) $(LDFLAGS)
	@printf "Done.\n"
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@mv $(OBJ_SFML) $(BUILD_DIR)
	@mv $(LIB_SFML_NAME) $(TARGET_DIR)

%.o: %.cpp
	@printf "\e[38;2;21;124;214m>\tCompiling $<...\033[0m  "
	@$(CC) -o $@ $(CXXFLAGS) $< $(LIBFLAGS)
	@printf "Done.\n"

clean:
	@printf "\e[38;2;21;124;214m>\tCleaning graphicals object files...\033[0m  "
	@$(RM) $(BUILD_DIR)/*.o
ifneq (, $(wildcard $(BUILD_DIR)))
	@$(RM) -r $(BUILD_DIR)
endif
	@printf "Done.\n"

fclean: clean
	@printf "\e[38;2;21;124;214m>\tCleaning graphicals shared library...\033[0m  "
	@$(RM) $(TARGET_DIR)/$(LIB_NCURSES_NAME)
	@$(RM) $(TARGET_DIR)/$(LIB_SFML_NAME)
	@$(RM) $(TARGET_DIR)/$(LIB_SDL_NAME)
	@printf "Done.\n"

re: fclean all

.PHONY: all clean fclean re
