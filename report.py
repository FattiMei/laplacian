import sys
import pandas as pd
import matplotlib.pyplot as plt


def report(csv_path):
    with open(csv_path, 'r') as file:
        header = file.readline().strip()

    df = pd.read_csv(csv_path)
    columns = header.split(',')


    plt.figure()

    for col in columns[1:]:
       plt.semilogy(df['n'], df[col], label = col)


    plt.legend()
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python report.py <csv_file_path>")
        sys.exit(1)

    report(sys.argv[1])
