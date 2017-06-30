#ifndef INCLUDE_PASSWORD
#define INCLUDE_PASSWORD

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include "Index_man.h"

using namespace std;

long long get_user_input();
short last_password_check(const string, string);
void create_progress_file(string &, const char *);
string write_password_list(const string &, long long &, const char *, short *, short);

#endif