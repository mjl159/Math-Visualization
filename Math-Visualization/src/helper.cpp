#include "../headers/helper.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::string Helper::readFile(const char* path) {
	std::string contents;
	std::ifstream file;

	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		file.open(path);
		std::stringstream stream;
		// read file's buffer contents into streams
		stream << file.rdbuf();
		// close file handlers
		file.close();
		// convert stream into string
		contents = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cout << "ERROR: " << strerror(errno) << std::endl;
	}

	return contents;
}
