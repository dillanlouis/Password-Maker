#ifndef INCLUDE_IO_MAN
#define INCLUDE_IO_MAN

using namespace std;
#include <algorithm>
#include <vector>

class index_man
{
public:
	
	index_man();
	index_man(short, short);
	~index_man();
	short operator++();
	void set_index_value(short, short);
	void set_index_value(short, short *, short);
	short operator[](short);
	short size();
	bool is_finished();
	void reset();
private:
	vector<short> vector_array;
	short max_index{0};
	bool finished{ false };
};



#endif 

