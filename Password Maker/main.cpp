#include "Password Maker.h"







int main() {
	const string wifi_pass_combo{ "01" };
	long long pass_count{};
	short length{};
	fstream progress;
	string last_password{};
	const char * password_file_name = "password.txt";
	const char * progress_file_name = "progress.dat";

	pass_count = get_user_input();

	if (pass_count == 0) return 0;

	progress.open(progress_file_name, ios::in);

	if (progress.is_open()) {
		progress >> last_password;
		progress.close();
		length = (short)last_password.size();

		if (last_password.size() > 64 || last_password.size() < 8) {
			last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, nullptr, 8);
			goto target;
		}

		if (last_password_check(wifi_pass_combo, last_password) < length) {
			last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, nullptr, 8);
			goto target;
		}

		short * last_index = new short[length];

		for (short a = 0; a < length; ++a) {
			last_index[a] = (short)wifi_pass_combo.find(last_password[a]);
		}

		last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, last_index, length);
	}
	else {
		progress.close();
		last_password = write_password_list(wifi_pass_combo, pass_count, password_file_name, nullptr, 8);
	}
target:if (last_password == " ") {
	remove(progress_file_name);
}
	   else {
	create_progress_file(last_password, progress_file_name);
}
	char a{};
	cout << "Enter a value to end program: ";
	cin >> a;
	return 0;
}