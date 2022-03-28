TARGET = prod_cons.exe
SRC = prod_cons.c
INC = prod_cons.h
CC = gcc
CFLAGS = -pthread

all: $(TARGET)

prod_cons.exe: $(SRC) $(INC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
