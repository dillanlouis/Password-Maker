#include "Index_man.h"


index_man::index_man()
{
}

index_man::index_man(short size, short max) : max_index(max)
{
	vector_array.resize(size, 0);
}

index_man::~index_man()
{
	vector_array.~vector();
}

void index_man::operator++()
{
	if (is_empty()) {
		finished = true;
		return;
	}

	short index_child{};
	index_child =(short) vector_array.size() - 1;
	short next_row{-1};

	++vector_array[index_child];

	if (vector_array[index_child] == max_index) {
			--vector_array[index_child];
			for (short a = index_child; a > -1; --a) {
				if (vector_array[a] == (max_index - 1)) {
					continue;
				}
				else {
					next_row = a;
					break;
				}
			}
			if (next_row == -1) {
				finished = true;
				return;
			}
			else {
				while (index_child != next_row) {
					vector_array[index_child] = 0;
					--index_child;
				}
				++vector_array[index_child];
				return;
			}
	}
	else {
		return;
	}

	return;
}

void index_man::set_index_value(short size, short max)
{
	max_index = max;
	finished = false;

	vector_array.resize(size, 0);
	reset();
}

void index_man::set_index_value(short size, short * posit, short max)
{
	max_index = max;
	finished = false;

	vector_array.resize(size, 0);
	reset();
}

short index_man::operator[](short index_val)
{
	return vector_array[index_val];
}

short index_man::size()
{
	return (short)vector_array.size();
}

bool index_man::is_finished()
{
	if (is_empty()) return true;
	return finished;
}

void index_man::reset()
{
	if (is_empty()) return;

	finished = false;

	for (short a = 0; a < vector_array.size(); ++a) {
		vector_array[a] = 0;
	}
}

void index_man::resize(short new_index_value)
{
	vector_array.resize(new_index_value);

	reset();
}

bool index_man::is_empty()
{
	return vector_array.empty();
}
