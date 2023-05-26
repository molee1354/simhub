
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
            arr = [line.strip().split() for line in lines][21:]

            data = [ [float(n) for n in line] 
                    for line in arr ]

            times = np.array([ datapoint[0] for datapoint in data ])
            pos_xs = np.array([ datapoint[1] for datapoint in data ])
            pos_ys = np.array([ datapoint[2] for datapoint in data ])
            pos_zs = np.array([ datapoint[3] for datapoint in data ])

            vel_xs = np.array([ datapoint[4] for datapoint in data ])
            vel_ys = np.array([ datapoint[5] for datapoint in data ])
            vel_zs = np.array([ datapoint[6] for datapoint in data ])

        return {
                "times" : times,
                "pos_xs" : pos_xs,
                "pos_ys" : pos_ys,
                "pos_zs" : pos_zs,
                "vel_xs" : vel_xs,
                "vel_ys" : vel_ys,
                "vel_zs" : vel_zs
                }


class Plotter(Projectile):
    def __init__(self, filename: str) -> None:
        super().__init__(filename)

    def plot_data(self) -> None:
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.plot(
                self.data["pos_xs"],
                self.data["pos_zs"],
                self.data["pos_ys"]
                )
        plt.title("Projectile Trajectory")
        ax.set_xlabel("x pos")
        ax.set_ylabel("z pos")
        ax.set_zlabel("y pos") # the z, y axes are flipped

        plt.grid()
        plt.show()


class Animator(Projectile):
    def __init__(self, filename: str) -> None:
        super().__init__(filename)

        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(projection='3d')

        self.trajectory, = self.ax.plot([],[],[], lw=1)
        self.disc, = self.ax.plot([],[],[], linestyle="", marker='o')

        self.ax.set_xlim((-.5*max(self.data["pos_xs"]),
                          max(self.data["pos_xs"])))
        self.ax.set_ylim((-.5*max(self.data["pos_zs"]),
                          max(self.data["pos_zs"])))
        self.ax.set_zlim((0,max(self.data["pos_ys"]))) # -> vertical axis

    def __update_trajectory(self, iter: int, trajectory, disc):
        trajectory.set_data( self.data["pos_xs"][:iter], self.data["pos_zs"][:iter] )
        trajectory.set_3d_properties( self.data["pos_ys"][:iter] )
        disc.set_data( self.data["pos_xs"][iter], self.data["pos_zs"][iter] )
        disc.set_3d_properties( self.data["pos_ys"][iter] )
        return trajectory, disc

    def animate_data(self) -> None:
        _ = animation.FuncAnimation(self.fig, self.__update_trajectory,
                                    fargs=(self.trajectory, self.disc),
                                    frames=len(self.data["pos_xs"]),
                                    interval=.2,
                                    blit=True)
        plt.show()
