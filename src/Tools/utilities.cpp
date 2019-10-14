#if defined(__linux__) || defined(linux) || defined(__linux) || defined(__FreeBSD__)
#include <unistd.h>
#include <string.h>
#include <errno.h>
#elif defined(__APPLE__) || defined(__MACH__)
#include <mach-o/dyld.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

#include <cstdlib>
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

std::string cli::get_binary_path()
{
	std::string binary_path;

#if defined(__linux__) || defined(linux) || defined(__linux) || defined(__FreeBSD__)
	constexpr size_t path_size = 8192;
	char path[path_size];
#ifdef __FreeBSD__
	auto len = readlink("/proc/curproc/file", path, path_size);
#else
	auto len = readlink("/proc/self/exe", path, path_size);
#endif
	if (len == -1)
	{
		std::stringstream message;
		message << "'readlink' failed ('errno' = " << strerror(errno) << ").";
		throw std::runtime_error(message.str());
	}
	path[len] = '\0';
	binary_path = path;
#elif defined(__APPLE__) || defined(__MACH__)
	constexpr size_t path_size = 8192;
	char path[path_size];
	uint32_t size = sizeof(path);
	if (_NSGetExecutablePath(path, &size) != 0)
	{
		std::stringstream message;
		message << "'_NSGetExecutablePath' path buffer is too small; need 'size' = " << size << "('path_size' = "
		        << path_size << ").";
		throw std::runtime_error(message.str());
	}
	binary_path = path;
#elif defined(_WIN32) || defined(_WIN64)
	constexpr size_t path_size = 8192;
	char path[path_size];
	DWORD copied = 0;
	copied = GetModuleFileName(NULL, path, path_size);
	if (copied >= path_size)
	{
		std::stringstream message;
		message << "'GetModuleFileName' path buffer is too small ('path_size' = " << path_size << ").";
		throw std::runtime_error(message.str());
	}
	binary_path = path;
#endif

	return binary_path;
}

void cli::split_path(const std::string& path, std::string &basedir, std::string &filename)
{
  size_t found;
  found = path.find_last_of("/\\");
  basedir = path.substr(0,found);
  filename = path.substr(found+1);
}
