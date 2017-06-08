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

//This function saves the last konown password
void create_progress_file(string & last_password2){
	fstream progress2;
	progress2.open("progress.dat", ios::out);
	progress2 << last_password2;
	progress2.close();
}

//This function starts the first set of 8 length passwords
short eight_combo(const string & combo8, long long & count8, const char * password_file_name8, char * last_combo8){
	fstream password_list8;
	string last_password8{};
	bool first_round8{ false };
	if (last_combo8 == nullptr) first_round8 = true;
	password_list8.open(password_file_name8, ios::out);
	for (const char a0 : combo8) {
		if (first_round8 || a0 == last_combo8[0]) {
			for (const char a1 : combo8) {
				if (first_round8 || a1 == last_combo8[1]) {
					for (const char a2 : combo8) {
						if (first_round8 || a2 == last_combo8[2]) {
							for (const char a3 : combo8) {
								if (first_round8 || a3 == last_combo8[3]) {
									for (const char a4 : combo8) {
										if (first_round8 || a4 == last_combo8[4]) {
											for (const char a5 : combo8) {
												if (first_round8 || a5 == last_combo8[5]) {
													for (const char a6 : combo8) {
														if (first_round8 || a6 == last_combo8[6]) {
															for (const char a7 : combo8) {
																if (first_round8 || a7 == last_combo8[7]) {
																	first_round8 = 1;
																	password_list8 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << '\n';
																	--count8;
																	if (count8 == 0) {
																		password_list8.close();
																		last_password8 = last_password8 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7;
																		create_progress_file(last_password8);
																		return 0;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	password_list8.close();
	nine_combo(combo8, count8, password_file_name8, nullptr);
	return 0;
}

short nine_combo(const string & combo9, long long & count9, const char * password_file_name9, char * last_combo9){
	if(last_combo9 == nullptr){
		fstream password_list9;
		password_list9.open(password_file_name9, ios::app);
		for(const char a: combo9){
			for(const char b: combo9){
				for(const char c: combo9){
					for(const char d: combo9){
						for(const char e: combo9){
							for(const char f: combo9){
								for(const char g: combo9){
									for(const char h: combo9){
										for(const char i: combo9){
											password_list9 << a << b << c << d << e << f << g << h << i << '\n';
											--count9;
											if(count9 == 0){
												password_list9.close();
												string last_password9{};
												last_password9 = last_password9 + a + b + c + d + e + f + g + h + i;
												create_progress_file(last_password9);
												return 0;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list9.close();
		ten_combo(combo9, count9, password_file_name9, nullptr);
	}else{
		for(short a = 0; a < 9; ++a){
			cout << last_combo9[a] << '\n';
		}
	}
	return 0;
}

short ten_combo(const string & combo10, long long & count10, const char * password_file_name10, char * last_combo10){
	if(last_combo10 == nullptr){
		fstream password_list10;
		password_list10.open(password_file_name10, ios::app);
		for(const char a: combo10){
			for(const char b: combo10){
				for(const char c: combo10){
					for(const char d: combo10){
						for(const char e: combo10){
							for(const char f: combo10){
								for(const char g: combo10){
									for(const char h: combo10){
										for(const char i: combo10){
											for(const char j: combo10){
												--count10;
												password_list10 << a << b << c << d << e << f << g << h << i << j << '\n';
												if(count10 == 0){
													password_list10.close();
													string last_password10;
													last_password10 = last_password10 + a + b + c + d + e + f + g + h + i + j;
													create_progress_file(last_password10);
													return 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list10.close();
		eleven_combo(combo10, count10, password_file_name10, nullptr);
		
	}else{
		for(short a = 0; a < 10; ++a){
			cout << last_combo10[a] << '\n';
		}
	}
	return 0;
}

short eleven_combo(const string & combo11, long long & count11, const char * password_file_name11, char * last_combo11){
	if(last_combo11 == nullptr){
		fstream password_list11;
		password_list11.open(password_file_name11, ios::app);
		for(const char a: combo11){
			for(const char b: combo11){
				for(const char c: combo11){
					for(const char d: combo11){
						for(const char e: combo11){
							for(const char f: combo11){
								for(const char g: combo11){
									for(const char h: combo11){
										for(const char i: combo11){
											for(const char j: combo11){
												for(const char k: combo11){
													password_list11 << a << b << c << d << e << f << g << h << i << j << k << '\n';
													--count11;
													if(count11 == 0){
														password_list11.close();
														string last_password11{};
														last_password11 = last_password11 + a + b + c + d + e + f + g + h + i + j + k;
														create_progress_file(last_password11);
														return 0;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list11.close();
		twelve_combo(combo11, count11, password_file_name11, nullptr);
	}else{
		for(short a = 0; a < 11; ++a){
			cout << last_combo11[a] << '\n';
		}
	}
	return 0;
}

short twelve_combo(const string & combo12, long long & count12, const char * password_file_name12, char * last_combo12){
	if(last_combo12 == nullptr){
		fstream password_list12;
		password_list12.open(password_file_name12, ios::app);
		for(const char a: combo12){
			for(const char b: combo12){
				for(const char c: combo12){
					for(const char d: combo12){
						for(const char e: combo12){
							for(const char f: combo12){
								for(const char g: combo12){
									for(const char h: combo12){
										for(const char i: combo12){
											for(const char j: combo12){
												for(const char k: combo12){
													for(const char l: combo12){
														--count12;
														password_list12 << a << b << c << d << e << f << g << h << i << j << k << l << '\n';
														if(count12 == 0){
															password_list12.close();
															string last_password12{};
															last_password12 = last_password12 + a + b + c + d + e + f + g + h + i + j + k + l;
															create_progress_file(last_password12);
															return 0;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list12.close();
		thirteen_combo(combo12, count12, password_file_name12, nullptr);
	}else{
		for(short a = 0; a < 12; ++a){
			cout << last_combo12[a] << '\n';
		}
	}
	return 0;
}

short thirteen_combo(const string & combo13, long long & count13, const char * password_file_name13, char * last_combo13){
	if(last_combo13 == nullptr){
		fstream password_list13;
		password_list13.open(password_file_name13, ios::app);
		for(const char a: combo13){
			for(const char b: combo13){
				for(const char c: combo13){
					for(const char d: combo13){
						for(const char e: combo13){
							for(const char f: combo13){
								for(const char g: combo13){
									for(const char h: combo13){
										for(const char i: combo13){
											for(const char j: combo13){
												for(const char k: combo13){
													for(const char l: combo13){
														for(const char m: combo13){
															password_list13 << a << b << c << d << e << f << g << h << i << j << k << l << m << '\n';
															--count13;
															if(count13 == 0){
																password_list13.close();
																string last_password13{};
																last_password13 = last_password13 + a + b + c + d + e + f + g + h + i + j + k + l + m;
																create_progress_file(last_password13);
																return 0;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list13.close();
		fourteen_combo(combo13, count13, password_file_name13, nullptr);
	}else{
		for(short a = 0; a < 13; ++a){
			cout << last_combo13[a] << '\n';
		}
	}
	return 0;
}

short fourteen_combo(const string & combo14, long long & count14, const char * password_file_name14, char * last_combo14){
	if(last_combo14 == nullptr){
		fstream password_list14;
		password_list14.open(password_file_name14, ios::app);
		for(const char a: combo14){
			for(const char b: combo14){
				for(const char c: combo14){
					for(const char d: combo14){
						for(const char e: combo14){
							for(const char f: combo14){
								for(const char g: combo14){
									for(const char h: combo14){
										for(const char i: combo14){
											for(const char j: combo14){
												for(const char k: combo14){
													for(const char l: combo14){
														for(const char m: combo14){
															for(const char n: combo14){
																password_list14 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << '\n';
																--count14;
																if(count14 == 0){
																	password_list14.close();
																	string last_password14{};
																	last_password14 = last_password14 + a + b + c + d + e + f + g + h + i + j + k + l + m + n;
																	create_progress_file(last_password14);
																	return 0;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list14.close();
		fifteen_combo(combo14, count14, password_file_name14, nullptr);
	}else{
		for(short a = 0; a < 14; ++a){
			cout << last_combo14[a] << '\n';
		}
	}
	return 0;
}

short fifteen_combo(const string & combo15, long long & count15, const char * password_file_name15, char * last_combo15){
	if(last_combo15 == nullptr){
		fstream password_list15;
		password_list15.open(password_file_name15, ios::app);
		for(const char a: combo15){
			for(const char b: combo15){
				for(const char c: combo15){
					for(const char d: combo15){
						for(const char e: combo15){
							for(const char f: combo15){
								for(const char g: combo15){
									for(const char h: combo15){
										for(const char i: combo15){
											for(const char j: combo15){
												for(const char k: combo15){
													for(const char l: combo15){
														for(const char m: combo15){
															for(const char n: combo15){
																for(const char o: combo15){
																	password_list15 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << '\n';
																	--count15;
																	if(count15 == 0){
																		password_list15.close();
																		string last_password15{};
																		last_password15 = last_password15 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o;
																		create_progress_file(last_password15);
																		return 0;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list15.close();
		sixteen_combo(combo15, count15, password_file_name15, nullptr);
	}else{
		for(short a = 0; a < 15; ++a){
			cout << last_combo15[a] << '\n';
		}
	}
	return 0;
}

short sixteen_combo(const string & combo16, long long & count16, const char * password_file_name16, char * last_combo16){
	if(last_combo16 == nullptr){
		fstream password_list16;
		password_list16.open(password_file_name16, ios::app);
		for(const char a: combo16){
			for(const char b: combo16){
				for(const char c: combo16){
					for(const char d: combo16){
						for(const char e: combo16){
							for(const char f: combo16){
								for(const char g: combo16){
									for(const char h: combo16){
										for(const char i: combo16){
											for(const char j: combo16){
												for(const char k: combo16){
													for(const char l: combo16){
														for(const char m: combo16){
															for(const char n: combo16){
																for(const char o: combo16){
																	for(const char p: combo16){
																		password_list16 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << '\n';
																		--count16;
																		if(count16 == 0){
																			password_list16.close();
																			string last_password16{};
																			last_password16 = last_password16 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p;
																			create_progress_file(last_password16);
																			return 0;
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list16.close();
		seventeen_combo(combo16, count16, password_file_name16, nullptr);
	}else{
		for(short a = 0; a < 16; ++a){
			cout << last_combo16[a] << '\n';
		}
	}
	return 0;
}

short seventeen_combo(const string & combo17, long long & count17, const char * password_file_name17, char * last_combo17){
	if(last_combo17 == nullptr){
		fstream password_list17;
		password_list17.open(password_file_name17, ios::app);
		for(const char a: combo17){
			for(const char b: combo17){
				for(const char c: combo17){
					for(const char d: combo17){
						for(const char e: combo17){
							for(const char f: combo17){
								for(const char g: combo17){
									for(const char h: combo17){
										for(const char i: combo17){
											for(const char j: combo17){
												for(const char k: combo17){
													for(const char l: combo17){
														for(const char m: combo17){
															for(const char n: combo17){
																for(const char o: combo17){
																	for(const char p: combo17){
																		for(const char q: combo17){
																			password_list17 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << '\n';
																			--count17;
																			if(count17 == 0){
																				password_list17.close();
																				string last_password17{};
																				last_password17 = last_password17 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q;
																				create_progress_file(last_password17);
																				return 0;
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list17.close();
		eightteen_combo(combo17, count17, password_file_name17, nullptr);
	}else{
		for(short a = 0; a < 17; ++a){
			cout << last_combo17[a] << '\n';
		}
	}
	return 0;
}

short eightteen_combo(const string & combo18, long long & count18, const char * password_file_name18, char * last_combo18){
	if(last_combo18 == nullptr){
		fstream password_list18;
		password_list18.open(password_file_name18, ios::app);
		for(const char a: combo18){
			for(const char b: combo18){
				for(const char c: combo18){
					for(const char d: combo18){
						for(const char e: combo18){
							for(const char f: combo18){
								for(const char g: combo18){
									for(const char h: combo18){
										for(const char i: combo18){
											for(const char j: combo18){
												for(const char k: combo18){
													for(const char l: combo18){
														for(const char m: combo18){
															for(const char n: combo18){
																for(const char o: combo18){
																	for(const char p: combo18){
																		for(const char q: combo18){
																			for(const char r: combo18){
																				password_list18 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << '\n';
																				--count18;
																				if(count18 == 0){
																					password_list18.close();
																					string last_password18{};
																					last_password18 = last_password18 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r;
																					create_progress_file(last_password18);
																					return 0;
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list18.close();
		nineteen_combo(combo18, count18, password_file_name18, nullptr);
	}else{
		for(short a = 0; a < 18; ++a){
			cout << last_combo18[a] << '\n';
		}
	}
	return 0;
}

short nineteen_combo(const string & combo19, long long & count19, const char * password_file_name19, char * last_combo19){
	if(last_combo19 == nullptr){
		fstream password_list19;
		password_list19.open(password_file_name19, ios::app);
		for(const char a: combo19){
			for(const char b: combo19){
				for(const char c: combo19){
					for(const char d: combo19){
						for(const char e: combo19){
							for(const char f: combo19){
								for(const char g: combo19){
									for(const char h: combo19){
										for(const char i: combo19){
											for(const char j: combo19){
												for(const char k: combo19){
													for(const char l: combo19){
														for(const char m: combo19){
															for(const char n: combo19){
																for(const char o: combo19){
																	for(const char p: combo19){
																		for(const char q: combo19){
																			for(const char r: combo19){
																				for(const char s: combo19){
																					password_list19 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << '\n';
																					--count19;
																					if(count19 == 0){
																						password_list19.close();
																						string last_password19{};
																						last_password19 = last_password19 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s;
																						create_progress_file(last_password19);
																						return 0;
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list19.close();
		twenty_combo(combo19, count19, password_file_name19, nullptr);
	}else{
		for(short a = 0; a < 19; ++a){
			cout << last_combo19[a] << '\n';
		}
	}
	return 0;
}

short twenty_combo(const string & combo20, long long & count20, const char * password_file_name20, char * last_combo20){
	if(last_combo20 == nullptr){
		fstream password_list20;
		password_list20.open(password_file_name20, ios::app);
		for(const char a: combo20){
			for(const char b: combo20){
				for(const char c: combo20){
					for(const char d: combo20){
						for(const char e: combo20){
							for(const char f: combo20){
								for(const char g: combo20){
									for(const char h: combo20){
										for(const char i: combo20){
											for(const char j: combo20){
												for(const char k: combo20){
													for(const char l: combo20){
														for(const char m: combo20){
															for(const char n: combo20){
																for(const char o: combo20){
																	for(const char p: combo20){
																		for(const char q: combo20){
																			for(const char r: combo20){
																				for(const char s: combo20){
																					for(const char t: combo20){
																						password_list20 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << '\n';
																						--count20;
																						if(count20 == 0){
																							password_list20.close();
																							string last_password20{};
																							last_password20 = last_password20 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t;
																							create_progress_file(last_password20);
																							return 0;
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list20.close();
		twentyone_combo(combo20, count20, password_file_name20, nullptr);
	}else{
		for(short int a = 0; a < 20; ++a){
			cout << last_combo20[a] << '\n';
		}
	}
	return 0;
}

short twentyone_combo(const string & combo21, long long & count21, const char * password_file_name21, char * last_combo21){
	if(last_combo21 == nullptr){
		fstream password_list21;
		password_list21.open(password_file_name21, ios::app);
		for(const char a: combo21){
			for(const char b: combo21){
				for(const char c: combo21){
					for(const char d: combo21){
						for(const char e: combo21){
							for(const char f: combo21){
								for(const char g: combo21){
									for(const char h: combo21){
										for(const char i: combo21){
											for(const char j: combo21){
												for(const char k: combo21){
													for(const char l: combo21){
														for(const char m: combo21){
															for(const char n: combo21){
																for(const char o: combo21){
																	for(const char p: combo21){
																		for(const char q: combo21){
																			for(const char r: combo21){
																				for(const char s: combo21){
																					for(const char t: combo21){
																						for(const char u: combo21){
																							password_list21 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << u << '\n';
																							--count21;
																							if(count21 == 0){
																								password_list21.close();
																								string last_password21{};
																								last_password21 = last_password21 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u;
																								create_progress_file(last_password21);
																								return 0;
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list21.close();
		twentytwo_combo(combo21, count21, password_file_name21, nullptr);
	}else{
		for(short a = 0; a < 21; ++a){
			cout << last_combo21[a] << '\n';
		}
	}
	return 0;
}

short twentytwo_combo(const string & combo22, long long & count22, const char * password_file_name22, char * last_combo22){
	if(last_combo22 == nullptr){
		fstream password_list22;
		password_list22.open(password_file_name22, ios::app);
		for(const char a: combo22){
			for(const char b: combo22){
				for(const char c: combo22){
					for(const char d: combo22){
						for(const char e: combo22){
							for(const char f: combo22){
								for(const char g: combo22){
									for(const char h: combo22){
										for(const char i: combo22){
											for(const char j: combo22){
												for(const char k: combo22){
													for(const char l: combo22){
														for(const char m: combo22){
															for(const char n: combo22){
																for(const char o: combo22){
																	for(const char p: combo22){
																		for(const char q: combo22){
																			for(const char r: combo22){
																				for(const char s: combo22){
																					for(const char t: combo22){
																						for(const char u: combo22){
																							for(const char v: combo22){
																								password_list22 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << u << v << '\n';
																								--count22;
																								if(count22 == 0){
																									password_list22.close();
																									string last_password22{};
																									last_password22 = last_password22 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v;
																									create_progress_file(last_password22);
																									return 0;
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list22.close();
		twentythree_combo(combo22, count22, password_file_name22, nullptr);
	}else{
		for(short a = 0; a < 22; ++a){
			cout << last_combo22[a] << '\n';
		}
	}
	return 0;
}

short twentythree_combo(const string & combo23, long long & count23, const char * password_file_name23, char * last_combo23) {
	if (last_combo23 == nullptr) {
		fstream password_list23;
		password_list23.open(password_file_name23, ios::app);
		for (const char a : combo23) {
			for (const char b : combo23) {
				for (const char c : combo23) {
					for (const char d : combo23) {
						for (const char e : combo23) {
							for (const char f : combo23) {
								for (const char g : combo23) {
									for (const char h : combo23) {
										for (const char i : combo23) {
											for (const char j : combo23) {
												for (const char k : combo23) {
													for (const char l : combo23) {
														for (const char m : combo23) {
															for (const char n : combo23) {
																for (const char o : combo23) {
																	for (const char p : combo23) {
																		for (const char q : combo23) {
																			for (const char r : combo23) {
																				for (const char s : combo23) {
																					for (const char t : combo23) {
																						for (const char u : combo23) {
																							for (const char v : combo23) {
																								for (const char w : combo23) {
																									password_list23 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << u << v << w << '\n';
																									--count23;
																									if (count23 == 0) {
																										password_list23.close();
																										string last_password23;
																										last_password23 = last_password23 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w;
																										create_progress_file(last_password23);
																										return 0;
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list23.close();
		twentyfour_combo(combo23, count23, password_file_name23, nullptr);
	}
	else {
		for (short a = 0; a < 23; ++a) {
			cout << last_combo23[a] << '\n';
		}
	}
	
return 0;
}

short twentyfour_combo(const string & combo24, long long & count24, const char * password_file_name24, char * last_combo24) {
	if (last_combo24 == nullptr) {
		fstream password_list24;
		password_list24.open(password_file_name24, ios::app);
		for (const char a : combo24) {
			for (const char b : combo24) {
				for (const char c : combo24) {
					for (const char d : combo24) {
						for (const char e : combo24) {
							for (const char f : combo24) {
								for (const char g : combo24) {
									for (const char h : combo24) {
										for (const char i : combo24) {
											for (const char j : combo24) {
												for (const char k : combo24) {
													for (const char l : combo24) {
														for (const char m : combo24) {
															for (const char n : combo24) {
																for (const char o : combo24) {
																	for (const char p : combo24) {
																		for (const char q : combo24) {
																			for (const char r : combo24) {
																				for (const char s : combo24) {
																					for (const char t : combo24) {
																						for (const char u : combo24) {
																							for (const char v : combo24) {
																								for (const char w : combo24) {
																									for (const char x : combo24) {
																										password_list24 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << u << v << w << x << '\n';
																										--count24;
																										if (count24 == 0) {
																											password_list24.close();
																											string last_password24{};
																											last_password24 = last_password24 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x;
																											create_progress_file(last_password24);
																											return 0;
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list24.close();
		twentyfive_combo(combo24, count24, password_file_name24, last_combo24);
	}
	else {
		for (short a = 0; a < 24; ++a) {
			cout << last_combo24[a] << '\n';
		}
	}
	return 0;
}

short twentyfive_combo(const string & combo25, long long & count25, const char * password_file_name25, char * last_combo25){
	if (last_combo25 == nullptr) {
		fstream password_list25;
		password_list25.open(password_file_name25, ios::app);
		for (const char a : combo25) {
			for (const char b : combo25) {
				for (const char c : combo25) {
					for (const char d : combo25) {
						for (const char e : combo25) {
							for (const char f : combo25) {
								for (const char g : combo25) {
									for (const char h : combo25) {
										for (const char i : combo25) {
											for (const char j : combo25) {
												for (const char k : combo25) {
													for (const char l : combo25) {
														for (const char m : combo25) {
															for (const char n : combo25) {
																for (const char o : combo25) {
																	for (const char p : combo25) {
																		for (const char q : combo25) {
																			for (const char r : combo25) {
																				for (const char s : combo25) {
																					for (const char t : combo25) {
																						for (const char u : combo25) {
																							for (const char v : combo25) {
																								for (const char w : combo25) {
																									for (const char x : combo25) {
																										for (const char y : combo25) {
																											password_list25 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << u << v << w << x << y << '\n';
																											--count25;
																											if (count25 == 0) {
																												password_list25.close();
																												string last_password25{};
																												last_password25 = last_password25 + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x + y;
																												create_progress_file(last_password25);
																												return 0;
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list25.close();
		twentysix_combo(combo25, count25, password_file_name25, nullptr);
	}
	else {
		for (short a = 0; a < 25; ++a) {
			cout << last_combo25[a] << endl;
		}
	}
	return 0;
}

short twentysix_combo(const string & combo26, long long & count26, const char * password_file_name26, char * last_combo26){
	if (last_combo26 == nullptr) {
		fstream password_list26;
		password_list26.open(password_file_name26, ios::app);
		for (const char a : combo26) {
			for (const char b : combo26) {
				for (const char c : combo26) {
					for (const char d : combo26) {
						for (const char e : combo26) {
							for (const char f : combo26) {
								for (const char g : combo26) {
									for (const char h : combo26) {
										for (const char i : combo26) {
											for (const char j : combo26) {
												for (const char k : combo26) {
													for (const char l : combo26) {
														for (const char m : combo26) {
															for (const char n : combo26) {
																for (const char o : combo26) {
																	for (const char p : combo26) {
																		for (const char q : combo26) {
																			for (const char r : combo26) {
																				for (const char s : combo26) {
																					for (const char t : combo26) {
																						for (const char u : combo26) {
																							for (const char v : combo26) {
																								for (const char w : combo26) {
																									for (const char x : combo26) {
																										for (const char y : combo26) {
																											for (const char z : combo26) {
																												password_list26 << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s << t << u << v << w << x << y << z << '\n';
																												--count26;
																												if (count26 == 0) {
																													password_list26.close();
																													string last_password{};
																													last_password = last_password + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x + y + z;
																													create_progress_file(last_password);
																													return 0;
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		password_list26.close();
		cout << "number of passwords remaining: " << count26 << endl;
	}
	else {
		for (short a = 0; a < 26; ++a) {
			cout << last_combo26[a] << '\n';
		}
	}
	return 0;
}

short twentyseven_combo(const string & combo27, long long & count27, const char * password_file_name, char * last_combo27){
	return 0;
}

short twentyeight_combo(const string & combo28, long long & count28, const char * password_file_name28, char * last_combo28){
	return 0;
}

short twentynine_combo(const string & combo29, long long & count29, const char * password_file_name29, char * last_combo29){
	return 0;
}

short thirty_combo(const string & combo30, long long & count30, const char * password_file_name30, char * last_combo30){
	return 0;
}

int main(){
	const string wifi_pass_combo{"01"};
	long long pass_count{};
	unsigned long long length{};
	fstream progress;
	string last_password{};
	const char * password_file_name = "password.txt";

	pass_count = get_user_input();
	
	if(pass_count == 0) return 0;
	
	progress.open("progress.dat", ios::in);
	
	if(progress.is_open()){
		progress >> last_password;
		progress.close();
		length = last_password.size();
		if(length < 8 || length > 64) eight_combo(wifi_pass_combo, pass_count, password_file_name, nullptr);
		char * last_combo = new char[length];

		for(unsigned short a = 0; a < length; ++a){
			last_combo[a] = last_password[a];
		}

		last_password.clear();

		switch(length){
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
	}else{
		progress.close();
		eight_combo(wifi_pass_combo, pass_count, password_file_name, nullptr);
	}

	system("pause");
	return 0;
}