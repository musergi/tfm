import argparse
from string import printable
import pandas as pd
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument('--dataset', required=True)
parser.add_argument('--column', required=True)
args = parser.parse_args()

df = pd.read_csv(args.dataset)
df['timestamp'] = pd.to_datetime(df['timestamp'], unit='ms')
print(df.head())
if args.column is None:
    printable_cols = list(df.columns)
    printable_cols.remove('timestamp')
    fig, axs = plt.subplots(len(printable_cols))
    for ax, col in zip(axs, printable_cols):
        ax.plot(df['timestamp'], df[col])
        ax.set_title(col)
    plt.show()
else:
    plt.plot(df['timestamp'], df[args.column])
    plt.xlabel('Timestamp')
    if args.column.islower():
        plt.ylabel(args.column.capitalize())
    else:
        plt.ylabel(args.column)
    plt.show()