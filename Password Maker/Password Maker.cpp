#include "Password Maker.h"


/*This program creates a wordlist file for cracking passwords.
It makes the list at a fixed number that the user wants every time being ran replacing the orginal continueing from where it has left off.
*/


//This function gets a whole number from user input and enforces it to be a whole number 
long long get_user_input(){
	char a{};
	string user_input{};
	long long pass_count{0};
	long double dec_count{0};

	if(numeric_limits<long long>::max() < (numeric_limits<long double>::max())){
		cout << "This machine limit is: " << numeric_limits<long long>::max() << endl;
	}else{
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
	else if(user_input.size() > 19){
		cerr << "Buffer overflow!\a\n" << endl;
		cout << "Please enter less than 20 characters: ";
		user_input.clear();
		goto target;
	}
	else if(user_input == "limit"){
		pass_count = numeric_limits<long long>::max();
		return pass_count;
	}else{
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
			cout << "Please enter a number below " << numeric_limits<long long>::max()  << ": ";
			user_input.clear();
			goto target;
		}
		else if(pass_count == 0) {
			cerr << "Sorry but zero does not count!\a\n" << endl;
			cout << "Enter a whole number: ";
			user_input.clear();
			goto target;

		}
	}
	return pass_count;
}

//this functions verifies that the last password saved was not tampered with
short last_password_check(const string combo, string last_known)
{
	short count{0};
	for (const char a : last_known) {
		for (const char b : combo) {
			if (a == b) {
				++count;
				continue;
			}
		}
	}
	return count;
}

//This function saves the last konown password
void create_progress_file(string & last_password2, const char * progress_file_name2){
	if (last_password2 == " ") return;
	fstream progress2;
	progress2.open(progress_file_name2, ios::out);
	progress2 << last_password2;
	progress2.close();
}

//This function writes the password list
string write_password_list(const string & combo2, long long & count2, const char * password_file_name2, short * last_combo2, short length2){
	fstream password_list8;
	string last_password8{};
	password_list8.open(password_file_name2, ios::out);
	index_man man1;

	if (last_combo2 != nullptr) {
		man1.set_index_value(length2, last_combo2, (short)combo2.size());
		++man1;
	}
	else {
		man1.set_index_value(length2, (short)combo2.size());
	}
		
	target:while (!man1.is_finished()) {
		if (man1[0] < 0) continue;
		for (short a = 0; a < man1.size(); ++a) {
			password_list8 << combo2[man1[a]];
		}

		password_list8 << '\n';
		--count2;

		if (count2 == 0) {
			password_list8.close();
			for (short a = 0; a < man1.size(); ++a) {
				last_password8 = last_password8 + combo2[man1[a]];
			}
			return last_password8;
		}
		++man1;
	}
		
	if (count2 > 0) {
		man1.reset();
		++length2;
		if (length2 > 64) {
			password_list8.close();
			return " ";
		}
		man1.set_index_value(length2, (short)combo2.size());
		goto target;
	}
	
	
	password_list8.close();
	for (short a = 0; a < man1.size(); ++a) {
		last_password8 = last_password8 + combo2[man1[a]];
	}
	return last_password8;
}

