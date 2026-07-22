CFLAGS = -Wall -I include

SRC = src/main.c src/vm.c
	TARGET = vm.exe

all:
	gcc $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	# Usamos del para compatibilidad con Windows CMD/PowerShell
	del /Q /F $(TARGET)