import os
import subprocess
import argparse
import time
from datetime import datetime

from requests import head

# Assert that the user is running as root
if os.geteuid() != 0:
    exit("Root privileges are required to run this script")

# Parse arguments
parser = argparse.ArgumentParser()
parser.add_argument('--vuln', required=True)
parser.add_argument('--events', required=True, nargs='+')
parser.add_argument('--stress')
args = parser.parse_args()

# Run the processes
recording_proc = subprocess.Popen(args=['./build/src/record', *args.events])
time.sleep(0.5)
stress_proc = subprocess.Popen(args=['taskset', '0x1', 'stress'])
time.sleep(0.5)
start_time = round(datetime.now().timestamp() * 1000)
exploit_proc = subprocess.Popen(args=['taskset', '0x1', args.vuln])
exploit_proc.wait()
end_time = round(datetime.now().timestamp() * 1000)
recording_proc.wait()
stress_proc.kill()

# Dataset labeling
with open('out.csv') as f:
    data = list(map(lambda l: l.strip().split(','), f))
    headers = data[0]
    timestamp_index = headers.index('timestamp')
    headers.append('label')
    new_content = map(lambda row: [*row, '1'] if start_time < int(row[timestamp_index]) < end_time else [*row, '0'], data[1:])
    new_lines = [headers] + list(new_content)
    new_lines = map(lambda l: ','.join(l) + '\n', new_lines)
    with open('out_labeled.csv', 'w') as f:
        f.writelines(new_lines)