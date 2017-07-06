#ifndef INCLUDE_PASSWORD_D
#define INCLUDE_PASSWORD_D

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include "Index_man.h"

using namespace std;

short last_password_check(const string, string);
void create_progress_file(string &, const char *);
string write_password_list(const string &, long long &, const char *, short *, short, short);
void start_passowrd_list(const string, const char *, const char *, long long);
#endif