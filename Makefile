CFLAGS = -Wall -I include

SRC = src/main.c src/vm.c
TARGET = vm

all:
	gcc $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)