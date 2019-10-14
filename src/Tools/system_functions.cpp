#if (defined(__GNUC__) || defined(__clang__) || defined(__llvm__)) && (defined(__linux__) || defined(__linux) || defined(__APPLE__))
#include <cxxabi.h>   // __cxa_demangle
#endif

#if defined(__linux__) || defined(linux) || defined(__linux) || defined(__FreeBSD__)
#include <unistd.h>
#include <string.h>
#include <errno.h>
#elif defined(__APPLE__) || defined(__MACH__)
#include <mach-o/dyld.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

#include <stdexcept>
#include <sstream>
#include <cstdlib>

#include "Tools/system_functions.h"

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

std::string binary_name;

void cli::set_binary_name(const std::string &bin_name)
{
	binary_name = bin_name;
}

const std::string& cli::get_binary_name()
{
	return binary_name;
}