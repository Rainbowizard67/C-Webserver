# Makefile script to easily compile and then run program files (Really for debugging and dev work, the main script is in the tools directory)

# Compiler and linker settings
CC := gcc
CFLAGS := -fPIC -I$(shell pwd)/src/headers
LDFLAGS := -L$(shell pwd)/src/shared_objects
LD_LIBRARY_PATH := $(shell pwd)/src/shared_objects
EXE_FINAL_PATH := $(shell pwd)/src/bin/
EXE_NAME := webSrv
OBJ_PATH := $(shell pwd)/src/objs
SRC_PATH := $(shell pwd)/src/program_files

# Source and object files
SRC := $(wildcard $(SRC_PATH)/*.c)
OBJ := $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC))

# Shared library target
LIBRARY := $(LD_LIBRARY_PATH)/libWeblib.so
SHARED_OBJS := $(OBJ_PATH)/cache.o $(OBJ_PATH)/handleClient.o $(OBJ_PATH)/threadpool.o $(OBJ_PATH)/settings.o

# Main program target
mainWebSrv: $(OBJ_PATH) $(OBJ) $(LIBRARY)
	@$(CC) $(SRC_PATH)/server.c -o $(EXE_FINAL_PATH)$(EXE_NAME) -L$(LD_LIBRARY_PATH) -lWeblib -lpthread -Wl,--rpath=$(shell pwd)/src/shared_objects
	@echo "Created executable, in the project bin directory"

# Compile object files from source
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

# Shared library target
$(LIBRARY): $(OBJ_PATH) $(SHARED_OBJS)
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

# Cleans up shared libraries, exe, and objs
clean:
	@rm -f $(LIBRARY)
	@rm -f $(OBJ)
	@rm -f $(EXE_FINAL_PATH)$(EXE_NAME)
	@echo "Cleared shared libraries, object files, and executable"
