# Makefile script to easily compile and then run program files

# Compiler and linker settings
CC := gcc
CFLAGS := -fPIC
LDFLAGS := -L$(shell pwd)/../shared_objects -lncurses
LD_LIBRARY_PATH := $(shell pwd)/../shared_objects
EXE_FINAL_PATH := $(shell pwd)/../bin/
EXE_NAME := webSrv
OBJ_PATH := $(shell pwd)/../objs

# Source and object files
SRC := settings.c handleClient.c cache.c threadpool.c
OBJ := $(patsubst %.c,$(OBJ_PATH)/%.o,$(SRC))

# Shared library target
LIBRARY := $(LD_LIBRARY_PATH)/libWeblib.so
SHARED_OBJS := $(OBJ)

# Main program target
mainWebSrv: $(OBJ_PATH) $(OBJ) $(LIBRARY)
	@$(CC) server.c -o $(EXE_FINAL_PATH)$(EXE_NAME) -L$(LD_LIBRARY_PATH) -lWeblib -lncurses
	@echo "Created executable, in the project bin directory"

# Compile object files from source
$(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@


# Shared library target
$(LIBRARY): $(OBJ_PATH) $(SHARED_OBJS)
	@$(CC) -shared -o $(LIBRARY) $(SHARED_OBJS)
	@echo "Shared library $(LIBRARY) created"

# Runs the executable
run:
	@echo "Running executable..."
	$(EXE_FINAL_PATH)$(EXE_NAME)

# Runs the executable in debug mode
debug:
	@echo "Running in debug mode..."
	@gdb $(EXE_FINAL_PATH)$(EXE_NAME)

# Cleans up shared libraries, exe, and objs
clean:
	@rm -f $(LIBRARY)
	@rm -f $(OBJ)
	@rm -f $(EXE_FINAL_PATH)/webSrv
	@echo "Cleared shared libraries, object files, and executable"
