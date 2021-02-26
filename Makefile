CC = gcc -Wall
CFLAGS = -Ilibnmea/include

LIBS = -lm
LIBNMEA = libnmea/lib/libnmea.a

all: main

main: main.o util.o print_msgs.o $(LIBNMEA)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(LIBNMEA):
	make -C libnmea

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@

util.o: util.c
	$(CC) -c $^ -o $@

print_msgs.o: print_msgs.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o

cleanall:
	$(MAKE) clean
	cd libnmea && $(MAKE) clean && cd ..
