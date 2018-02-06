#!/bin/sh
# Build the LPCFI demo.

gcc -c -o hashtable.o hashtable.c

# LPCFI lib
gcc -c -o lpcfi.o lpcfi.c
ar rcs liblpcfi.a lpcfi.o hashtable.o

# LPCFI demo.
gcc -c -o demo-lpcfi.o demo.c
gcc -o demo-lpcfi demo-lpcfi.o liblpcfi.a

# PICFI demo.
gcc -D PICFI -c -o demo-picfi.o demo.c
gcc -o demo-picfi demo-picfi.o liblpcfi.a
