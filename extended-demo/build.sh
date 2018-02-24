#!/bin/sh
# Build the extended LPCFI demo.

cc -c -o fptable.o ../fptable.c

# LPCFI lib
cc -c -o lpcfi.o ../lpcfi.c
ar rcs liblpcfi.a lpcfi.o fptable.o

# LPCFI demo.
cc -c -o extended-demo-lpcfi.o extended-demo.c
cc -o extended-demo-lpcfi extended-demo-lpcfi.o liblpcfi.a privileges.c

# PICFI demo.
cc -D PICFI -c -o extended-demo-picfi.o extended-demo.c
cc -o extended-demo-picfi extended-demo-picfi.o liblpcfi.a privileges.c
