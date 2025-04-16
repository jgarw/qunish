# Default QNX build (make)
CC_QNX = qcc
CFLAGS_QNX = -V gcc_ntoaarch64le -Wall -Iinclude 
CC_X86 = gcc
CFLAGS_X86 = -g -Wall -Iinclude 

SRC = src/main.c src/prompt.c src/parser.c src/executor.c
BIN = bin/qunish

# Default target
all: qnx

qnx: $(SRC)
	$(CC_QNX) $(CFLAGS_QNX) $(SRC) -o $(BIN) -lreadline

x86: $(SRC)
	$(CC_X86) $(CFLAGS_X86) $(SRC) -o $(BIN) -lreadline

clean:
	rm -f $(BIN)
