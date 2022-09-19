# RoccoLang_v2

Custom Programming Language with the idea of it being easy to use for my third year PRBX module.

This repository does not include a lot of third pary libraries used to make this interface with the physical m3pi robot I used for organisation reasons. 

## Intention
This was designed so that an m3pi robot with an mbed NXP LPC1768 would be able to be used by people who aren't very familiar with programming.

Currently, the uploading of a program to this robot is done using the online mbed compiler to convert written C++ code into a binary which is then uploaded to the robot via its USB interface. 

The code used in this program is designed with the C++03 specification in mind as it is what's supported by the online compiler which was used to create the binary that runs on the robot. 

My intention for this was to have it so instead a program could be read from a USB flash drive inserted into the robot as a simple text file. The language used by the file would be easy enough for someone with only simple programming knowledge to use and be read by the robot and converted into the necessary C++ instructions to be interpreted by the robot. This would allow for easy programming by an inexperienced third party without having to navigate more complex C++ programming. 

## Current Issues:
While the robot was able to understand simple instructions, the import of the designed native library required for it to be adequately functional required more RAM than the board natively supplied with this current implementation. 

This was supplemented in my project with the creation of a basic simulator which would display basic simulated outputs of programs using a simulated robot text interface as a proof of concept.

