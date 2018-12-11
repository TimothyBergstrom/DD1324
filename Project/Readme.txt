_________________________
HOW TO INSTALL:

The programs require that gcc is installed, which can be installed by using this command in the terminal window:
"sudo apt install gcc"

In the terminal, go to the folder and write in:
"make"
This will trigger the makefile, which will in turn creates a folder called "pgm_images" and compile the programs "zipper" and "viewer".
To clean installed files, please write:
"make clean"
which in turn will remove the compiled softwares "zipper" and "viewer". Note that the directory "pgm_images" will remain, so you 
don't lose the images.


_________________________
HOW TO USE:

To visualize pgm files, they first have to be zipped by the "zipper" program. First, put in a pgm file in the directory "pgm_images"

ZIPPER APPLICATION
Go to the program directory and write:
"./zipper <name_of_pgm_file>"
Whereas <name_of_pgm_file> is the name of the pgm image you put in + the extension .pgm
Example:
"./zipper test.pgm"
This will compile the pgm image and create a file called <name_of_pgm_file.zip> in the pgm_images directory.
The program will also output the compression rate of the image.

VIEWER APPLICATION
Go to the program directory and write:
"./viewer <name_of_zipped_pgm_file> <SCALE_FACTOR>"
Whereas <name_of_zipped_pgm_file> is the name of the zipped pgm image which was created by the zipper program (including extension .zip)
while <SCALE_FACTOR> is an integer telling the program how much to scale the image.
This will output an ascii image of the pgm file and also create a file called "output.txt" with the output.

_________________________
ADDITIONAL INFORMATION:

The "zipper" compresses pgm files inside the "pgm_images" folder using the compression algorithm RLE.

PGM files are grey scaled images which are made in this format:

P2
# information about author
WIDTH HEIGHT
MaxValue-in-array
N1 N2 N3 ... N(width)
.
.
.
.			 N(width*height)


The zipped PGM files will be in this format:

WIDTH
HEIGHT
TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES
len(N1) N1 len(N2) N2 .... len(N(TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES)) N(TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES)


_________________________
QUESTIONS:

# What is the compression rate you obtained when compressing the four images we provided you?

ORIGINAL
saturn.ascii.pgm: 1.45
pepper.ascii.pgm: 0.92
mountain.ascii.pgm: 0.86
mona_lisa.ascii.pgm: 1.07
baboon.ascii.pgm: 0.86

So, pretty bad compressions in most images

OWN IMAGES
perfect_compression.ascii.pgm: 7300.33 (only matrix of 1s)
worst_compression.ascii.pgm: 0.50 (alternating between 1 and 0)


# What are possible ways to further increase the compression rate of the zipper application? 

You could do a lossy compression, aka you store a scaled down version of the images (using the algorithm in the viewer)
and then upscale the image when decoding. However, that would leave artifacts if too low compression was made.

You could also try to merge values which are close together (ex saturn.ascii.pgm has a large background where the values
are only very slightly changing). Depending on the image, you could get a better compression rate.

Another possibility would be to use Lempel–Ziv (LZ77 sliding-window compression algorithm with fixed Huffman coding) instead of RLE,
which is used by windows when making zipped folders.