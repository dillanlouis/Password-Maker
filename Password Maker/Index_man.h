#pragma once

using namespace std;
#include <vector>

class index_man
{
public:
	
	index_man(short, short, short);
	~index_man();
	void go_to_index(vector<short> &);
	void operator++();
	short operator[](short);
	short size();
	bool finish();
private:
	index_man();
	vector<short> index_list;
	short max_index{ 0 };
	short min_index_list{ 0 };
	short max_index_list{ 0 };
	bool finished{ false };
};

