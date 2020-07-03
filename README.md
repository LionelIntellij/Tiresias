Project Title:
-------------
This project generates a library to analysis input file and determinate encoding and type of data.
 The library implements machine learning methods based statistics.  



Authors:
--------
Lionel Lacroix 



Getting Started:
----------------
These instructions will get you a copy of the Tiresias project up and running on your local machine for development and testing purposes. See prerequisites and installing for notes on how to deploy the project on a live system.




Documentation:
--------------
The documentation about the library is available .



Prerequisites:
---------------

libs/ and smartDescriptor/: contains the sources of the library.
doxygen/: contains the configuration files to generate the documentation using doxygen.
configure.sh: is a script to compile the library.


What things you need to set in order to run the Node.js server using the library:


Dependencies:
-------------

Shared libraries necessary for the compilation are available here.

In Debian stretch you must install the following libraries:


apt install libarchive
apt install libz
apt install libbz2


Installing:
-----------
Steps to compile and install the library:

* $ ./configure
* $ mkdir build && cd build
* $ make -j4
* $ make install
* $ cd ..

Shared and static libraries are generated in lib/


Last version :
-------------
1.1.0