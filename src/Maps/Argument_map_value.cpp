#include "Types/File_system/File_system.hpp"
#include "Types/Number/Integer.hpp"
#include "Maps/Argument_map_value.hpp"

using namespace cli;

bool Argument_map_value
::exist(const Argument_tag &tags) const
{
	return (this->find(tags) != this->end());
}

uint64_t Argument_map_value
::to_uint64(const Argument_tag &tags) const
{
	try
	{
		return cli::Integer_type<uint64_t>::convert_to_int(this->at(tags));
	}
	catch (std::exception&)
	{
		return 0;
	}
}

int Argument_map_value
::to_int(const Argument_tag &tags) const
{
	try
	{
		return std::stoi(this->at(tags));
	}
	catch (std::exception&)
	{
		return 0;
	}
}

float Argument_map_value
::to_float(const Argument_tag &tags) const
{
	try
	{
		return std::stof(this->at(tags));
	}
	catch (std::exception&)
	{
		return 0.0f;
	}
}

std::string Argument_map_value::
to_file(const Argument_tag &tags) const
{
	if (Is_file::check(this->at(tags)))
		return this->at(tags);
	else
	{
		auto new_str = modify_path<Is_file>(this->at(tags));
		if (new_str.empty())
			return this->at(tags);
		else
			return new_str;
	}
}

std::string Argument_map_value::
to_folder(const Argument_tag &tags) const
{
	if (Is_folder::check(this->at(tags)))
		return this->at(tags);
	else
	{
		auto new_str = modify_path<Is_folder>(this->at(tags));
		if (new_str.empty())
			return this->at(tags);
		else
			return new_str;
	}
}

std::string Argument_map_value::
to_path(const Argument_tag &tags) const
{
	if (Is_path::check(this->at(tags)))
		return this->at(tags);
	else
	{
		auto new_str = modify_path<Is_path>(this->at(tags));
		if (new_str.empty())
			return this->at(tags);
		else
			return new_str;
	}
}