# CSCI 4061: Introduction to Operating Systems Project

**Project Group:** 128

**Group Members:**
- Chesont Opsasnick (opsas002)
- Ahmed Kadar (kadar008)

**CSELabs Computer Used for Testing:** login03.cselabs.umn.edu

# Changes
**merkle.c** read in the command line arguments and added them to the 
**utils.c** implemented the partion_file_data;

# implementing merkel tree
Initialization:

    Determine the total number of data blocks.
    Spawn the root process in merkele and run child_process.c

How to spawn child proccesses:

    id = 0
    while(id < n - 1)
        left_pid = fork()
        if(left_pid == 0){
            id = 2*id + 1
            //left node
        }
        right_pid = fork();
        if(right_pid == 0){
            id = 2 * id + 2
            //right node
        }

**within the child proccesses**
    Base Case:

    If N == 1, then you're at a leaf node.
    Hash the single data block assigned to this leaf.
    Write the hash to an output file.
    Exit the process.

    Recursive Case:

    If N > 1:
    Create two child processes by iterating again. Distribute the data blocks evenly between these two subtrees.
    
    These child processes repeat the same process, hashing and combining blocks until reaching leaf nodes.

    Wait for both child processes to finish.

    Combine and hash the outputs of the two child processes to generate its own hash.
    Write this hash to an output file.
    Exit the process.

    Root Process:

    Root process waits for child processes to finish.
    Then combines and hashes their output hashes and writes final hash to file
    
    Exit the process.
    
    Tree Construction:

    This recursive process constructs a binary tree structure, with each node (process) having two child nodes, except for the leaf nodes that hash individual data blocks.
    The root process is responsible for the final hash that represents the entire Merkle tree.
    