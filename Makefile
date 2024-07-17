server.o: server.c
	gcc -c server.c -o server.o

clean:
	rm server.o