# Makefile script to easily compile and then run program files

# Compiler and linker settings
CC := gcc
CFLAGS := -fPIC
LDFLAGS := -L$(shell pwd)/../shared_objects -lncurses
LD_LIBRARY_PATH := $(shell pwd)/../shared_objects
EXE_FINAL_PATH := $(shell pwd)/../../
EXE_NAME = webSrv

# Source and object files
SRC := netMenu.c handleClient.c cache.c threadpool.c
OBJ := $(SRC:.c=.o)

# Shared library target
LIBRARY := $(LD_LIBRARY_PATH)/libWeblib.so
SHARED_OBJS := netMenu.o handleClient.o cache.o threadpool.o

# Main program target
mainWebSrv: $(OBJ) $(LIBRARY)
	@$(CC) server.c -o $(EXE_FINAL_PATH)/$(EXE_NAME) -L$(LD_LIBRARY_PATH) -lWeblib -lncurses
	@rm -f $(OBJ)
	@echo "Cleared object files"

# Compile object files from source
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Shared library target
$(LIBRARY): $(SHARED_OBJS)
	@$(CC) -shared -o $(LIBRARY) $(SHARED_OBJS)
	@echo "Shared library $(LIBRARY) created"

# Runs the executable
run:
	@echo "Running executable..."
	$(EXE_FINAL_PATH)$(EXE_NAME)

debug:
	@echo "Running in debug mode..."
	@gdb $(EXE_FINAL_PATH)$(EXE_NAME)

# Cleans up shared libraries
clean:
	@rm -f $(LIBRARY)
	@rm -f $(OBJ)
	@rm -f $(EXE_FINAL_PATH)/webSrv
	@echo "Cleared shared libraries, object files, and executable"
