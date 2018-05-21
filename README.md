# raspberry-pi-fpv-visor
A simple FPV visor that captures the raspberry's camera input and displays it in full screen, with some OSD data.

Directory structure:
- lib: All complex functionality resides here. All implementation have unit testing
	- src: classes.
	- include: headers, to be included from application
	- test: tests.
- app: The standalone executable, and classes depending directly on hardware.

# Prepare hardware

I assume that you have a newly installed _Raspberry PI_. This is what you need to do:
- Activate the camera
- Activate I2C bus
- Enable V4L2

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
```

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
- Install git
- Install cmake

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
As I am not a Robinson on my island, I depend on the work of others:
- Install pkg-config
- Install opencv
- Install gtk (needs to be Gtk3)

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
sudo apt-get install cmake git libgtk-3-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev # required
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
make -j4
```

Go for a walk; this takes ages. If process breaks, you can launch again just retyping:

```
make -j3
```

When compilation is done, complete the installation:

```bash
sudo make install
sudo ldconfig
```

To check if the library is available as a dependency:

```bash
pkg-config --list-all | grep opencv
```

You can now delete the sources folder; you don't need it any more:

```bash
cd ..
cd ..
rm -rf opencv-3.4.1
rm 3.4.1.zip
```

## gtk for c++
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

You've got all pre-conditions and dependencies, now its time to:
- Compile and test.
- Execute it.
- Autorun.
- Avoid console blanking.
- Avoid screen blanking.

## Compile and test

```bash
git clone https://github.com/jean-michel-gonet/raspberry-pi-fpv-visor.git
cd raspberry-pi-fpv-visor
mkdir build
cd build
cmake ../src/
make
```

To execute the tests (assuming you're still in the ``build`` folder):

```bash
./lib/fpv-lib-test
```

The more traditional ``make test`` works also, but it doesn't show as much information.

## Execute
You need to be in X environment, as the application is graphical.

To launch application, (assuming you're still in the ``build`` folder):


```bash
./app/fpv
```

Application starts full-screen:
- [f] To toggle full-screen
- [Ctrl] + [C] to exit
- [s] To toggle video saving. Video is called ``live.avi`` and saved in your current user folder. 

## Autorun
Easiest way I found to auto-run a GUI application in Raspberry is to create a desktop file in the autostart directory.

```bash
mkdir ~/.config/autostart
vim ~/.config/autostart/fpv.desktop
```

The content of ``fpv.desktop`` should be similar to:

```config
[Desktop Entry]
Name=raspberry-pi-fpv-visor
Exec=/home/pi/raspberry-pi-fpv-visor/build/app/fpv
Path=/home/pi
Type=application
```

The ``Path`` key is where the application will save videos.
- See more about syntax here: https://specifications.freedesktop.org/desktop-entry-spec/latest/ar01s06.html
- See original explanation here: https://www.raspberrypi.org/forums/viewtopic.php?t=18968

## Avoid console blanking
Console blanking affects you if you're using ssh to execute commands. If, for some time, you don't type anything
in the console, it will close.

To avoid it, edit file ``/boot/cmdline.txt`` and append the paramter ``consoleblank=0``


See original explanation here: https://www.raspberrypi.org/documentation/configuration/screensaver.md

## Avoid idle screen
A FPV application will typically have no user interaction, so screen may go idle leaving you in the dark. To prevent this, 
simplest approach is to install a screen saver and then configure it to NOT run:

```bash
sudo apt-get install xscreensaver
```

After this, screensaver application is in _Preferences_, in desktop menu. 
Use the appropriate options to prevent screen saver.

## Enabling composite video out

If you're using a FPV transmitter, you probably want to

```bash
sudo vim /boot/config.txt
```

And then add:
```config
...
sdtv_mode=2
...
hdmi_force_hotplug=0
...
```

When hdmi_force_hotplug is set to 1, system assumes that there is a HDMI device present, so
it never activates video composite output.

When hdmi_force_hotplug is set to 0, system will use composite video unless it detects HDMI device. So,
Raspberry will still use the HDMI monitor if it is connected at boot sequence.

See more about this:
- Original article: https://bhavyanshu.me/tutorials/force-raspberry-pi-output-to-composite-video-instead-of-hdmi/03/03/2014
- Official doc: https://www.raspberrypi.org/documentation/configuration/config-txt/video.md
- More official: https://www.raspberrypi.org/documentation/configuration/config-txt/README.md

# Troubleshooting
I hope you don't need this section.

## Gtk-ERROR **: GTK+ 2.x symbols detected. 
If you get this error message:

```
Gtk-ERROR **: GTK+ 2.x symbols detected. Using GTK+ 2.x and GTK+ 3 in the same process is not supported
```

You may accidentally linked opencv with Gtk2. As this project uses Gtk3, there is a conflict.

You need to be sure that opencv is linked with:

- Uninstall Gtk2
```bash
sudo apt-get remove libgtk2.0-dev
sudo apt-get install libgtk-3-dev
sudo apt-get auto-remove
sudo apt-get install libgtkmm-3.0-dev
```
- Remove the build directory of opencv (yes, you need to rebuild, sorry).
- Start again, BUT...
- Before launching ``make``, check the ``cmake`` log, and verify the Gtk version is linked with. Look for 
something like this:

```
...
--   GUI: 
--     GTK+:                        YES (ver 3.22.11)
--       GThread :                  YES (ver 2.50.3)
--       GtkGlExt:                  NO
--     VTK support:                 NO
...
```

## Debug
Sometimes you need to debug using Raspberry environment. In that case you need to compile with debug symbols, 
and then you use ``gdb`` to run application:

```bash
cd raspberry-pi-fpv-visor
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ../src/
make -j4
gdb ./app/fpv
```

See more about using it: http://apoorvaj.io/hitchhikers-guide-to-the-gdb.html
