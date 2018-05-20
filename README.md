# raspberry-pi-fpv-visor
A simple FPV visor that captures the raspberry's camera input and displays it in full screen, with some OSD data

Directory structure:
- lib: All complex functionality resides here. All implementation have unit testing
	- src: classes.
	- include: headers, to be included from application
	- test: tests.
- app: The standalone executable, and classes depending directly on hardware.

# Prepare hardware

I assume that you have a newly installed _Raspberry PI_. This is what you need:
- Activate the camera
- Activate I2C bus
- Install openCV
- Install gtk
- Install git
- Install cmake
- Download and compile
- Auto-run it at boot
- Deactivate the idle screen

## Activate camera
Why? This is pretty obvious: you need a camera to perform the _View_ part of _First Person View_

Easiest way is to do it from the desktop:
- _Raspberry_ --> _Preferences_
- Open _Interfaces_ tab
- _Enable_ the _Camera_ (while you're at it, activate also I2C, see below)

To check that the camera works, type
```bash
raspistill -f -t 0
```

You should be able to see images from camera. Exit with ``Ctrl+C``

## Driver v4L2
Why? Because OpenCV uses it to capture images from the camera.

Driver is present by default, but not active. To activate it:

```bash
sudo modprobe bcm2835-v4l2
ls /dev/video0
```

To activate it by default when the Raspberry is booted, edit file ``/etc/modules`` and add the
following snippet at the bottom:

```bash
bcm2835-v4l2
``

## Activate I2C interface
Why? Currently, this project connects to https://github.com/jean-michel-gonet/pic18f-bldc-controller.X using
I2C interface. If you have other plans, you can skip this part. 

Easiest way is to do it from the desktop:
- _Raspberry_ --> _Preferences_
- Open _Interfaces_ tab
- _Enable_ the _I2C_ interface

To check that I2C interface is present, verify that the device exists:

```bash
$ ls /dev/i2*
/dev/i2c-1
```

You can also make a check with _i2ctools_:

```bash
$ i2cdetect -V
i2cdetect version 3.1.2
$ i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- 0c 0d 0e 0f 
10: 10 11 12 13 14 15 16 17 -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --
```

# Prepare tooling
As the project is distributed as compilable sources, you need some development tooling.

## Install git
Why? Because it is the easiest way to download all sources in a consistent and predictable manner, and to keep up
with updates later. If you know what you do, you can also obtain sources as a ZIP archive from this repository. 

Probably it is already installed. If not, use the following command:

```bash
sudo apt-get install git
```

And verify it with:
```bash
git --version
```

## Install cmake
Why? Because the project is prepared to build with this tool. It is a cross platform ``Makefile`` generator, 
and makes things easier.

```bash
sudo apt-get install cmake
```

And verify it with:
```bash
cmake --version
```

You need to have a version higher than 3.1


# Prepare dependencies

## pkg-config
Why? Because it is a common tool to handle dependencies between projects, and cmake uses it.

It is very probably installed in your machine. To verify it:

```bash
$ pkg-config --version
0.29
$ pkg-config --list-all
...
udev               udev - udev
python2            Python - Python library
...
```

If not, install it with:

```bash
sudo apt-get install pkg-config
```

## opencv
Why? Because this project, as many others, use it to process images.

```bash
sudo apt-get install build-essential # compiler
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev # required
sudo apt-get install python-dev python-numpy libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev # optional
```

When some libraries were missing, I followed the suggestion of using ``--fix-missing``. Also, ``libtbb2`` and 
``libtbb2-dev`` are not available for _ARM_, but they're optional and their absence doesn't prevent you to proceed.

Fetch the latest version of opencv sources, and unzip it:

```bash
wget https://github.com/opencv/opencv/archive/3.4.1.zip
unzip 3.4.1.zip
```

Prepare and compile:

```bash
cd opencv-3.4.1
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
```

Go for a walk; this takes ages.

When you're back, complete the installation:

```bash
sudo make install
sudo ldconfig
```

To check if the library is available as a dependency:

```bash
pkg-config --list-all | grep opencv
```

## gtk
Why? Because GTK is a widely used library to make GUIs, and is cross platform. This project uses it for having a user
interface that works in Raspberry, but also in Windows and Mac, so you can test the application from your computer.

```bash
sudo apt-get install libgtkmm-3.0-dev
```

To check if the library is available as a dependency:

```bash
pkg-config --list-all | grep gtkmm
```

# Install the project

## Compile


Go to the root folder:
cd raspberry-pi-fpv-visor

Create the build folder:
mkdir build
cd build
cmake ../src
make

Launch the application:
app/fpv

## Run

## Install as Autorun

## Avoid idle screen
