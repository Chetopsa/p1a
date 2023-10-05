# CSCI 4061: Introduction to Operating Systems Project

**Project Group:** 128

**Group Members:**
- Chesont Opsasnick (opsas002)
- Ahmed Kadar (kadar008)

**CSELabs Computer Used for Testing:** login03.cselabs.umn.edu

# Changes
**merkle.c** read the command line arguments and added them to the 

## Project Description

This project involves the implementation of a binary Merkle Tree using the C programming language and various system calls. The goal is to efficiently hash data blocks from a file and build a Merkle tree structure. The resulting tree is used for data verification and is a crucial concept in various software systems such as Bitcoin, Git, and Cassandra.

## Project Structure

- **include/:** Header files (hash.h, print_tree.h, sha256.h, utils.h)
- **lib/:** Compiled library files (hash.o, print_tree.o, sha256.o)
- **src/:** Source code files (merkle.c, child_process.c, utils.c)
- **input/:** Input text files (e.g., T1.txt, T2.txt, T3.txt)
- **expected/:** Expected visualization files (e.g., T1.txt, T2.txt, T3.txt)
- **output/:** Program results (generated during execution)
- **Makefile:** Build and test instructions

## Compilation Instructions

$ make all
