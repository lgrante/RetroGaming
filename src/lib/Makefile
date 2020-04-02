SRC_NCURSES			=	./ncurses/NCurseModule.cpp \
						./ncurses/NCurseTexture.cpp \
						./Object.cpp
OBJ_NCURSES			=	$(SRC_NCURSES:.cpp=.o)

SRC_SFML			=	./sfml/SFMLModule.cpp
OBJ_SFML			=	$(SRC_SFML:.cpp=.o)

CXXFLAGS			=	-Wall -Wextra -Wno-delete-non-virtual-dtor -pedantic -I./ -I../ -I./ncurses -I./sfml -c -fpic
LDFLAGS				=	-shared

BUILD_DIR			=	../../build
TARGET_DIR			=	../../lib
LIB_NCURSES_NAME	=	$(LIB_PREFIX)ncurses.so
LIB_SFML_NAME		=	$(LIB_PREFIX)sfml.so


all: $(OBJ_NCURSES) $(OBJ_SFML)
	@printf "\e[38;2;21;124;214m>\tLinking $(LIB_NCURSES_NAME)...\033[0m  "
	@$(CC) -o $(LIB_NCURSES_NAME) $(OBJ_NCURSES) $(LDFLAGS)
	@printf "Done.\n"
	
	@printf "\e[38;2;21;124;214m>\tLinking $(LIB_SFML_NAME)...\033[0m  "
	@$(CC) -o $(LIB_SFML_NAME) $(OBJ_SFML) $(LDFLAGS)
	@printf "Done.\n"

	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@mv $(OBJ_NCURSES) $(OBJ_SFML) $(BUILD_DIR)
	@mv $(LIB_NCURSES_NAME) $(LIB_SFML_NAME) $(TARGET_DIR)

%.o: %.cpp
	@printf "\e[38;2;21;124;214m>\tCompiling $<...\033[0m  "
	@$(CC) -o $@ $(CXXFLAGS) $(SFMLFLAGS) $<
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
	@printf "Done.\n"

re: fclean all

.PHONY: all clean fclean re
