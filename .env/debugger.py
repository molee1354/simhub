import gdb

def debugger(filename: str) -> None:
    print(f"Setting current file as {filename}...")
    gdb.execute("file "+filename)
    gdb.execute("set pagination off")
    gdb.execute("set print pretty on")
    gdb.execute("set verbose off")
    # gdb.execute("break src/FLIP_fluid.c:159")

    gdb.execute("run")

    # while True:
    #     id = gdb.parse_and_eval('id')
    #     qx = gdb.parse_and_eval('qx')
    #     max_p = gdb.parse_and_eval('fluid->maxParticles')
    #     print(f"id    = {id}")
    #     gdb.execute("continue")
    #     if int(id) > 100:
    #         break;
    id = gdb.parse_and_eval('id')
    qx = gdb.parse_and_eval('qx')
    max_p = gdb.parse_and_eval('fluid->maxParticles')
    print("id larger than max_p")
    print(f"\tmax_p = {max_p}")
    print(f"\tid    = {id}")
    print(f"\tqx    = {qx}\n")

def main() -> None:
    path = "simulation/bin/main"
    debugger(path)
    # gdb.execute('quit')


if __name__ == "__main__":
    main()
