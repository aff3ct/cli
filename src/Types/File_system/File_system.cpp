#include <fstream>
#include <dirent.h>

#include "Types/File_system/File_system.hpp"

std::string cli::openmode_to_string(const openmode& mode)
{
	std::string str;

	switch(mode)
	{
		case openmode::read :
			str += "read only";
			break;

		case openmode::write :
			str += "write only";
			break;

		case openmode::read_write : // nothing to check
			str += "read/write";
			break;
	}

	return str;
}

bool cli::Is_file::check(const std::string& filename)
{
	std::ifstream f(filename);

	DIR *dp = opendir(filename.c_str());

	// if filename is a directory return false
	if (dp != nullptr)
	{
		closedir(dp);
		return false;
	}

	return f.good();
}

bool cli::Is_folder::check(const std::string& foldername)
{
	DIR *dp = opendir(foldername.c_str());

	if (dp != nullptr)
	{
		closedir(dp);
		return true;
	}

	return false;
}

bool cli::Is_path::check(const std::string& path)
{
	return Is_file::check(path) || Is_folder::check(path);
}

bool cli::No_check::check(const std::string&)
{
	return true;
}