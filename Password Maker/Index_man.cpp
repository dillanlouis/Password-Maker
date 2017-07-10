#include "Index_man.h"


index_man::index_man()
{
}


index_man::index_man(short max_index_value, short min_size, short max_size) : max_index(max_index_value - 1), min_index_list(min_size), max_index_list(max_size)
{
	index_list.resize(min_size, 0);
}

index_man::~index_man()
{
	index_list.~vector();
}

void index_man::go_to_index(vector<short> & last_index_value)
{
	index_list = last_index_value;
}

void index_man::operator++()
{
	for (short a = short(index_list.size() - 1); a > -1; --a) {
		if (index_list[a] < max_index) {
			++index_list[a];
			return;
		}
		else {
			index_list[a] = 0;
		}
	}
	

	if (min_index_list < max_index_list) {
		++min_index_list;
		index_list.push_back(0);
	}
	else {
		finished = true;
	}
}


short index_man::operator[](short index_val)
{
	return index_list[index_val];
}

short index_man::size()
{
	return (short)index_list.size();
}

bool index_man::finish()
{
	return finished;
}

