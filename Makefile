# Makefile script to easily compile and then run program files (Really for debugging and dev work, the main script is in the tools directory)

# ===START SETUP=== #

# Compiler and linker settings
CC := gcc
CFLAGS := -fPIC -I$(shell pwd)/src/include
LDFLAGS := -L$(shell pwd)/src/shared_objects
EXE_FINAL_PATH := $(shell pwd)/src/bin/
EXE_NAME := webSrv

SRC_UTILS_PATH := $(shell pwd)/src/utils
OBJ_PATH := $(shell pwd)/src/objs
SRC_SERVER_PATH := $(shell pwd)/src/server
SETUP_PATH := $(shell pwd)/config
SETUP_SCRIPT := setup_script.sh

# Source and object files
UTILS_SRC := $(wildcard $(SRC_UTILS_PATH)/*.c)
SERVER_SRC := $(SRC_SERVER_PATH)/handleClient.c $(SRC_SERVER_PATH)/settings.c

# Shared source files and objects
SHARED_SRC := $(UTILS_SRC) $(SERVER_SRC)
SHARED_OBJS := $(patsubst %.c,$(OBJ_PATH)/%.o,$(notdir $(SHARED_SRC)))

# Shared library target
LD_LIBRARY_PATH := $(shell pwd)/src/shared_objects
LIBRARY := $(LD_LIBRARY_PATH)/libWeblib.so

# ===END SETUP=== #

# Main program target
mainWebSrv: dirs $(OBJ_PATH) $(OBJ) $(LIBRARY)
	@$(CC) -g $(SRC_SERVER_PATH)/server.c -o $(EXE_FINAL_PATH)$(EXE_NAME) -L$(LD_LIBRARY_PATH) -lWeblib -lcyaml -lpthread -Wl,--rpath=$(shell pwd)/src/shared_objects
	@echo "Created executable, in the project bin directory"

# Setting up dependencies and directories
setup:
	@echo "Running dependency script for entire program and creating directories..."
	@bash -e -c 'bash $(SETUP_PATH)/$(SETUP_SCRIPT)'
	@make -s dirs
	@echo "All dependencies and directories are setup"

# Making the obj, shared_obj, and bin directories
dirs:
	@mkdir -p $(OBJ_PATH) $(LD_LIBRARY_PATH) $(EXE_FINAL_PATH)

# Compile object files from source
$(OBJ_PATH)/%.o: $(SRC_UTILS_PATH)/%.c | dirs
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_SERVER_PATH)/%.c | dirs
	@$(CC) $(CFLAGS) -c $< -o $@

# Shared library target
$(LIBRARY): dirs $(OBJ_PATH) $(SHARED_OBJS)
	@$(CC) -shared -o $(LIBRARY) $(SHARED_OBJS)
	@echo "Shared library $(LIBRARY) created"

# Runs the executable
run: $(EXE_FINAL_PATH)$(EXE_NAME)
	@echo "Running executable..."
	$(EXE_FINAL_PATH)$(EXE_NAME)

# Runs the executable in debug mode
debug: $(EXE_FINAL_PATH)$(EXE_NAME)
	@echo "Running in debug mode..."
	@gdb $(EXE_FINAL_PATH)$(EXE_NAME)

# Runs the executable in memory check mode
valgrind: $(EXE_FINAL_PATH)$(EXE_NAME)
	@echo "Running in memory checker mode..."
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(EXE_FINAL_PATH)$(EXE_NAME)

# Cleans up shared libraries, exe, and objs
clean:
	@rm -f $(LIBRARY)
	@rm -f $(OBJ_PATH)/*.o
	@rm -f $(EXE_FINAL_PATH)$(EXE_NAME)
	@echo "Cleared shared libraries, object files, and executable"
