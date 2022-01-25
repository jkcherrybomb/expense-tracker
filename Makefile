SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))

CFLAGS = `pkg-config gtk+-3.0 --cflags`
LIBS = `pkg-config gtk+-3.0 --libs`

CFLAGS += -ggdb
LIBS += -fsanitize=address

all: $(OBJS)
	gcc $(OBJS) -o main $(LIBS)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm *.o
	rm main