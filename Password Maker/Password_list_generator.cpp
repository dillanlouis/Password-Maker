#include "Password_list_generator.h"





//this functions verifies that the last password saved was not tampered with
short last_password_check(const string combo, string last_known)
{
	short count{0};
	for (const char a : last_known) {
		for (const char b : combo) {
			if (a == b) {
				++count;
				break;
			}
		}
	}
	return count;
}

//This function saves the last konown password
void create_progress_file(string & last_password, const char * progress_file_name){
	fstream progress2;
	progress2.open(progress_file_name, ios::out);
	progress2 << last_password;
	progress2.close();
}

//This function writes the password list
string write_password_list(const string & combo, long long & count, const char * password_file_name, short * last_combo, short min_length, short max_length){
	fstream password_list8;
	string last_password8{};
	index_man man1((short)combo.size(), min_length, max_length);

	password_list8.open(password_file_name, ios::out);
	
	if (last_combo != nullptr) {
		man1.go_to_index(last_combo);
		++man1;
	}
		
	while (!man1.finish()) {

		for (short a = 0; a < man1.size(); ++a) {
			password_list8 << combo[man1[a]];
		}

		password_list8 << '\n';
		--count;

		if (count == 0) {
			password_list8.close();
			for (short a = 0; a < man1.size(); ++a) {
				last_password8 = last_password8 + combo[man1[a]];
			}
			return last_password8;
		}
		++man1;
	}
	
	password_list8.close();
	return " ";
}

//this function starts or resumes the password list writing over the last list
void start_passowrd_list(const string wifi_pass_combo, const char * password_file_name, const char * progress_file_name, long long pass_count)
{
	unsigned long long length{};
	fstream progress;
	string last_password{};

	progress.open(progress_file_name, ios::in);

	if (progress.is_open()) {
		progress >> last_password;
		progress.close();
		length = last_password.size();

		if (length > 64 || length < 8) {
			last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, nullptr, 8, 64);
			goto target;
		}

		if (last_password_check(wifi_pass_combo, last_password) < length) {
			last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, nullptr, 8, 64);
			goto target;
		}

		short * last_index = new short[length];

		for (short a = 0; a < length; ++a) {
			last_index[a] = (short)wifi_pass_combo.find(last_password[a]);
		}

		last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, last_index, (short)length, 64);
	}
	else {
		progress.close();
		last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, nullptr, 8, 64);
	}
target:if (last_password == " ") {
	remove(progress_file_name);
}
	   else {
		   create_progress_file(last_password, progress_file_name);
	   }
}

