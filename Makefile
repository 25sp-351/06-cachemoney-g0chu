all: money

OBJS = main.o money_cache.o money_conversion.o
CC = gcc
CFLAGS = -Wall

money: $(OBJS)
	$(CC) $(CFLAGS) -o money $(OBJS)

main.o: main.c money_cache.h
	$(CC) $(CFLAGS) -c main.c

money_cache.o: money_cache.c money_cache.h money_conversion.h
	$(CC) $(CFLAGS) -c money_cache.c

money_conversion.o: money_conversion.c money_conversion.h
	$(CC) $(CFLAGS) -c money_conversion.c

clean:
	rm -f money $(OBJS)
