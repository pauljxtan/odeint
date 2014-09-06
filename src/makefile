CC = gcc
#CC = clang
CFLAGS = -g -Wall
INCLUDES = -I../include
LFLAGS = -L../lib
LIBS = -lm
SRCS = bulsto.c eoms.c fweuler.c integrate.c rk4.c
OBJS = $(SRCS:.c=.o)
MAIN = integrate

.PHONY: depend clean

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm *.o $(MAIN)
