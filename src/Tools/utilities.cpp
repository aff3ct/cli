#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "Tools/utilities.hpp"

std::vector<std::string> cli::split(const std::string &s)
{
	std::string buf;                 // have a buffer string
	std::stringstream ss(s);         // insert the string into a stream
	std::vector<std::string> tokens; // create vector to hold our words

	while (ss >> buf)
		tokens.push_back(buf);

	return tokens;
}

void cli::getline(std::istream &file, std::string &line)
{
	if (file.eof() || file.fail() || file.bad())
		throw std::runtime_error("Something went wrong when getting a new line.");

	while (std::getline(file, line))
		if (line[0] != '#' && !std::all_of(line.begin(),line.end(),isspace))
			break;
}