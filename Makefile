CC = clang++
FLAGS = -Wall -Wextra -Werror

EXEC_NAME = avm
SRC_FILES = main.cpp \

OBJ_FILES = $(SRC_FILES:.cpp=.o)

SRC_PATH = ./src/
OBJ_PATH = ./.obj/
LIB_PATH = ./lib/
INC_PATH = ./inc/

SRCS = $(addprefix $(SRC_PATH),$(SRC_FILES))
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_FILES))
INCS = $(addprefix -I, $(INC_PATH))

.PHONY : all clean fclean re

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJS)
	@$(CC) $(FLAGS) -o $(EXEC_NAME) $(OBJS)
	@echo "$(EXEC_NAME) compiled ✓"

$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) $(INCS) -o $@ -c $<
	@echo "$@ created ✓"

clean :
	@/bin/rm -rf $(OBJ_PATH)
	@echo "Objects cleaned ✓"

fclean : clean
	@/bin/rm -f $(EXEC_NAME)
	@echo "$(EXEC_NAME) deleted ✓"
re :
	$(MAKE) fclean
	$(MAKE) all
