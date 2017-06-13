#include "Password Maker.h"







int main() {
	const string wifi_pass_combo{ "abcdefghijklmnopqrstuvwxyz" };
	long long pass_count{};
	unsigned long long length{};
	fstream progress;
	string last_password{};
	const char * password_file_name = "password.txt";
	const char * progress_file_name = "progress.dat";

	pass_count = get_user_input();

	if (pass_count == 0) return 0;

	progress.open("progress.dat", ios::in);

	if (progress.is_open()) {
		progress >> last_password;
		progress.close();
		length = last_password.size();
		if (length < 8 || length > 64) eight_combo(wifi_pass_combo, pass_count, password_file_name, nullptr);
		char * last_combo = new char[length];

		for (unsigned short a = 0; a < length; ++a) {
			last_combo[a] = last_password[a];
		}

		last_password.clear();

		switch (length) {
		case 8:
			eight_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 9:
			nine_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 10:
			ten_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 11:
			eleven_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 12:
			twelve_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 13:
			thirteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 14:
			fourteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 15:
			fifteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 16:
			sixteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 17:
			seventeen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 18:
			eightteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 19:
			nineteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 20:
			twenty_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 21:
			twentyone_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 22:
			twentytwo_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 23:
			twentythree_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 24:
			twentyfour_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 25:
			twentyfive_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 26:
			twentysix_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		default:
			break;
		}

		delete[] last_combo;
	}
	else {
		progress.close();
		eight_combo(wifi_pass_combo, pass_count, password_file_name, nullptr);
	}

	system("pause");
	return 0;
}