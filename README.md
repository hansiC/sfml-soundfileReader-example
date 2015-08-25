Before you can run 'make', you have to open the Makefile and insert the paths to your sfml and mpg123 installations where indicated.

Then run make. It will build executable 'audioexe'

If SFML is already on your LD_LIBRARY_PATH, invoke program using:

	./audioexe <filename>

Otherwise invoke using:

	export LD_LIBRARY_PATH=/path-to-sfml-install/lib/ && ./audioexe <filename>

ESCAPE key exits, SPACE pauses and plays.
