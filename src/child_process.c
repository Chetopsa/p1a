#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "hash.h"

#define PATH_MAX 1024

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./child_process <blocks_folder> <hashes_folder> <N> <child_id>\n");
        return 1;
    }

    char* blocks_folder = argv[1];
    char* hashes_folder = argv[2];
    int N = atoi(argv[3]);
    int child_id = atoi(argv[4]);

    FILE *fptr;

    pid_t child1;
    pid_t child2;

    // TODO: If the current process is a leaf process, read in the associated block file 
    // and compute the hash of the block.
    if(child_id >= N-1){
        //read in data from correct block
        char block[100];
        int block_num = child_id - N + 1;
        sprintf(block, "%s/%d.txt", blocks_folder, block_num);
        char block_hash[SHA256_BLOCK_SIZE * 2 + 1];
        //compute hash
        hash_data_block(block_hash, block);
        char hash_file[PATH_MAX];
        sprintf(hash_file, "%s/%d.out", hashes_folder, child_id);
        fptr = fopen(hash_file, "w");
        if(fptr == NULL){
            printf("failed to open file\n");
            return 1;
        }
    
        fwrite(block_hash, (SHA256_BLOCK_SIZE * 2 + 1) ,1, fptr);
        fclose(fptr);
    }

    
    

    // TODO: If the current process is not a leaf process, spawn two child processes using  
    // exec() and ./child_process. 
    else{
        child1 = fork(); //create left child_process
        if(child1 == 0){
            char right[64];
            sprintf(right, "%d", 2*child_id+2);
            //execute next processes
            execl("./child_process", "template/child_process", blocks_folder, hashes_folder, argv[3], right, NULL);
        }

        child2 = fork(); //create right child_process
        if(child2 == 0){
            //get next id for left and right processes
            char left[64];
            sprintf(left, "%d", 2*child_id+1);
            execl("./child_process", "template/child_process", blocks_folder, hashes_folder, argv[3], left, NULL);
        }
    }
    if(child_id < N-1){
        // TODO: Wait for the two child processes to finish
        wait(NULL);
        wait(NULL);
        // TODO: Retrieve the two hashes from the two child processes from output/hashes/
        // and compute and output the hash of the concatenation of the two hashes.
        
        //read left hash
        char left_hash_file[PATH_MAX];
        int left_num = (child_id*2 + 1);
        sprintf(left_hash_file, "%s/%d.out", hashes_folder, left_num);

        char left_hash[SHA256_BLOCK_SIZE * 2 + 1];
        fptr = fopen(left_hash_file, "r");
        if(fptr == NULL){
            printf("failed to open file\n");
            return 1;
        }
        fread(left_hash, 1, (SHA256_BLOCK_SIZE * 2 + 1), fptr);
        fclose(fptr);

        //read right hash
        char right_hash_file[PATH_MAX];
        int right_num = (child_id*2 + 2);
        sprintf(right_hash_file, "%s/%d.out", hashes_folder, right_num);

        char right_hash[SHA256_BLOCK_SIZE * 2 + 1];
        fptr = fopen(right_hash_file, "r");
        if(fptr == NULL){
            printf("failed to open file\n");
            return 1;
        }
        fread(right_hash, 1, (SHA256_BLOCK_SIZE * 2 + 1), fptr);
        fclose(fptr);

        //combine hashes
        char combo_hash[SHA256_BLOCK_SIZE * 2 + 1];
        compute_dual_hash(combo_hash, left_hash, right_hash);
        //write to file
        char file[PATH_MAX];
        sprintf(file, "%s/%d.out", hashes_folder, child_id);
        fptr = fopen(file, "w");
        fwrite(combo_hash, (SHA256_BLOCK_SIZE * 2 + 1) , 1, fptr);
    }

    return 0;
}

