import sys
import gameoflife as gol


def main() -> None:
    try:
        dumps_dir = sys.argv[1]
    except IndexError:
        dumps_dir = "../dumps"
        print(f"Simulation directory not found. Using {dumps_dir}!")
    obj = gol.Animator(dumps_dir)
    obj.animate_data()


if __name__ == "__main__":
    main()
