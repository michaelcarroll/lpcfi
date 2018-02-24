# LPCFI demo

This demo is intended to present a weakness of PICFI
as overcome by LPCFI. Instructions to run the demo
are provided below.

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
  * This may be installed as `python2` or `python`; this
    document will assume it is installed as `python2`.

## Building
Simply run the `build.sh` script:

```
    sh buid.sh
```

## Demo Instructions
1. Build the demo binaries - `demo-lpcfi` and `demo-picfi` -
   according to the above build instructions.

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

## Extended Demo Instructions
The extended demo contains a vulnerability whereby an attacker may
modify the value of a function pointer whose value directly depends
upon the password entered by the user. When an incorrect password is
input, `op` should be set to the value of `nopriv` and then called, and
when the correct password ("secret") is input, `op` should be set to the
value of `priv` and then called. This loops until "finish" is input as the
password.

Observe the payload in `payload.py` - it,
   * on the first iteration, inputs the incorrect password and sets `op`
     to `nopriv`'s value (as expected by the programmer)
   * on the second iteration, inputs the correct password and sets `op` to
     `priv`'s value (also as expected by the programmer)
   * on the third iteration, inputs the incorrect password but sets `op` to
     `priv`'s value (which is unexpected by the programmer)
   * finally, ends the demo by inputting "finish" as the password.

1. Change to the extended demo directory.
```
        cd extended-demo
```

2. Build the demo binaries - `extended-demo-lpcfi` and `extended-demo-picfi` -
   according to the above build instructions.

3. Run
```
        python2 payload.py | ./extended-demo-picfi
```

4. The addresses of some functions will appear (attacking
   ASLR is orthogonal to our purposes).

   A prompt will appear asking for the value of `priv`
   Enter the value of `priv` as it appears
   *without the leading '0x'*.

5. Press enter.

6. Repeat steps 4 and 5 for `nopriv`.

7. Notice that PICFI allows the user to call the privileged operation
   on the third iteration since the privileged function has been
   activated.

8. Repeat steps 4 - 6 after running
```
        python2 payload.py | ./extended-demo-lpcfi
```

9. Notice that LPCFI prevents `op` from being called during the third
   iteration since it carries an illegal value unexpected by the
   programmer.

The payload may be modified for other combinations.

