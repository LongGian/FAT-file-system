#include "file_system.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Creazione di un'istanza del file system
    FileSystem fs;
    fs.buffer_size = 1024;
    fs.buffer = malloc(fs.buffer_size);
    fs.current_directory.num_entries = 0;
    fs.current_directory.entries = NULL;

    // Creazione di un file
    createFile(&fs, "file1.txt");

    // Tentativo di creare un altro file con lo stesso nome
    createFile(&fs, "file1.txt");

    // Creazione di altri file
    createFile(&fs, "file2.txt");
    createFile(&fs, "file3.txt");
    createFile(&fs, "file4.txt");

    // Stampa del directory corrente
    printf("Current Directory:\n");
    for (int i = 0; i < fs.current_directory.num_entries; i++) {
        printf("- %s\n", fs.current_directory.entries[i].name);
    }

    // Cancellazione di un file esistente
    eraseFile(&fs, "file2.txt");

    // Tentativo di cancellare un file inesistente
    eraseFile(&fs, "file5.txt");

    // Stampa del directory corrente dopo la cancellazione
    printf("Current Directory:\n");
    for (int i = 0; i < fs.current_directory.num_entries; i++) {
        printf("- %s\n", fs.current_directory.entries[i].name);
    }

    // Deallocazione della memoria del buffer e delle voci del directory
    free(fs.buffer);
    free(fs.current_directory.entries);

    return 0;
}