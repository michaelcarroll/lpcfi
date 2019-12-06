# Live Path Control Flow Integrity (LPCFI) demonstration

This demo is intended to present a weakness of PICFI
as overcome by LPCFI for our presentation on Control Flow Integrity for CSCI-340. Instructions to run the demo
are provided below.

Forked from https://github.com/mbarbar/lpcfi.

## Implementation
LPCFI is implemented naively with a basic hash table serving
as the fp-table. PICFI is not implemented but simulated. If
a function address has been activated, the PICFI simulation
regards such function as a legal target for any indirect call.
This is more coarse than PICFI, but irrelevant for this demo.

The C code from the poster is available in `demo.c`.

## Dependencies 
* Unix system (The CSB/SJU Linux Student Pool will work)
* C compiler
* Python 2
  * This may be installed as `python2` or `python`; this
    document will assume it is installed as `python2`.
    
## Log into VMware Horizon
    
## Cloning Repository
Clone the repository by running this command in the terminal:

```
        git clone github.com/michaelcarroll/lpcfi
```

## Building
Change the directory to the cloned repository:

```
        cd lpcfi
```

Run the `build.sh` script:

```
    sh buid.sh
```

## Demonstration of Per-input Control Flow Integrity (PICFI)
1. In the terminal, run:
```
        python2 payload.py | ./demo-picfi
```

   A prompt will appear asking for the desired value of
   `fp` when `foo` is called with argument `n = 1`. 
   
   Enter the value of `g` as it appears *without the leading '0x'*.
   
2. Press enter.

3. A second prompt will appear asking for the desired value of
   `fp` when `foo` is called with argument `n = 0`. 
   
   Enter the value of `g` again as before.

4. Notice that PICFI allows `g` to be called during the second `foo`
   call despite that the only legal target at that point is `h`.

## Demonstration of Live Path Control Flow Integrity (LPCFI)
1. In the terminal, run:
```
        python2 payload.py | ./demo-lpcfi
```

   A prompt will appear asking for the desired value of
   `fp` when `foo` is called with argument `n = 1`. 
   
   Enter the value of `g` as it appears *without the leading '0x'*.
   
2. Press enter.

3. A second prompt will appear asking for the desired value of
   `fp` when `foo` is called with argument `n = 0`. 
   
   Enter the value of `g` again as before.

4. Notice that LPCFI prevents `g` from being called during the second
   `foo` call.

