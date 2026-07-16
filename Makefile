CFLAGS = -Wall -I include

SRC = src/main.c src/vm.c
TARGET = vm

all:
	gcc $(SRC) $(CFLAGS) -o $(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)