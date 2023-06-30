# simhub

## About `simhub`

`simhub` is a lightweight simulation program built in C.

## Creating a Simulation

### Setting up the necessary local environment

To create a simulation, first clone this repository into your local machine:

        git clone https://github.com/molee1354/simhub.git

`cd` into the `simhub` directory that was just created:

        cd ./simhub

Before any simulation is created, the necessary Python virtual environment and the bash helper functions and commands must be loaded into the current shell session:

        . ./set-env

It is important that this command takes this exact form as this loads the Python virtual environment into the *current* working shell and not as a child process.

If the environment is properly loaded, the terminal will display a message that displays the paths to the current Python interpreter and the Python package manager. It should look something like this:

        Set Python interpreter to 
        [/**/.env/pyvenv-3.XX/bin/python3]
        Set Python Pip to 
        [/**/.env/pyvenv-3.XX/bin/pip3]

where the "XX" in `pyvenv-3.XX` should be the version number of the Python interpreter found on your machine.

### Loading a simulation

With the virtual environment and the bash helper functions set up, the simulation is now ready to be loaded. To load a simulation, run the `./set-sim` command followed by the desired simulation name. For example, this is how the 2d projectile simulation would be called:

        sim call projectile-2d

The above command will load the simulation with modifiable initial parameters. You should be able to see that within the current  directory, there is a new `./simulation` directory within which are the necessary files and functions for computation. Simulation names are simply the directory in which the `main.c` for the simulation lives, all in lower-case and separated by dashes instead of forward slashes. So from the above command, we can see that the `main.c` file for the 2d projectile simulation lives in the `./source/Projectile/2d/` directory.

### Running the simulation

To compile and run the simulation, simply run the `sim run` command in the terminal:

        sim run

This command compiles the necessary files and runs the simulation after the compilation is done. To simply compile the simulation without running it, use the `sim make` command.

The simulation will output to the terminal the calculated values in real time. Once the computation is successful the simulation will exit with a

        Done!

prompted out to the terminal, and the values of the simulation will be saved in a `dump.out` file. The name of this file can be modified in the `sim.input` file as desired.

### Visualization

Simulations that support visualizations have a `./vis/` file within the simulation directory. To visualize the simulation, either run the

        sim plot

command to plot the simulation, and

        sim anim

to visualize the simulation.
