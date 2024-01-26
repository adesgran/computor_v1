NAME = computor
CC = c++
C_FLAGS = -Wall -Wextra -Werror -std=c++98
SRC_DIR = sources
INCLUDE_DIR = headers
OBJ_DIR = objects
DEP_DIR = objects

# List your source files without directory prefixes
CPP_FILES = main.cpp Equation.cpp equation_utils.cpp Fraction.cpp

# Prefix source files with the source directory
SRC_FILES = $(addprefix $(SRC_DIR)/, $(CPP_FILES))

# Generate object files by replacing .cpp extension with .o
O_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))
DEP_FILES = $(addprefix $(DEP_DIR)/, $(notdir $(SRC_FILES:.cpp=.d)))
INCLUDES = -I $(INCLUDE_DIR)

-include $(DEP_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "\033[0;33mGenerating ${NAME} objects... %-33.33s\r\033[0m" $@
	@mkdir -p $(@D)
	@${CC} ${C_FLAGS} ${INCLUDES} -MMD -MP -c $< -o $@

all: ${NAME}

${NAME}: ${O_FILES}
	@echo "\n\n\033[0;34mCompiling ${NAME}...\033[0m\n"
	@${CC} ${O_FILES} -o ${NAME}

clean:
	@echo "\n\033[0;31mRemoving objects files...\033[0m"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	@echo "\n\033[0;31mRemoving ${NAME} executable...\032[0m\n"
	@rm -f ${NAME}

re: fclean all

$(shell mkdir -p $(OBJ_DIR) $(DEP_DIR))
