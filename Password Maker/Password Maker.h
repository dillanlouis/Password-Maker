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
void create_progress_file(string &, const char *);
string eight_combo(const string &, long long &, const char *, char *);
string nine_combo(const string &, long long &, const char *, char *);
string ten_combo(const string &, long long &, const char *, char *);
string eleven_combo(const string &, long long &, const char *, char *);
string twelve_combo(const string &, long long &, const char *, char *);
string thirteen_combo(const string &, long long &, const char *, char *);
string fourteen_combo(const string &, long long &, const char *, char *);
string fifteen_combo(const string &, long long &, const char *, char *);
string sixteen_combo(const string &, long long &, const char *, char *);
string seventeen_combo(const string &, long long &, const char *, char *);
string eightteen_combo(const string &, long long &, const char *, char *);
string nineteen_combo(const string &, long long &, const char *, char *);
string twenty_combo(const string &, long long &, const char *, char *);
string twentyone_combo(const string &, long long &, const char *, char *);
string twentytwo_combo(const string &, long long &, const char *, char *);
string twentythree_combo(const string &, long long &, const char *, char *);
string twentyfour_combo(const string &, long long &, const char *, char *);
string twentyfive_combo(const string &, long long &, const char *, char *);
string twentysix_combo(const string &, long long &, const char *, char *);
string twentyseven_combo(const string &, long long &, const char *, char *);
string twentyeight_combo(const string &, long long &, const char *, char *);
string twentynine_combo(const string &, long long &, const char *, char *);
string thirty_combo(const string &, long long &, const char *, char *);

#endif