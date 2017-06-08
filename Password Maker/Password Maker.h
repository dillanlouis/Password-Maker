#ifndef INCLUDE_PASSWORD
#define INCLUDE_PASSWORD

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

bool valid_number(string &);
bool whole_number(string &);
long long get_user_input();
void create_progress_file(string &);
short eight_combo(const string &, long long &, const char *, char *);
short nine_combo(const string &, long long &, const char *, char *);
short ten_combo(const string &, long long &, const char *, char *);
short eleven_combo(const string &, long long &, const char *, char *);
short twelve_combo(const string &, long long &, const char *, char *);
short thirteen_combo(const string &, long long &, const char *, char *);
short fourteen_combo(const string &, long long &, const char *, char *);
short fifteen_combo(const string &, long long &, const char *, char *);
short sixteen_combo(const string &, long long &, const char *, char *);
short seventeen_combo(const string &, long long &, const char *, char *);
short eightteen_combo(const string &, long long &, const char *, char *);
short nineteen_combo(const string &, long long &, const char *, char *);
short twenty_combo(const string &, long long &, const char *, char *);
short twentyone_combo(const string &, long long &, const char *, char *);
short twentytwo_combo(const string &, long long &, const char *, char *);
short twentythree_combo(const string &, long long &, const char *, char *);
short twentyfour_combo(const string &, long long &, const char *, char *);
short twentyfive_combo(const string &, long long &, const char *, char *);
short twentysix_combo(const string &, long long &, const char *, char *);

#endif