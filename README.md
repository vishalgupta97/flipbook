FLIPBOOK

Generate an mp4 file using FLIPBOOK grammar and BMP input image file. Support still images, images moving in line and images moving in square. Other designs can be added easily.

INSTALL
------------
1. Install g++, python3.8, ffmpeg, flex, bison
2. Install matplotlib and numpy using pip3

FILES
------------

flipbook.l :- Contains token for lexer (used by flex).
flipbook.y :- Contains grammar for flipbook (used by bison).
tree.h :- Contains C++ classes to handle flipbook grammar.
flipbook.cpp :- Contains main program to generate each frame according to the given specification.
flipbook.sh :- Contains ffmpeg code which converts a sequence of frames to mp4 file.

smiley.bmp, moon.bmp, sun.bmp :- Input image files
test\_file.flip, test\_file1.flip :- Flipbook usage examples.
out.mp4, out1.mp4 :- Contains generated output file

FUTURE
----------------

1. Add support for other image files.
2. Extend the grammar to support different transitions.
