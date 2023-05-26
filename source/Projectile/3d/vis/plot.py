import sys
import projectile as proj


def main() -> None:
    try:
        filename = sys.argv[1]
    except IndexError:
        print(f"Simulation file {sys.argv[1]} not found. Using ../dump.out!")
        filename = "dump.out"
    obj = proj.Plotter(filename)
    obj.plot_data()


if __name__ == "__main__":
    main()
