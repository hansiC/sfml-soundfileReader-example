CC=g++
CFLAGS=-std=c++11 -g -O0

# IMPORTANT
# replace <TODO> with your installation directories
#
SFML=TODO
MPG123=<TODO>

INCLUDESFML=$(SFML)/include
INCLUDEMPG123=$(MPG123)/include

LIBSFML=$(SFML)/lib
LIBMPG123=$(MPG123)/lib

INCLUDES := -I$(INCLUDEMPG123) -I$(INCLUDESFML)
# for non-debug builds
LIBS     := -L$(LIBMPG123) -lmpg123 -L$(LIBSFML) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# for debug builds
#LIBS     := -L$(LIBMPG123) -lmpg123 -L$(LIBSFML) -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d

AUDIOEXE := audioexe

all: $(AUDIOEXE)

$(AUDIOEXE): Main.o
	$(CC) $(CFLAGS) $< -o $@ SoundFileReaderMp3.o $(LIBS)

Main.o: Main.cpp SoundFileReaderMp3.o
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

SoundFileReaderMp3.o: SoundFileReaderMp3.cpp SoundFileReaderMp3.hpp
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@
 
clean:
	rm $(AUDIOEXE) *.o
