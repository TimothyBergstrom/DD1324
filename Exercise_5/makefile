# Variables
# Make everything depend on headers, so if headers change, it will recompile everything
SOURCE		= exercise5-3.c init.c shuffle.c
HEADERS 	= init.h shuffle.h
OBJECTS		= $(SOURCE:.c=.o)
TARGET 		= exercise5-4
CC			= gcc
CFLAGS		= -Wall -g

program: exercise5-3.o init.o shuffle.o
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)

# clean all
clean:
	-rm $(TARGET)
	-rm $(OBJECTS)

# Clean only .o files
clean_o:
	-rm $(OBJECTS)

