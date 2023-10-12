# CSCI 4061: Introduction to Operating Systems Project

**Project Group:** 128

**Group Members:**
- Cheston Opsasnick (opsas002)
- Ahmed Kadar (kadar008)
- Ahmed-dahir Dayib (dayib007)

**CSELabs Computer Used for Testing:** csel-kh1250-01.cselabs.umn.edu

# Changes
**merkle.c** read in the command line arguments and created root child_process 
**utils.c** implemented the partion_file_data;
**child_process.c** implemented the main function

# Contributions
Ahmed-dahir Dayib - Wrote Read me and Psuedo code, helped debug and wrote error checks
Ahmed Kadar - Wrote parition_file_data_implmentation
Cheston Opsasnick - Wrote child_proccess.c

# implementing merkel tree
Initialization:

    Determine the total number of data blocks.
    Spawn the root process in merkele and run child_process.c

How to spawn child proccesses:

    if id < N-1 :
    fork()
     ./child_process using exec() //left
    fork()
     ./child_process using exec() //right

**within the child proccesses**
    Base Case:

    If id > N-1, then you're at a leaf node.
    Hash the single data block assigned to this leaf.
    Write the hash to an output file.
    Exit the process.

    Recursive Case:

    If id < n-1:

    Create 2 new child processes and distribute the data blocks evenly between these two subtrees.
    
    These child processes repeat the same process, hashing and combining blocks until reaching leaf nodes.

    Wait for both child processes to finish.

    Combine and hash the outputs of the two child processes to generate its own hash.
    Write this hash to an output file.
    Exit the process.

    Root Process:

    Root process waits for child processes to finish.
    Then combines and hashes their output hashes and writes final hash to file

**How Our psuedo code changed:**
The main process was the same, but we had to correct some minor errors, 
like including the fork() and switching a comparison, (>) to (<)

    