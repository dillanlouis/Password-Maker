#include "Password Maker.h"


/*This program creates a wordlist file for cracking passwords.
It makes the list at a fixed number that the user wants every time being ran replacing the orginal continueing from where it has left off.
*/


//This function checks if the user enters a valid number
bool valid_number(string & user_input2){
	
		for(char a: user_input2){
			if(a == '-' || a == '.' || a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9'){
				if(a == '-'){
					if(user_input2.size() == 1){
						cout << "Invalid number!\a\n" << endl;
						cout << "Enter a valid number: ";
						return false;
					}else{
						if(count(begin(user_input2), end(user_input2), '-') > 1){
							cout << "Invalid number!\a\n" << endl;
							cout << "Enter a valid number: ";
							return false;
						}else if(user_input2[0] != '-'){
							cout << "Invalid number!\a\n" <<endl;
							cout << "Enter a valid number: ";
							return false;
						}else{
							if(user_input2[1] == '.'){
								cout << "Invalid number!\a\n" << endl;
								cout << "Enter a valid number: ";
								return false;
							}
						}
					}
				}else if(a == '.'){
					if(user_input2.size() == 1){
						cout << "Invalid number!\a\n" << endl;
						cout << "Enter a valid number: ";
						return false;
					}else if(user_input2[0] == '.'){
						cerr << "Invalid number!\a\n" << endl;
						cout << "Enter a valid number: ";
						return false;
					}else{
						if(count(begin(user_input2), end(user_input2), '.') > 1){
							cout << "Invalid number!\a\n" << endl;
							cout << "Enter a valid number: ";
							return false;
						}
					}
				}
			}else if(a == ' '){
				cerr << "No blank spaces are allowed!\a\n" << endl;
				cout << "Please enter a numeric value: ";
				return false;
			}else{
				cerr << "Not a number!\a\n" << endl;
				cout << "Please enter a numeric value: ";
				return false;
			}
		}
		
		if(user_input2.empty()){
			cerr << "Error input is empty!!\a\n" << endl;
			cout << "Please enter a value: ";
			return false;
		}
	return true;
}

//This function checks if the user input is a whole number above zero and does not exceed the machines limit
bool whole_number(string & user_input2){
		
		if(count(begin(user_input2), end(user_input2), '-') || count(begin(user_input2), end(user_input2), '.')){
			cerr << "Sorry but negative or decimal numbers are not supported!!\a\n" << endl;
			cout << "Enter a whole positive number higher than 0: ";
			return false;
		}
		
		long long pass_count2{};
		long double dec_count{};
		stringstream(user_input2) >> pass_count2;
		stringstream(user_input2) >> dec_count;
		
		if(user_input2.size() > 19 || pass_count2 < dec_count){
			cout << "Sorry but you have passed your machine limit!\a\n" << endl;
			cout << "Please enter a number below 9,223,372,036,854,775,808: ";
			return false;
		}
		if(dec_count == 0){
			cerr << "Zero is not a counting number!\a\n" << endl;
			cout << "Enter a non-zero number :";
			return false;
		}

	return true;
}

//This function get the user input
long long get_user_input(){
	string user_input{};
	long long length{0};
	if(numeric_limits<long long>::max() < (numeric_limits<long double>::max())){
		cout << "This machine limit is: " << numeric_limits<long long>::max() << endl;
	}else{
		cout << "Sorry this machine is not supported\a\n" << endl;
		system("pause");
		return 0;
	}
	
	cout << "Enter the number of passwords you would like to create: ";
	target:getline(cin, user_input);
	
	
	if(user_input == "limit"){
		length = numeric_limits<long long>::max();
	}else if (!valid_number(user_input)) {
		user_input.clear();
		goto target;
	}else if(!whole_number(user_input)){
		user_input.clear();
		goto target;
	}else{
		stringstream(user_input) >> length;
	}
	return length;
}

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

//This function starts the first set of 8 length passwords
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

