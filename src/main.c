#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, char** argv) {
    // Check if file format is ok
    if (argc < 2) {
        printf("Use: %s <archivo.bin>.\n", argv[0]);
        return 1;
    }

    // Read binary file
    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error: File could not be opened %s.\n", argv[1]);
        return 1;
    }

    VirtualMachine vm;
    vm_init(&vm);

    // Store all bytes from the file to the Memory
    size_t bytes_read = fread(vm.memory, 1, MEMORY_SIZE, file);
    printf("Cargados %zu bytes en la memoria.\n", bytes_read);
    
    fclose(file);
    vm_run(&vm);

    return 0;
}