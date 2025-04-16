CC = gcc
CFLAGS = -g -Wall -Iinclude
SRC = src/main.c src/prompt.c src/input.c src/parser.c src/executor.c
BIN = bin/qunish

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)
