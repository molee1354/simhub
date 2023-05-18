import os

try:
    import matplotlib.pyplot as plt
    import numpy as np
except ModuleNotFoundError:
    os.system("pip3 install -r requirements.txt")


def fetch_data( filename: str ) -> dict:
    with open( filename, 'r' ) as file:
        lines = file.readlines()
        arr = [line.strip().split() for line in lines][17:]

        data = [ [float(n) for n in line] 
                          for line in arr ]

        times = np.array([ datapoint[0] for datapoint in data ])
        pos_xs = np.array([ datapoint[1] for datapoint in data ])
        pos_ys = np.array([ datapoint[2] for datapoint in data ])
        vel_xs = np.array([ datapoint[3] for datapoint in data ])
        vel_ys = np.array([ datapoint[4] for datapoint in data ])

    return {
        "times" : times,
        "pos_xs" : pos_xs,
        "pos_ys" : pos_ys,
        "vel_xs" : vel_xs,
        "vel_ys" : vel_ys
    }


def plot_data( filename: str) -> None:
    data = fetch_data(filename)
    
    plt.plot(
        data["pos_xs"],
        data["pos_ys"]
    )
    plt.title("Projectile Trajectory")
    plt.xlabel("x pos")
    plt.ylabel("y pos")
    plt.grid()
    plt.show()


def main() -> None:
    filename = "../dump"
    plot_data( filename )


if __name__ == "__main__":
    main()
