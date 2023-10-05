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

    if id > N-1 :
     ./child_process using exec() //left
     ./child_process using exec() //right

**within the child proccesses**
    Base Case:

    If id < N-1, then you're at a leaf node.
    Hash the single data block assigned to this leaf.
    Write the hash to an output file.
    Exit the process.

    Recursive Case:

    If id > n-1:

    Create 2 new child processes and distribute the data blocks evenly between these two subtrees.
    
    These child processes repeat the same process, hashing and combining blocks until reaching leaf nodes.

    Wait for both child processes to finish.

    Combine and hash the outputs of the two child processes to generate its own hash.
    Write this hash to an output file.
    Exit the process.

    Root Process:

    Root process waits for child processes to finish.
    Then combines and hashes their output hashes and writes final hash to file
    