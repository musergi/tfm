from ast import arg, parse
from operator import sub
import os
import subprocess
import argparse
import time

if os.geteuid() != 0:
    exit("Root privileges are required to run this script")

parser = argparse.ArgumentParser()
parser.add_argument('--vuln', required=True)
parser.add_argument('--events', required=True, nargs='+')
args = parser.parse_args()

recording_proc = subprocess.Popen(args=['./build/src/record', *args.events])
time.sleep(1)
exploit_proc = subprocess.Popen(args=['taskset', '0x1', args.vuln])
exploit_proc.wait()
recording_proc.wait()
