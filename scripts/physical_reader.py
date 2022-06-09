#!/bin/python3
import time
import subprocess

p = subprocess.Popen(['./deps/meltdown/secret', '0x240000000'])
time.sleep(2)
p.kill()
