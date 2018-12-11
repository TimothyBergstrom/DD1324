# Variables
CC			= gcc
CFLAGS		= -Wall -g

all: create_folder zipper viewer

create_folder:
	-mkdir -p pgm_images

zipper:
	$(CC) $(CFLAGS) zipper.c -o zipper
	
viewer:
	$(CC) $(CFLAGS) viewer.c -o viewer

# clean all
clean:
	-rm zipper
	-rm viewer
