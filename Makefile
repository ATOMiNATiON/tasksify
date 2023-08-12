CC = clang
CFLAGS = -Wall -Wextra -Werror -Wstrict-prototypes -pedantic -gdwarf-4
LFLAGS = -lm

EXEC = task
OBJS = task.o

.PHONY: all clean
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build:
	scan-build --use-cc=$(CC) make
