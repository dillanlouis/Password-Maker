#include "Password_list_generator.h"


/*This program creates a wordlist for brute-forcing wifi
It makes the list depending on the number of passwords the user wants saving the last password when finished
*/

//This function gets the number of passwords to create
long long get_user_input() {
	char a{};
	string user_input{};
	long long pass_count{ 0 };
	long double dec_count{ 0 };

	if (numeric_limits<long long>::max() < (numeric_limits<long double>::max())) {
		cout << "This machine limit is: " << numeric_limits<long long>::max() << endl;
	}
	else {
		cerr << "Sorry this machine is not supported\a\n" << endl;
		cin >> a;
		return 0;
	}

	cout << "Enter the number of passwords you would like to create: ";
target:getline(cin, user_input);


	if (user_input.empty()) {
		cerr << "Error input is empty!!\a\n" << endl;
		cout << "Please enter a value: ";
		goto target;
	}
	else if (user_input.size() > 19) {
		cerr << "Buffer overflow!\a\n" << endl;
		cout << "Please enter less than 20 characters: ";
		user_input.clear();
		goto target;
	}
	else if (user_input == "limit") {
		pass_count = numeric_limits<long long>::max();
		return pass_count;
	}
	else {
		for (char a : user_input) {
			if (!isdigit(a)) {
				cerr << "Input is not a whole number!\a\n" << endl;
				cout << "Please enter a whole number: ";
				user_input.clear();
				goto target;
			}
		}
		stringstream(user_input) >> pass_count;
		stringstream(user_input) >> dec_count;
		if (pass_count < dec_count) {
			cerr << "Sorry but you have passed your machine limit!\a\n" << endl;
			cout << "Please enter a number below " << numeric_limits<long long>::max() << ": ";
			user_input.clear();
			goto target;
		}
		else if (pass_count == 0) {
			cerr << "Sorry but zero does not count!\a\n" << endl;
			cout << "Enter a whole number: ";
			user_input.clear();
			goto target;

		}
	}
	return pass_count;
}


int main() {
	const string wifi_pass_combo{ "01" };
	const char * password_file_name = "password.txt";
	const char * progress_file_name = "progress.dat";
	long long pass_count{};

	pass_count = get_user_input();

	if (pass_count == 0) return 0;

	start_passowrd_list(wifi_pass_combo, password_file_name, progress_file_name, pass_count);
	
	char a{};
	cout << "Enter a value to end program: ";
	cin >> a;
	return 0;
}