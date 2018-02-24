#!/usr/bin/python2

import struct
import sys

CORRECT_PASSWORD   = "secret"
INCORRECT_PASSWORD = "wrong!"
FINISH_PASSWORD    = "finish"

sys.stderr.write("Enter what priv points to: ")
priv = raw_input().strip()
sys.stderr.write("Enter what nopriv points to: ")
nopriv = raw_input().strip()

# Incorrect password + unprivileged operation.
sys.stdout.write(INCORRECT_PASSWORD)
sys.stdout.write(struct.pack("P", int(nopriv, 16)))

# Correct password + privileged operation.
sys.stdout.write(CORRECT_PASSWORD)
sys.stdout.write(struct.pack("P", int(priv, 16)))

# Incorrect password + privileged operation (!!!).
sys.stdout.write(INCORRECT_PASSWORD)
sys.stdout.write(struct.pack("P", int(priv, 16)))

# This ends the demo - leave in place.
sys.stdout.write(FINISH_PASSWORD)

