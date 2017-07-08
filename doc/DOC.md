# Compilation

To compile QuantiC you need:

0. [The source code](https://github.com/Daimanu06/QuantiC)
0. [Qt](https://www.qt.io/developers/) version 5.1 or greater
0. a C++ compiler supporting C++11

# Installation

Coming soon

# First use

When you first use the program you may have to indicate the location of the data.
Open the Application menu, then go in setup.
Click the "data" tab, click on browse button on the data location line.
You might find the content in the data folder in the source folder.

# Issues

You may have some following issues:

## No data found / Order file is missing

Check the data folder's structure, it must contain a "icons" folder with png files, and a "quantities" folder with xml files and an "order" text file.


## No localized texts

Make sure you have the *your langage code*.qm in the executable folder.  
The application is curently availaible in english and french.  
Missing languages will come in the future.

# Notes

QuantiC creates a preferences file in the user's folder. e.g.:  
``C:\\*user folder*\\AppData\\Roaming\\Daimanu\\Quanitc.ini`` on Microsoft Windows  
``~/.config/Daimanu/QuantiC.ini`` on GNU/Linux
