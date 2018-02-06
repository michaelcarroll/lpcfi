# LPCFI demo

This demo is intended to present a weakness of PICFI
as overcome by LPCFI. An explanation of the demo is
provided within the poster, and instructions to run
the demo are provided below.

## Implementation
LPCFI is implemented naively with a basic hash table serving
as the fp-table. PICFI is not implemented but simulated. If
a function address has been activated, the PICFI simulation
regards such function as a legal target for any indirect call.
This is more coarse than PICFI, but irrelevant for this demo.

The C code from the poster is available in `demo.c`.

## Dependencies
* Unix-like system
* C compiler (at `cc`)
* `ar` to create a static library
* Python 2

## Building
Simply run the `build.sh` script:

```
    sh buid.sh
```

## Instructions
1. Build the demo binaries - `demo-lpcfi` and `demo-picfi` -
   according to the above build instructions

2. In a shell, run:
```
        python2 payload.py | ./demo-picfi
```

3. The addresses of some functions will appear (attacking
   ASLR is orthogonal to our purposes).

   A prompt will appear asking for the desired value of
   `fp` when `foo` is called with argument `n = 1`. Enter
   the value of `g` as it appears *without the leading '0x'*.
4. Press enter.

5. A second prompt will appear asking for the desired value of
   `fp` when `foo` is called with argument `n = 0`. Enter the
   value of `g` again as before.

6. Notice that PICFI allows `g` to be called during the second `foo`
   call despite that the only legal target at that point is `h`.

7. Repeat steps 3 - 5 after running
```
        python2 payload.py | ./demo-lpcfi
```

8. Notice that LPCFI prevents `g` from being called during the second
   `foo` call.

Other combinations may be input into the payload.
