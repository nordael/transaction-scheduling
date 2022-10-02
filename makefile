#https://embarcados.com.br/introducao-ao-makefile/

# Name of the project
PROJ_NAME=escalona

# .c files
C_SOURCE=$(wildcard ./src/*.c)

# .h files
H_SOURCE=$(wildcard ./include/*.h)

# bin folder
BIN=$(wildcard ./bin/)

# Object files
OBJ=$(subst .c,.o,$(subst ./src,./bin,$(C_SOURCE)))

# Compiler
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
		 -std=c99   \
         -Wall  	\
         -Wextra    \
		 -pedantic

# Includes src directory
INCLUDE_SRC=-I./src

# Includes headers directory
INCLUDE_HEADERS=-I./include

# Command used at clean target
RM = rm -rf

# Coloring output
YELLOW=`tput bold; tput setaf 3`
GREEN=`tput bold; tput setaf 2`
RED=`tput bold; tput setaf 1`
RESET=`tput sgr0`

#
# Compilation and linking
#

build: clean all

all: createBinFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo "$(YELLOW)Building binary using GCC linker: $(GREEN) $@ $(RESET)"
	$(CC) $(BIN)*.o -o $(BIN)$(PROJ_NAME)
	@ echo ' '
	@ echo "$(GREEN)Finished building binary: $@ $(RESET)"
	@ echo ' '

$(OBJ): $(C_SOURCE)
	@ echo "$(YELLOW)Building target using GCC compiler: $^ $(RESET)"
	$(CC) $(CC_FLAGS) $(C_SOURCE) $(INCLUDE_HEADERS)
	@ mv ./*.o $(BIN)
	@ echo ' '

createBinFolder:
	@ echo "$(GREEN)Creating bin folder ... $(RESET)"
	@ mkdir -p bin
	@ echo ' '

clean:
	@ echo "$(GREEN)Cleaning build files ... $(RESET)"
	@ $(RM) $(BIN)*.o $(BIN)$(PROJ_NAME) *~
	@ rmdir $(BIN)
	@ echo ' '

.PHONY: all clean
