#AutomodelCar Demo

This project shows the image processing implemented to detect the Lane and Crossing Lines of a road. It is a demo based on the ROS project AutomodelCar: https://github.com/Conilo/automodelcar-cic-ipn.git
The algorithms design was developed by César Gerardo Bravo Conejo.
The original C++ ROS nodes used here were coded by Esteban Iván Rojas Hernandéz and Brenda Camacho García.
  
##Required Libraries:
  -OpenCV
  -Gflags


sudo apt-get install cmake-curses-gui

//gflags clone the original git repo to where you think you need it (/opt for me)
$ git clone https://github.com/gflags/gflags
install it
$ cd gflags
// $ vi INTSALL.md // optional - gives details
$ mkdir build
$ cd build
$ ccmake ..
[ press c then e then g]
$ make
$ sudo make install
