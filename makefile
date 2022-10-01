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

# Includes src directory
INCLUDE_SRC=-I./src

# Includes headers directory
INCLUDE_HEADERS=-I./include

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#

build: clean all

all: createBinFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $(BIN)*.o -o $(BIN)$(PROJ_NAME)
	@ echo 'Finished building binary: $@'
	@ echo ' '

$(OBJ): $(C_SOURCE)
	@ echo 'Building target using GCC compiler: $^'
	$(CC) $(CC_FLAGS) $(C_SOURCE) $(INCLUDE_HEADERS)
	@ mv ./*.o $(BIN)
	@ echo ' '

createBinFolder:
	@ mkdir -p bin

clean:
	@ $(RM) $(BIN)*.o $(BIN)$(PROJ_NAME) *~
	@ rmdir $(BIN)

.PHONY: all clean
