TARGET = krishnamoorthynatarajanke_proj1.exe
SRC = krishnamoorthynatarajanke_proj1.c
INC = krishnamoorthynatarajanke_proj1.h
CC = gcc
CFLAGS = -pthread

all: $(TARGET)

krishnamoorthynatarajanke_proj1.exe: $(SRC) $(INC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
