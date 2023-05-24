import os

try:
    import matplotlib.pyplot as plt
    import numpy as np
except ModuleNotFoundError:
    os.system("pip3 install -r requirements.txt")

def plot_data( filename: str) -> None:
    data = fetch_data(filename)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(
            data["pos_xs"],
            data["pos_zs"],
            data["pos_ys"]
            )
    plt.title("Projectile Trajectory")
    ax.set_xlabel("x pos")
    ax.set_ylabel("y pos")
    ax.set_zlabel("z pos")

    plt.grid()
    plt.show()


def main() -> None:
    filename = "../dump.out"
    plot_data( filename )


if __name__ == "__main__":
    main()
