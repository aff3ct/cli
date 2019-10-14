#include "Ranges/Length.hpp"

cli::Length_range* cli::Length(size_t min_size, size_t max_size)
{
	return new Length_range(min_size, max_size);
}