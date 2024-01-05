import pandas as pd
import matplotlib.pyplot as plt


def report(csv_path):
    with open(csv_path, 'r') as file:
        header = file.readline().strip()

    df = pd.read_csv(csv_path)
    columns = header.split(',')


    plt.figure()

    for col in columns[1:]:
       plt.plot(df['n'], df[col], label = col)


    plt.legend()
    plt.show()


if __name__ == "__main__":

    filename = "./build/results.csv"
    report(filename)
