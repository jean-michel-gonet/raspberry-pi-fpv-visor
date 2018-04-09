# raspberry-pi-fpv-visor
A simple FPV visor that captures the raspberry's camera input and displays it in full screen, with some OSD data

Directory structure:
- lib: All complex functionality resides here. All implementation have unit testing
	- src: classes.
	- include: headers, to be included from application
	- test: tests.
- app: The standalone executable, and classes depending directly on hardware.

To build:

Go to the root folder:
cd raspberry-pi-fpv-visor

Create the build folder:
mkdir build
cd build
cmake ../src
make

Launch the application:
app/fpv

Enjoy!
