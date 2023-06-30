import sys
import projectile as proj


def main() -> None:
    try:
        filename = sys.argv[1]
    except IndexError:
        filename = "dump.out"
        print(f"Simulation file {sys.argv[1]} not found. Using ../{filename}!")
    obj = proj.Plotter(filename)
    obj.plot_data()


if __name__ == "__main__":
    main()
