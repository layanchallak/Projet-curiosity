# Curiosity — Robot Exploration in C

## 📌 Description
**Curiosity** is a university project developed in **C** during my Bachelor's degree in Computer Science.
The project focuses on simulating a robot exploring a terrain. It includes the management of terrains and environments, robot movements, program interpretation, data structures, and terrain generation.
This project was developed as part of my computer science studies to practice **C programming**, **modular programming**, **compilation with Makefiles**, and the design of a multi-file software project.

## 🛠️ Technologies

* **C**
* **Clang**
* **Make / Makefile**
* Standard C libraries


## ⚙️ Compilation

Make sure you have a C compiler and `make` installed.

To compile all programs:

```bash
make
```

The Makefile uses **Clang** with warning options enabled:

```bash
CC=clang -Wall
```

You can also compile a specific program:

```bash
make curiosity
```

For example:

```bash
make test_terrain
make test_robot
make robot_terrain
make curiosity
make curiosity-test
make test_generation_terrains
make curiosity-perf
```

## ▶️ Running the Programs

After compilation, the generated executables can be launched directly.

For example:

```bash
./curiosity
```

To run the terrain tests:

```bash
./test_terrain
```

To run the robot tests:

```bash
./test_robot
```

## 📊 Performance

The project also includes a performance program:

```bash
./curiosity-perf
```

It is used to evaluate the execution performance of the Curiosity program and the terrain generation system.

## 🧹 Cleaning the Project

To remove compiled executables and object files:

```bash
make clean
```
## 👤 Author

**Layan Challak & Leila Bouricha**

Université Grenoble Alpes
