#include "Types/None.hpp"

using namespace cli;

None_type
::None_type()
: Argument_type("")
{

}

None_type
::~None_type()
{

}

None_type* None_type
::clone() const
{
	return new None_type(*this);
}

void None_type
::check(const std::string& val) const
{

}

cli::None_type* cli::None()
{
	return new None_type();
}