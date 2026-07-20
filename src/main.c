#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, char** argv) {
    bool debug_mode = false;
    char* file_path = NULL;

    // Activate flag of debug_mode
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debug_mode = true;
        } else {
            file_path = argv[i];
        }
    }

    // Check if file format is ok
    if (file_path == NULL) {
        printf("Use: %s <file.bin> [-d]\n", argv[0]);
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
    vm_run(&vm, debug_mode);

    return 0;
}