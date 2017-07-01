#include "Index_man.h"


index_man::index_man()
{
}

index_man::index_man(short size, short max) : max_index(max)
{
	for (short a = 0; a < size; ++a) {
		vector_array.push_back(0);
	}
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
	if (!is_empty()) vector_array.clear();

	max_index = max;
	finished = false;

	for (short a = 0; a < size; ++a) {
		vector_array.push_back(0);
	}
}

void index_man::set_index_value(short size, short * posit, short max)
{
	max_index = max;
	finished = false;

	if (!is_empty()) vector_array.clear();

	for (short a = 0; a < size; ++a) {
		vector_array.push_back(posit[a]);
	}
}

short index_man::operator[](short index_val)
{
	if (index_val < 0 || index_val > (vector_array.size() - 1) || is_empty()) {
		return -1;
	}
	else {
		return vector_array[index_val];
	}
	
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
	short current_index_value = (short)vector_array.size();

	if(new_index_value == 0){
		return;
	}
	else if (new_index_value == current_index_value) {
		return;
	}
	else if (new_index_value < 0) {
		return;
	}
	else if (current_index_value < new_index_value) {
		for (short a = 0; a < (new_index_value - current_index_value); ++a) {
			vector_array.push_back(0);
		}
	}
	else if (current_index_value > new_index_value) {
		for (short a = 0; (current_index_value - new_index_value); ++a) {
			vector_array.pop_back();
		}
	}

	reset();

}

bool index_man::is_empty()
{
	if (vector_array.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}
