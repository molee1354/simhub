import os

try:
    import matplotlib.pyplot as plt
    import matplotlib.animation as animation
    import seaborn as sns
    import numpy as np
    from matplotlib.colors import LinearSegmentedColormap
except ModuleNotFoundError:
    os.system("pip3 install -r requirements.txt")
    import matplotlib.pyplot as plt
    import matplotlib.animation as animation
    import seaborn as sns
    import numpy as np
    from matplotlib.colors import LinearSegmentedColormap


class GameOfLife:
    def __init__(self, filename: str) -> None:
        self.filename = filename
        self.data = self.__fetch_data()

    def __fetch_data(self) -> np.ndarray:
        if not os.path.exists(self.filename):
            raise FileNotFoundError(
                    f"Input file \"{self.filename}\" not found! " \
                            "Make sure to run the \"sim run\" command " \
                            "to compile and run the simulation."
                            )
        out = []
        with open( self.filename, 'r' ) as file:
            line = [l.strip().split() for l in file.readlines()]
            board = []
            for l in line:
                if len(l) == 0:
                    continue
                elif l[0] == "Timestep":
                    if len(board) == 0:
                        continue
                    else:
                        out.append(board)
                    board = []
                else:
                    board.append(l)
        return np.array(out, dtype=np.int8)


class Animator(GameOfLife):

    def __init__(self, filename: str) -> None:
        super().__init__(filename)

        self.fig, self.ax = plt.subplots()
        self.myColorsBW = (
            (0.8,0.8,0.8,1), 
            (0,0,0,1)
        )
        self.colorsBW = LinearSegmentedColormap.from_list('Custom',
                                                          self.myColorsBW,
                                                          len(self.myColorsBW))

    def __update_state(self, iter: int) -> None:
        self.ax.cla()
        self.ax.set_title(f"Timestep {iter}")
        sns.heatmap( self.data[iter, ...],
                ax = self.ax,
                cmap = self.colorsBW,
                cbar = False,
                square = True,
                xticklabels = False,
                yticklabels = False
                )

    def animate_data(self) -> None:
        _ = animation.FuncAnimation(self.fig, self.__update_state,
                                    frames = len(self.data),
                                    interval=50.,
                                    blit=False)
        plt.show()

