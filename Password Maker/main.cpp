#include "Password Maker.h"







int main() {
	const string wifi_pass_combo{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	long long pass_count{};
	unsigned long long length{};
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
		length = last_password.size();
		char * last_combo = new char[length];

		for (unsigned short a = 0; a < length; ++a) {
			last_combo[a] = last_password[a];
		}

		last_password.clear();

		switch (length) {
		case 8:
			last_password = eight_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 9:
			last_password = nine_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 10:
			last_password = ten_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 11:
			last_password = eleven_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 12:
			last_password = twelve_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 13:
			last_password = thirteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 14:
			last_password = fourteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 15:
			last_password = fifteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 16:
			last_password = sixteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 17:
			last_password = seventeen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 18:
			last_password = eightteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 19:
			last_password = nineteen_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 20:
			last_password = twenty_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 21:
			last_password = twentyone_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 22:
			last_password = twentytwo_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 23:
			last_password = twentythree_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 24:
			last_password = twentyfour_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 25:
			last_password = twentyfive_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 26:
			last_password = twentysix_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 27:
			last_password = twentyseven_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 28:
			last_password = twentyeight_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 29:
			last_password = twentynine_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		case 30:
			last_password = thirty_combo(wifi_pass_combo, pass_count, password_file_name, last_combo);
			break;
		default:
			last_password = eight_combo(wifi_pass_combo, pass_count, password_file_name, nullptr);
			break;
		}

		delete[] last_combo;
	}
	else {
		progress.close();
		last_password = eight_combo(wifi_pass_combo, pass_count, password_file_name, nullptr);
	}
	create_progress_file(last_password, progress_file_name);
	system("pause");
	return 0;
}