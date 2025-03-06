# Makefile script to easily compile and then run program files

CC := gcc
LD_LIBRARY_PATH := $(shell pwd)/shared_objects


mainWebSrv: 
	C server.c -o webSrv

objects: 
	CC -fPIC -c netMenu.c handleClient.c cache.c 

shared_library:
	CC -shared -o LD_LIBRARY_PATH/libWeblib.so netMenu.o handleClient.o cache.o

clean:
	@rm *.o
	@echo "Cleared object files"