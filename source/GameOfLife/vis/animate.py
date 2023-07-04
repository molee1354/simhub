import sys
import gameoflife as gol


def main() -> None:
    try:
        filename = sys.argv[1]
    except IndexError:
        filename = "dump.out"
        print(f"Simulation file {sys.argv[1]} not found. Using ../{filename}!")
    obj = gol.Animator(filename)
    obj.animate_data()


if __name__ == "__main__":
    main()
