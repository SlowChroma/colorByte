FOR UNIX SYSTEMS

colorByte is a program I wrote to just test out an ideo I had: an 8-bit RGBA representation system, where each 2 bits represent the R, G,
B, and A channels respectively. This would result in 4 possible combination for each channel (00, 01, 10, 11) and 256 total different colors,
from clear black (00000000) to opaque white (11111111).

You need to have the Raylib library installed (sudo pacman -S raylib on arch linux) and make sure its in the environment path variables. To
build the application, just run the Makefile, and execute colorByte.bin
