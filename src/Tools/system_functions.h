#ifndef SYSTEM_FUNCTIONS_H_
#define SYSTEM_FUNCTIONS_H_

#include <string>

namespace cli
{

/*!
 * \brief return the full location/path of the binary
 *
 * \return the binary path if supported, empty string else
 */
std::string get_binary_path();

/*!
 * \brief split a path in basedir and filename
 *
 * \param path is the path (basedir/filename)
 * \param basedir is the directory without the filename
 * \param filename is the name of the file without the base directory
 */
void split_path(const std::string& path, std::string &basedir, std::string &filename);

void set_binary_name(const std::string &bin_name);

const std::string& get_binary_name();

}

#endif // SYSTEM_FUNCTIONS_H_