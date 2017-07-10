#include "Password_list_generator.h"




void get_last_password(current_state & current1, last_state & last1) {
	
	fstream progress(PROGRESS_FILE, ios::in);

	if (progress.is_open()) {

		progress >> last1.last_password;

		progress.close();
		if (numeric_limits<short>::max() < last1.last_password.size()) return;
		last1.min = (short)last1.last_password.size();

		if (last1.min > current1.max || last1.min < current1.min) {
			last1.last_password.clear();
			return;
		}

		for (const char a : last1.last_password) {
			if (current1.combo.find(a) == string::npos)
			{
				return;
			}
			else {

			}
		}

		for (short a = 0; a < last1.min; ++a) {
			last1.position.push_back( (short)current1.combo.find(last1.last_password[a]) );
		}

		last1.exist = true;
	}
	else {
		return;
	}
}

//This function saves the last konown password
void create_progress_file(string & last_password){
	fstream progress(PROGRESS_FILE, ios::out);
	progress << last_password;
	progress.close();
}

//This function writes the password list
void write_password_list(const string & combo, long long & count, const char * password_file_name, index_man & man1){
	fstream password_list8(password_file_name, ios::out);

	while (!man1.finish()) {

		for (short a = 0; a < man1.size(); ++a) {
			password_list8 << combo[man1[a]];
		}

		password_list8 << '\n';
		--count;

		if (count == 0) {
			password_list8.close();
			return;
		}
		++man1;
	}
	
	password_list8.close();
	return;
}

//this function starts or resumes the password list writing over the last list
void start_passowrd_list(const char * password_file_name, long long pass_count, current_state & current1, vector<short> * posit)
{
	string last_password{};
	index_man man1((short)current1.combo.size(), current1.min, current1.max);
	if (posit != nullptr) {
		man1.go_to_index(*posit); 
		++man1;
		if (man1.finish()) {
			remove(password_file_name);
		}
		else {
			write_password_list(current1.combo, pass_count, password_file_name, man1);
		}
	}
	else {
		write_password_list(current1.combo, pass_count, password_file_name, man1);
	}

	for (short a = 0; a < man1.size(); ++a) {
		last_password = last_password + current1.combo[man1[a]];
	}

	if (man1.finish()) {
		remove(PROGRESS_FILE);
	}
	else {
		create_progress_file(last_password);
	}
}

