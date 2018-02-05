#!/bin/sh
# Build the LPCFI demo.

gcc -c -o hashtable.o hashtable.c

# LPCFI lib
gcc -c -o lpcfi.o lpcfi.c
ar rcs liblpcfi.a lpcfi.o hashtable.o

# Demo
gcc -c -o demo.o demo.c
gcc -o demo-lpcfi demo.o liblpcfi.a

