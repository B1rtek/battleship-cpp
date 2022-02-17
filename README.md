# Battleship-cpp

[My Battleship game](https://github.com/B1rtek/battleship-py) rewritten in C++, with a GUI made in Qt5

## Requirements:

* Windows: none since all files that this game needs to run are included
* Linux: Qt5, you can install it through the package manager

## Usage:

To launch the game, execute the `battleship-(your system goes here)` file, or if you want to play in
console, `battleship-cli` (although this one might not work on linux in some cases). To launch the game in the console
mode from the main executable, execute:

```shell
$ battleship-win32 --no-ui
```

Or, on Linux:

```shell
$ ./battleship-linux --no-ui
```

The terminal version has terrible controls, to show help, just type `help` and press enter. Also, your terminal should
be at least 36 lines tall.

## Building

Regardless of the OS, to build just run these commands (from project root):

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Both versions (the GUI and the terminal-only) will be built this way. You can specify the target (
with `--target battleship-win32` for example) if you don't need both of them. Compilation was done using the GNU
compiler, and all dlls included are compatible with it.

This project uses the [JSON for Modern C++](https://github.com/nlohmann/json) library
by [Niels Lohmann](https://github.com/nlohmann) and [Argparse](https://github.com/p-ranav/argparse) library
by [Pranav](https://github.com/p-ranav)
