#!/usr/bin/python2

import struct
import sys

sys.stderr.write("fp within foo(1): ")
x = raw_input().strip()
sys.stderr.write("fp within foo(0): ")
y = raw_input().strip()

sys.stdout.write(struct.pack("L", int(x, 16)))
sys.stdout.write(struct.pack("L", int(y, 16)))
