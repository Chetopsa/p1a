#include "utils.h"
#include <string.h>
#include <stdio.h>

// Create N files and distribute the data from the input file evenly among them
// See section 3.1 of the project writeup for important implementation details
void partition_file_data(char *input_file, int n, char *blocks_folder) {
    if(input_file == NULL || n < 1 || blocks_folder == NULL){
        return;
    }
    // Hint: Use fseek() and ftell() to determine the size of the file
    FILE* inp_file = fopen(input_file, "r"); //open in read mode
    if(inp_file == NULL){
        printf("failed to open file\n");
        return;
    }
    fseek(inp_file, 0, SEEK_END); //find size of file
    size_t size = ftell(inp_file);
    rewind(inp_file); //reset file pointer
    
    size_t block_size = size / n; //divide size of file by n
    size_t last_block_size = block_size + size % n; //add remainder for last blcok size

    FILE *fptr;
    
    // char buffer allocate;
    char *buffer = (char *)malloc(sizeof(size_t) * block_size);
    int i;
    //iterate thorugh n-1 files and write data to the blocks
    for(i = 0; i < n-1; i++){
        
        fread(buffer, 1, block_size, inp_file);
        char filename[PATH_MAX];
        sprintf(filename, "%s//%d.txt", blocks_folder, i);;
        fptr = fopen(filename, "w");
        fwrite(buffer, block_size, 1, fptr);
        fclose(fptr);
    }
    free(buffer);

    
    //calculate last file
    char* last_buffer = (char *)malloc(sizeof(size_t) * last_block_size);
    //char last_buffer[1000000];
    fread(last_buffer, 1, last_block_size, inp_file);
    char filename[PATH_MAX];
    sprintf(filename, "%s//%d.txt", blocks_folder, i);;
    fptr = fopen(filename, "w");
    fwrite(last_buffer, last_block_size,1, fptr);

    fclose(fptr);
    fclose(inp_file);
    free(last_buffer);
}

// ##### DO NOT MODIFY THIS FUNCTION #####
void setup_output_directory(char *block_folder, char *hash_folder) {
    // Remove output directory
    pid_t pid = fork();
    if (pid == 0) {
        char *argv[] = {"rm", "-rf", "./output/", NULL};
        if (execvp(*argv, argv) < 0) {
            printf("ERROR: exec failed\n");
            exit(1);
        }
        exit(0);
    } else {
        wait(NULL);
    }

    sleep(1);

    // Creating output directory
    if (mkdir("output", 0777) < 0) {
        printf("ERROR: mkdir output failed\n");
        exit(1);
    }

    sleep(1);

    // Creating blocks directory
    if (mkdir(block_folder, 0777) < 0) {
        printf("ERROR: mkdir output/blocks failed\n");
        exit(1);
    }

    // Creating hashes directory
    if (mkdir(hash_folder, 0777) < 0) {
        printf("ERROR: mkdir output/hashes failed\n");
        exit(1);
    }
}
