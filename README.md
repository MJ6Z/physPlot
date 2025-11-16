# physPlot
This project is a graphing library writtern in C++ for python, specifically for applications in Physics. The program uses openCV. An example python file, as well as demo images can be found in [python](/python)

## Dependencies 
This project requires an installation of openCV & pybind11 to compile. These are well known and easy to install.

```bash
sudo apt install pybind11-dev libopencv-dev
```

## Installation

Installation guide for Debian/Ubuntu Linux. Other OS's have not been tested, but would almost certainly work.

```bash
cd physPlot

#building the makefile.
mkdir build && cmake -B build/

#compliling my code.
cd build
make
cd ..

#copying the library file to the python/ directory.
cp /build/src/physPlot.cpython{Your OS}.so python/

#running the demo file.
cd python
python3 demo.py

```
## Disclaimer
This is an student project, and is not intented for real world use or development. But you're still welcome to have a look at what I've been getting up to!


