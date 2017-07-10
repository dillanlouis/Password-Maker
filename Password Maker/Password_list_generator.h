#pragma once

#define WIFI_COMBO "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.$"
#define PROGRESS_FILE "progress.dat"

#include <fstream>
#include <string>
#include <vector>
#include "Index_man.h"

using namespace std;


struct current_state
{
	string combo{ "" };
	short min{ 0 };
	short max{ 0 };
};

struct last_state
{
	bool exist{ false };
	string last_password{};
	short min{};
	vector<short> position{};

};

void get_last_password(current_state &, last_state &);
void create_progress_file(string &);
void write_password_list(const string &, long long &, const char *, index_man &);
void start_passowrd_list(const char *, long long, current_state &, vector<short> *);