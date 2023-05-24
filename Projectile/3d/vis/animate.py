import projectile as proj


def main() -> None:
    filename = "../dump.out"

    obj = proj.Animator(filename)
    obj.animate_data()


if __name__ == "__main__":
    main()
