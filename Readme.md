# AutomodelCarDemo

This project shows the image processing implemented to detect the Lane and Crossing Lines of a road. It is a demo based on the ROS project AutomodelCar: https://github.com/Conilo/automodelcar-cic-ipn.git

The algorithms design was developed by César Gerardo Bravo Conejo.

The original C++ ROS nodes used here were coded by Esteban Iván Rojas Hernandéz and Brenda Camacho García.
  
## Prerequisites


  -OpenCV
  
  -Gflags
### Gflags installation
```
 git clone https://github.com/gflags/gflags
 cd gflags
 mkdir build
 cd build
 ccmake ..
 ```
 
Press c  then g

```
 make
 
 sudo make install
```
## Installation
Clone the repository
```
git clone https://github.com/Brendacg616/AutonomousCarDemo.git
cd  AutononomousCarDemo
mkdir build
cd build
cmake ..
cmake --build
```
## Usage
``` 
cd build 
```
To display some help in the program usage, type on the terminal:
```
./AutomodelCar -h
```
For program execution:
```
./AutomodelCar -i [path_to_video_file]
```
