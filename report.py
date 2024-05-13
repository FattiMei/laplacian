#!/usr/bin/env python3

import sys
import pandas as pd
import matplotlib.pyplot as plt


def report(csv_path):
    with open(csv_path, 'r') as file:
        title  = file.readline().strip()

        if not title.startswith('#'):
            header = title
        else:
            title  = title[len('# '):]
            header = file.readline().strip()


    df = pd.read_csv(csv_path, comment = '#')
    columns = header.split(',')


    plt.figure()
    plt.title(title)

    for col in columns[1:]:
       plt.semilogy(df[columns[0]], df[col], label = col)


    plt.legend()
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python report.py <csv_file_path>")
        sys.exit(1)

    report(sys.argv[1])
