CC = gcc -Wall
CFLAGS = -Ilibnmea/include

LIBS = -lm
LIBNMEA = libnmea/lib/libnmea.a

all: main

main: main.o util.o constants.o $(LIBNMEA)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(LIBNMEA):
	make -C libnmea

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@

util.o: util.c
	$(CC) -c $^ -o $@

constants.o: constants.c
	$(CC) -c $^ -o $@

clean:
	rm -f *.o

cleanall:
	$(MAKE) clean
	cd libnmea && $(MAKE) clean && cd ..
