# Opciones de compilación (Wall activa los warnings para código más seguro)
CFLAGS = -Wall -I include

# Archivos de código fuente y ejecutable final
SRC = src/main.c src/vm.c
TARGET = vm

# Regla principal
all:
	gcc $(SRC) $(CFLAGS) -o $(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)