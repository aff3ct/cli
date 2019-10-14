#include <stdexcept>

#include "Maps/Argument_map_group.hpp"

using namespace cli;

bool Argument_map_group
::exist(const std::string &prefix) const
{
	return (this->find(prefix) != this->end());
}

void Argument_map_group
::add(const std::string& prefix, const std::string& title)
{
	if (prefix.size() == 0)
		throw std::invalid_argument("No prefix has been given ('prefix.size()' == 0).");

	if (title.size() == 0)
		throw std::invalid_argument("No title has been given ('title.size()' == 0).");

	(*this)[prefix] = title;
}
