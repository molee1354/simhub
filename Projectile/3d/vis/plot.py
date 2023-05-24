import projectile as proj


def main() -> None:
    filename = "../dump.out"

    obj = proj.Plotter(filename)
    obj.plot_data()


if __name__ == "__main__":
    main()
