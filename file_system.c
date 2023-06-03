#include "file_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    User wants to create a file
    -> Check if file already exists, if it doesnt proceed
    -> Find a free position in the buffer, if it's found proceed
    -> Update the directory entries
    -> Update the file system
*/

void createFile(FileSystem* fs, const char* filename) {
    DirectoryEntry* entries = fs->current_directory.entries;
    int num_entries = fs->current_directory.num_entries;

    for (int i = 0; i < num_entries; ++i) {
        if (strcmp(entries[i].name, filename) == 0) {
            printf("\nFile already exists.\n");
            return;
        }
    }

    int position = -1;
    for (int i = 0; i < fs->buffer_size; i += MAX_FILE_SIZE) {
        if (fs->buffer[i] == '\0') {
            position = i;
            break;
        }
    }

    if (position == -1) {
        printf("\n No free space available. \n");
        return;
    }

    DirectoryEntry new_entry;
    strcpy(new_entry.name, filename);
    new_entry.position = position;

    entries = realloc(entries, (num_entries + 1) * sizeof(DirectoryEntry));
    entries[num_entries] = new_entry;

    fs->current_directory.entries = entries;
    fs->current_directory.num_entries++;
}

/*
    User wants to delete a file
    -> Check if filename is in the directory entries, if found proceed
    -> Clear the file data in the buffer, 
       i.e. set to zero the a chunk of size MAX_FILE_SIZE
       starting at the found entry position
    -> Move the following blocks to the emptied position.
    -> Update the file system
*/

void eraseFile(FileSystem* fs, const char* filename) {
    DirectoryEntry* entries = fs->current_directory.entries;
    int num_entries = fs->current_directory.num_entries;

    for (int i = 0; i < num_entries; ++i) {
        if (strcmp(entries[i].name, filename) == 0) {
            memset(fs->buffer + entries[i].position, 0, MAX_FILE_SIZE);
            
            memmove(&entries[i], &entries[i + 1], (num_entries - i - 1) * sizeof(DirectoryEntry));
            entries = realloc(entries, (num_entries - 1) * sizeof(DirectoryEntry));

            fs->current_directory.entries = entries;
            fs->current_directory.num_entries--;
            return;
        }
    }
}