# ex: set ts=8 noet:

CFLAGS=-W -Wall

test: test.o sqless.o

clean:
	$(RM) test *.o

