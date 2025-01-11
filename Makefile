# Makefile script to easily compile and then run program files

webSrv: server.o
	@gcc server.o -o webSrv

server.o: server.c
	@gcc -c server.c -o server.o

clean:
	@echo "Cleared object files"
	@rm *.o