# AutomodelCarDemo

This project shows the image processing implemented to detect the Lane and Crossing Lines of a road. It is a demo based on the ROS project AutomodelCar: https://github.com/Conilo/automodelcar-cic-ipn.git

The algorithms design was developed by César Gerardo Bravo Conejo.

The original C++ ROS nodes used here were coded by Esteban Iván Rojas Hernandéz and Brenda Camacho García.

This project is composed for the following files:

  * **AutomodelCarDemo**: Main program, it opens the video file and save each frame in order to pass the data to the ImageProcessing, LaneDetection and CrossingDetection's member functions.
  
  * **ImageProcessing Library**: Contains ImageProcessing class in which the image is transformed from BGR to Gray Scale, then is filtered, cropped  and finally the perspective is transformed  in order to get a bird-eye view of the road.
  
  * **CrossingDetection Library**: Contains CrossingDetection class which perfoms a column based search of the crossing line points.
  
  * **LaneDetection Library**: Contains LaneDetection class which perfoms a row based search of the Lane line points.
  
  * **LocalMaximaDetection Library**: Contains the LocMax_pw() function that searchs the local maxima of a given vector, this function is used to get the line points in both crossing and lane line detection. This detection is reliable even when the light conditions are not favorable.
  
## Prerequisites

This project was built on Ubuntu 14.04, the following packages are required:

  * OpenCV
  * CMake (v2.8 minimum required)
  * Gflags
  
 ### CMake installation
```
sudo apt-get install cmake-curses-gui
 ```
  
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
### OpenCV Installation
Please refer to OpenCV installation guide https://docs.opencv.org/3.4.3/d7/d9f/tutorial_linux_install.html

## Installation
Clone the repository
```
git clone https://github.com/Brendacg616/AutonomousCarDemo.git
cd  AutononomousCarDemo
mkdir build
cd build
cmake ..
make
```
## Usage
To display some help in the program usage, type on the terminal:
```
./AutomodelCar -h
```
For program execution:
```
./AutomodelCar -i [path_to_video_file]
```
### Usage Example
```
./AutomodelCar -i ../videos/output.mp4
```
