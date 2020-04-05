SRC_A				=	./gameA/GameA.cpp \
						./Game.cpp
OBJ_A				=	$(SRC_A:.cpp=.o)

SRC_B				=	./gameB/GameB.cpp \
						./Game.cpp
OBJ_B				=	$(SRC_B:.cpp=.o)

CXXFLAGS			=	-Wall -Wextra -Wno-delete-non-virtual-dtor -pedantic -I../ -I./ -I./gameA -I./gameB -I../lib -I../lib/ncurses -c -fpic
LDFLAGS				=	-shared

BUILD_DIR			=	../../build
TARGET_DIR			=	../../games
GAME_A_NAME			=	$(LIB_PREFIX)game_a.so
GAME_B_NAME			=	$(LIB_PREFIX)game_b.so


game_a: $(OBJ_A)
	@printf "\e[38;2;21;124;214m>\tLinking $(GAME_A_NAME)...\033[0m  "
	@$(CC) -o $(GAME_A_NAME) $(OBJ_A) $(LDFLAGS)
	@printf "Done.\n"
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@mv $(OBJ_A) $(BUILD_DIR)
	@mv $(GAME_A_NAME) $(TARGET_DIR)

game_b: $(OBJ_B)
	@printf "\e[38;2;21;124;214m>\tLinking $(GAME_B_NAME)...\033[0m  "
	@$(CC) -o $(GAME_B_NAME) $(OBJ_B) $(LDFLAGS)
	@printf "Done.\n"
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	@mv $(OBJ_B) $(BUILD_DIR)
	@mv $(GAME_B_NAME) $(TARGET_DIR)

%.o: %.cpp
	@printf "\e[38;2;21;124;214m>\tCompiling $<...\033[0m  "
	@$(CC) -o $@ $(CXXFLAGS) $< $(LIBFLAGS)
	@printf "Done.\n"

clean:
	@printf "\e[38;2;21;124;214m>\tCleaning games object files...\033[0m  "
	@$(RM) $(BUILD_DIR)/*.o
ifneq (, $(wildcard $(BUILD_DIR)))
	@$(RM) -r $(BUILD_DIR)
endif
	@printf "Done.\n"

fclean: clean
	@printf "\e[38;2;21;124;214m>\tCleaning games shared library...\033[0m  "
	@$(RM) $(TARGET_DIR)/$(GAME_A_NAME)
	@$(RM) $(TARGET_DIR)/$(GAME_B_NAME)
	@printf "Done.\n"

re: fclean all

.PHONY: all clean fclean re
