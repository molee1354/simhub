
import os

try:
    import matplotlib.pyplot as plt
    import matplotlib.animation as animation
    import numpy as np
except ModuleNotFoundError:
    os.system("pip3 install -r requirements.txt")


class Projectile:
    def __init__(self, filename: str) -> None:
        self.filename = filename
        self.data = self.__fetch_data()

    def __fetch_data(self) -> dict:
        with open( self.filename, 'r' ) as file:
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


class Plotter(Projectile):
    def __init__(self, filename: str) -> None:
        super().__init__(filename)

    def plot_data(self) -> None:
        fig, ax = plt.subplots()
        ax.plot(
                self.data["pos_xs"],
                self.data["pos_ys"],
                )
        ax.set_title("Projectile Trajectory")
        ax.set_xlabel("x pos")
        ax.set_ylabel("y pos")

        plt.grid()
        plt.show()


class Animator(Projectile):
    def __init__(self, filename: str) -> None:
        super().__init__(filename)

        self.fig, self.ax = plt.subplots()

        self.trajectory, = self.ax.plot([],[], lw=1)
        self.disc, = self.ax.plot([],[], linestyle="", marker='o')

        self.ax.set_xlim((0,max(self.data["pos_xs"])))
        self.ax.set_ylim((0,max(self.data["pos_ys"])))

    def __update_trajectory(self, iter: int, trajectory, disc):
        trajectory.set_data( self.data["pos_xs"][:iter], self.data["pos_ys"][:iter] )
        disc.set_data( self.data["pos_xs"][iter], self.data["pos_ys"][iter] )
        return trajectory, disc

    def animate_data(self) -> None:
        _ = animation.FuncAnimation(self.fig, self.__update_trajectory,
                                    fargs=(self.trajectory, self.disc),
                                    frames=len(self.data["pos_xs"]),
                                    interval=.2,
                                    blit=True)
        plt.show()
