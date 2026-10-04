CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = programa
OBJS = main.o grafo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c grafo.h
	$(CC) $(CFLAGS) -c main.c

grafo.o: grafo.c grafo.h
	$(CC) $(CFLAGS) -c grafo.c

run: $(TARGET)
	./$(TARGET)

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXT = .exe
else
    RM = rm -f
    EXT =
endif

clean:
	$(RM) $(OBJS) $(TARGET)$(EXT)