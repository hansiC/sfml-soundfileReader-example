#include "SoundFileReaderMp3.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <fstream>

std::string getResourcePath(const std::string& executableDir, const std::string& resourceRelativeName) {
	// windows users may have to change "/" for "\"
	std::size_t pos = executableDir.find_last_of("/");
	std::string prefix = executableDir.substr (0, pos+1);
	return prefix + resourceRelativeName;
}

void togglePlayPause(sf::Music& music) {
	sf::SoundSource::Status musicStatus = music.getStatus();
	if(musicStatus == sf::SoundSource::Status::Paused) {
		music.play();
		std::cout << "music play" << std::endl;
	} else if(musicStatus == sf::SoundSource::Status::Playing) {
		music.pause();
		std::cout << "music pause" << std::endl;
	}
}

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cout << argv[0] << ": missing argument <absolute filename>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string filename(argv[1]);

	std::cout << "START: " << filename << std::endl;
	// Register our custom sf::SoundFileReader for mp3 files.
	// This is the preferred way of adding support for a new audio format.
	// Other formats will be handled by their respective readers.
	sf::SoundFileFactory::registerReader<audio::SoundFileReaderMp3>();

	// Load a music to play
	sf::Music music;
	if (!music.openFromFile(filename)) {
		std::cout << "check your file path. also only wav, flac, ogg and mp3 are supported." << std::endl;
		return EXIT_FAILURE;
	}

	// Now we are sure we can play the file
	// Set up the main window

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2u dimensions;

	// See if we can find the image
	std::string textureName = getResourcePath(std::string(argv[0]), "MP3_file_structure.png");
	std::ifstream ifile(textureName);
	if (ifile) {
		texture.loadFromFile(textureName);
		sprite.setTexture(texture);
		dimensions = texture.getSize();
	} else {
		std::cout << "Resource not found" << std::endl;
		dimensions.x = 800;
		dimensions.y = 600;
	}

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(dimensions.x, dimensions.y), "SFML window");

	// Start the music
	music.play();

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if(event.type == sf::Event::KeyPressed) {
				// the user interface: SPACE pauses and plays, ESC quits
				switch (event.key.code) {
					case sf::Keyboard::Space:
						togglePlayPause(music);
						break;
					case sf::Keyboard::Escape:
						window.close();
						break;
					default:
						break;
				}
			}
		}
		// Clear screen
		window.clear();
		// Draw the sprite
		window.draw(sprite);
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}

