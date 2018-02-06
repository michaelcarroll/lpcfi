#!/bin/sh
# Build the LPCFI demo.

cc -c -o hashtable.o hashtable.c

# LPCFI lib
cc -c -o lpcfi.o lpcfi.c
ar rcs liblpcfi.a lpcfi.o hashtable.o

# LPCFI demo.
cc -c -o demo-lpcfi.o demo.c
cc -o demo-lpcfi demo-lpcfi.o liblpcfi.a

# PICFI demo.
cc -D PICFI -c -o demo-picfi.o demo.c
cc -o demo-picfi demo-picfi.o liblpcfi.a
