CC=gcc
CFLAGS="-Wall"

DEPS = sock.h handler.h
OBJ = tcpserver.o sock.o handler.o

%.o: %.c $(DEPS)
	$(CC) -c -o  $@ $< $(CFLAGS) 
tcpserver: $(OBJ)
	$(CC) -o  $@ $^ $(CFLAGS) -g
debug:$(OBJ)
	$(CC) -o  $@ $^ $(CFLAGS) -g
clean:
	rm -vfr *~ tcpserver *.o
	