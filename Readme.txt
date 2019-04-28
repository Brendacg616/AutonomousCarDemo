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
