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
																	if (!first_round8) {
																		first_round8 = true;
																		continue;
																	}
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
	return nine_combo(combo8, count8, password_file_name8, nullptr);
}

short nine_combo(const string & combo9, long long & count9, const char * password_file_name9, char * last_combo9){
	fstream password_list9;
	string last_password9{};
	bool first_round9{ false };
	if (last_combo9 == nullptr) {
		first_round9 = true;
		password_list9.open(password_file_name9, ios::app);
	}
	else {
		password_list9.open(password_file_name9, ios::out);
	}
	for (const char a0 : combo9) {
		if (first_round9 || a0 == last_combo9[0]) {
			for (const char a1 : combo9) {
				if (first_round9 || a1 == last_combo9[1]) {
					for (const char a2 : combo9) {
						if (first_round9 || a2 == last_combo9[2]) {
							for (const char a3 : combo9) {
								if (first_round9 || a3 == last_combo9[3]) {
									for (const char a4 : combo9) {
										if (first_round9 || a4 == last_combo9[4]) {
											for (const char a5 : combo9) {
												if (first_round9 || a5 == last_combo9[5]) {
													for (const char a6 : combo9) {
														if (first_round9 || a6 == last_combo9[6]) {
															for (const char a7 : combo9) {
																if (first_round9 || a7 == last_combo9[7]) {
																	for (const char a8 : combo9) {
																		if (first_round9 || a8 == last_combo9[8]) {
																			if (!first_round9) {
																				first_round9 = true;
																				continue;
																			}
																			password_list9 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << '\n';
																			--count9;
																			if (count9 == 0) {
																				password_list9.close();
																				last_password9 = last_password9 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
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
	return ten_combo(combo9, count9, password_file_name9, nullptr);
}

short ten_combo(const string & combo10, long long & count10, const char * password_file_name10, char * last_combo10){
	fstream password_list10;
	string last_password10;
	bool first_round10{ false };
	if (last_combo10 == nullptr) {
		first_round10 = true;
		password_list10.open(password_file_name10, ios::app);
	}
	else {
		password_list10.open(password_file_name10, ios::out);
	}
	for (const char a0 : combo10) {
		if (first_round10 || a0 == last_combo10[0]) {
			for (const char a1 : combo10) {
				if (first_round10 || a1 == last_combo10[1]) {
					for (const char a2 : combo10) {
						if (first_round10 || a2 == last_combo10[2]) {
							for (const char a3 : combo10) {
								if (first_round10 || a3 == last_combo10[3]) {
									for (const char a4 : combo10) {
										if (first_round10 || a4 == last_combo10[4]) {
											for (const char a5 : combo10) {
												if (first_round10 || a5 == last_combo10[5]) {
													for (const char a6 : combo10) {
														if (first_round10 || a6 == last_combo10[6]) {
															for (const char a7 : combo10) {
																if (first_round10 || a7 == last_combo10[7]) {
																	for (const char a8 : combo10) {
																		if (first_round10 || a8 == last_combo10[8]) {
																			for (const char a9 : combo10) {
																				if (first_round10 || a9 == last_combo10[9]) {
																					if (!first_round10) {
																						first_round10 = true;
																						continue;
																					}
																					password_list10 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << '\n';
																					--count10;
																					if (count10 == 0) {
																						password_list10.close();
																						last_password10 = last_password10 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
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
	return eleven_combo(combo10, count10, password_file_name10, nullptr);
}

short eleven_combo(const string & combo11, long long & count11, const char * password_file_name11, char * last_combo11){
	fstream password_list11;
	string last_password11{};
	bool first_round11{ false };
	if (last_combo11 == nullptr) {
		first_round11 = true;
		password_list11.open(password_file_name11, ios::app);
	}
	else {
		password_list11.open(password_file_name11, ios::out);
	}
	for (const char a0 : combo11) {
		if (first_round11 || a0 == last_combo11[0]) {
			for (const char a1 : combo11) {
				if (first_round11 || a1 == last_combo11[1]) {
					for (const char a2 : combo11) {
						if (first_round11 || a2 == last_combo11[2]) {
							for (const char a3 : combo11) {
								if (first_round11 || a3 == last_combo11[3]) {
									for (const char a4 : combo11) {
										if (first_round11 || a4 == last_combo11[4]) {
											for (const char a5 : combo11) {
												if (first_round11 || a5 == last_combo11[5]) {
													for (const char a6 : combo11) {
														if (first_round11 || a6 == last_combo11[6]) {
															for (const char a7 : combo11) {
																if (first_round11 || a7 == last_combo11[7]) {
																	for (const char a8 : combo11) {
																		if (first_round11 || a8 == last_combo11[8]) {
																			for (const char a9 : combo11) {
																				if (first_round11 || a9 == last_combo11[9]) {
																					for (const char a10 : combo11) {
																						if (first_round11 || a10 == last_combo11[10]) {
																							if (!first_round11) {
																								first_round11 = true;
																								continue;
																							}
																							password_list11 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << '\n';
																							--count11;
																							if (count11 == 0) {
																								password_list11.close();
																								last_password11 = last_password11 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10;
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
	return twelve_combo(combo11, count11, password_file_name11, nullptr);
}

short twelve_combo(const string & combo12, long long & count12, const char * password_file_name12, char * last_combo12){
	fstream password_list12;
	string last_password12{};
	bool first_round12{ false };
	if (last_combo12 == nullptr) {
		first_round12 = true;
		password_list12.open(password_file_name12, ios::app);
	}
	else {
		password_list12.open(password_file_name12, ios::out);
	}
	for (const char a0 : combo12) {
		if (first_round12 || a0 == last_combo12[0]) {
			for (const char a1 : combo12) {
				if (first_round12 || a1 == last_combo12[1]) {
					for (const char a2 : combo12) {
						if (first_round12 || a2 == last_combo12[2]) {
							for (const char a3 : combo12) {
								if (first_round12 || a3 == last_combo12[3]) {
									for (const char a4 : combo12) {
										if (first_round12 || a4 == last_combo12[4]) {
											for (const char a5 : combo12) {
												if (first_round12 || a5 == last_combo12[5]) {
													for (const char a6 : combo12) {
														if (first_round12 || a6 == last_combo12[6]) {
															for (const char a7 : combo12) {
																if (first_round12 || a7 == last_combo12[7]) {
																	for (const char a8 : combo12) {
																		if (first_round12 || a8 == last_combo12[8]) {
																			for (const char a9 : combo12) {
																				if (first_round12 || a9 == last_combo12[9]) {
																					for (const char a10 : combo12) {
																						if (first_round12 || a10 == last_combo12[10]) {
																							for (const char a11 : combo12) {
																								if (first_round12 || a11 == last_combo12[11]) {
																									if (!first_round12) {
																										first_round12 = true;
																										continue;
																									}
																									password_list12 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << '\n';
																									--count12;
																									if (count12 == 0) {
																										password_list12.close();
																										last_password12 = last_password12 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11;
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
	return thirteen_combo(combo12, count12, password_file_name12, nullptr);
}

short thirteen_combo(const string & combo13, long long & count13, const char * password_file_name13, char * last_combo13){
	fstream password_list13;
	string last_password13{};
	bool first_round13{ false };
	if (last_combo13 == nullptr) {
		first_round13 = true;
		password_list13.open(password_file_name13, ios::app);
	}
	else {
		password_list13.open(password_file_name13, ios::out);
	}
	for (const char a0 : combo13) {
		if (first_round13 || a0 == last_combo13[0]) {
			for (const char a1 : combo13) {
				if (first_round13 || a1 == last_combo13[1]) {
					for (const char a2 : combo13) {
						if (first_round13 || a2 == last_combo13[2]) {
							for (const char a3 : combo13) {
								if (first_round13 || a3 == last_combo13[3]) {
									for (const char a4 : combo13) {
										if (first_round13 || a4 == last_combo13[4]) {
											for (const char a5 : combo13) {
												if (first_round13 || a5 == last_combo13[5]) {
													for (const char a6 : combo13) {
														if (first_round13 || a6 == last_combo13[6]) {
															for (const char a7 : combo13) {
																if (first_round13 || a7 == last_combo13[7]) {
																	for (const char a8 : combo13) {
																		if (first_round13 || a8 == last_combo13[8]) {
																			for (const char a9 : combo13) {
																				if (first_round13 || a9 == last_combo13[9]) {
																					for (const char a10 : combo13) {
																						if (first_round13 || a10 == last_combo13[10]) {
																							for (const char a11 : combo13) {
																								if (first_round13 || a11 == last_combo13[11]) {
																									for (const char a12 : combo13) {
																										if (first_round13 || a12 == last_combo13[12]) {
																											if (!first_round13) {
																												first_round13 = true;
																												continue;
																											}
																											password_list13 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << '\n';
																											--count13;
																											if (count13 == 0) {
																												password_list13.close();
																												last_password13 = last_password13 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12;
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
	return fourteen_combo(combo13, count13, password_file_name13, nullptr);
}

short fourteen_combo(const string & combo14, long long & count14, const char * password_file_name14, char * last_combo14){
	fstream password_list14;
	string last_password14{};
	bool first_round14{ false };
	if (last_combo14 == nullptr) {
		first_round14 = true;
		password_list14.open(password_file_name14, ios::app);
	}
	else {
		password_list14.open(password_file_name14, ios::out);
	}
	for (const char a0 : combo14) {
		if (first_round14 || a0 == last_combo14[0]) {
			for (const char a1 : combo14) {
				if (first_round14 || a1 == last_combo14[1]) {
					for (const char a2 : combo14) {
						if (first_round14 || a2 == last_combo14[2]) {
							for (const char a3 : combo14) {
								if (first_round14 || a3 == last_combo14[3]) {
									for (const char a4 : combo14) {
										if (first_round14 || a4 == last_combo14[4]) {
											for (const char a5 : combo14) {
												if (first_round14 || a5 == last_combo14[5]) {
													for (const char a6 : combo14) {
														if (first_round14 || a6 == last_combo14[6]) {
															for (const char a7 : combo14) {
																if (first_round14 || a7 == last_combo14[7]) {
																	for (const char a8 : combo14) {
																		if (first_round14 || a8 == last_combo14[8]) {
																			for (const char a9 : combo14) {
																				if (first_round14 || a9 == last_combo14[9]) {
																					for (const char a10 : combo14) {
																						if (first_round14 || a10 == last_combo14[10]) {
																							for (const char a11 : combo14) {
																								if (first_round14 || a11 == last_combo14[11]) {
																									for (const char a12 : combo14) {
																										if (first_round14 || a12 == last_combo14[12]) {
																											for (const char a13 : combo14) {
																												if (first_round14 || a13 == last_combo14[13]) {
																													if (!first_round14) {
																														first_round14 = true;
																														continue;
																													}
																													password_list14 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << '\n';
																													--count14;
																													if (count14 == 0) {
																														password_list14.close();
																														last_password14 = last_password14 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13;
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
	return fifteen_combo(combo14, count14, password_file_name14, nullptr);
}

short fifteen_combo(const string & combo15, long long & count15, const char * password_file_name15, char * last_combo15){
	fstream password_list15;
	string last_password15{};
	bool first_round15{ false };
	if (last_combo15 == nullptr) {
		first_round15 = true;
		password_list15.open(password_file_name15, ios::app);
	}
	else {
		password_list15.open(password_file_name15, ios::out);
	}
	for (const char a0 : combo15) {
		if (first_round15 || a0 == last_combo15[0]) {
			for (const char a1 : combo15) {
				if (first_round15 || a1 == last_combo15[1]) {
					for (const char a2 : combo15) {
						if (first_round15 || a2 == last_combo15[2]) {
							for (const char a3 : combo15) {
								if (first_round15 || a3 == last_combo15[3]) {
									for (const char a4 : combo15) {
										if (first_round15 || a4 == last_combo15[4]) {
											for (const char a5 : combo15) {
												if (first_round15 || a5 == last_combo15[5]) {
													for (const char a6 : combo15) {
														if (first_round15 || a6 == last_combo15[6]) {
															for (const char a7 : combo15) {
																if (first_round15 || a7 == last_combo15[7]) {
																	for (const char a8 : combo15) {
																		if (first_round15 || a8 == last_combo15[8]) {
																			for (const char a9 : combo15) {
																				if (first_round15 || a9 == last_combo15[9]) {
																					for (const char a10 : combo15) {
																						if (first_round15 || a10 == last_combo15[10]) {
																							for (const char a11 : combo15) {
																								if (first_round15 || a11 == last_combo15[11]) {
																									for (const char a12 : combo15) {
																										if (first_round15 || a12 == last_combo15[12]) {
																											for (const char a13 : combo15) {
																												if (first_round15 || a13 == last_combo15[13]) {
																													for (const char a14 : combo15) {
																														if (first_round15 || a14 == last_combo15[14]) {
																															if (!first_round15) {
																																first_round15 = true;
																																continue;
																															}
																															password_list15 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << '\n';
																															--count15;
																															if (count15 == 0) {
																																password_list15.close();
																																last_password15 = last_password15 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14;
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
	return sixteen_combo(combo15, count15, password_file_name15, nullptr);
}

short sixteen_combo(const string & combo16, long long & count16, const char * password_file_name16, char * last_combo16){
	fstream password_list16;
	string last_password16{};
	bool first_round16{ false };
	if (last_combo16 == nullptr) {
		first_round16 = true;
		password_list16.open(password_file_name16, ios::app);
	}
	else {
		password_list16.open(password_file_name16, ios::out);
	}
	for (const char a0 : combo16) {
		if (first_round16 || a0 == last_combo16[0]) {
			for (const char a1 : combo16) {
				if (first_round16 || a1 == last_combo16[1]) {
					for (const char a2 : combo16) {
						if (first_round16 || a2 == last_combo16[2]) {
							for (const char a3 : combo16) {
								if (first_round16 || a3 == last_combo16[3]) {
									for (const char a4 : combo16) {
										if (first_round16 || a4 == last_combo16[4]) {
											for (const char a5 : combo16) {
												if (first_round16 || a5 == last_combo16[5]) {
													for (const char a6 : combo16) {
														if (first_round16 || a6 == last_combo16[6]) {
															for (const char a7 : combo16) {
																if (first_round16 || a7 == last_combo16[7]) {
																	for (const char a8 : combo16) {
																		if (first_round16 || a8 == last_combo16[8]) {
																			for (const char a9 : combo16) {
																				if (first_round16 || a9 == last_combo16[9]) {
																					for (const char a10 : combo16) {
																						if (first_round16 || a10 == last_combo16[10]) {
																							for (const char a11 : combo16) {
																								if (first_round16 || a11 == last_combo16[11]) {
																									for (const char a12 : combo16) {
																										if (first_round16 || a12 == last_combo16[12]) {
																											for (const char a13 : combo16) {
																												if (first_round16 || a13 == last_combo16[13]) {
																													for (const char a14 : combo16) {
																														if (first_round16 || a14 == last_combo16[14]) {
																															for (const char a15 : combo16) {
																																if (first_round16 || a15 == last_combo16[15]) {
																																	if (!first_round16) {
																																		first_round16 = true;
																																		continue;
																																	}
																																	password_list16 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << '\n';
																																	--count16;
																																	if (count16 == 0) {
																																		password_list16.close();
																																		last_password16 = last_password16 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15;
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
	return seventeen_combo(combo16, count16, password_file_name16, nullptr);
}

short seventeen_combo(const string & combo17, long long & count17, const char * password_file_name17, char * last_combo17){
	fstream password_list17;
	string last_password17{};
	bool first_round17{ false };
	if (last_combo17 == nullptr) {
		first_round17 = true;
		password_list17.open(password_file_name17, ios::app);
	}
	else {
		password_list17.open(password_file_name17, ios::out);
	}
	for (const char a0 : combo17) {
		if (first_round17 || a0 == last_combo17[0]) {
			for (const char a1 : combo17) {
				if (first_round17 || a1 == last_combo17[1]) {
					for (const char a2 : combo17) {
						if (first_round17 || a2 == last_combo17[2]) {
							for (const char a3 : combo17) {
								if (first_round17 || a3 == last_combo17[3]) {
									for (const char a4 : combo17) {
										if (first_round17 || a4 == last_combo17[4]) {
											for (const char a5 : combo17) {
												if (first_round17 || a5 == last_combo17[5]) {
													for (const char a6 : combo17) {
														if (first_round17 || a6 == last_combo17[6]) {
															for (const char a7 : combo17) {
																if (first_round17 || a7 == last_combo17[7]) {
																	for (const char a8 : combo17) {
																		if (first_round17 || a8 == last_combo17[8]) {
																			for (const char a9 : combo17) {
																				if (first_round17 || a9 == last_combo17[9]) {
																					for (const char a10 : combo17) {
																						if (first_round17 || a10 == last_combo17[10]) {
																							for (const char a11 : combo17) {
																								if (first_round17 || a11 == last_combo17[11]) {
																									for (const char a12 : combo17) {
																										if (first_round17 || a12 == last_combo17[12]) {
																											for (const char a13 : combo17) {
																												if (first_round17 || a13 == last_combo17[13]) {
																													for (const char a14 : combo17) {
																														if (first_round17 || a14 == last_combo17[14]) {
																															for (const char a15 : combo17) {
																																if (first_round17 || a15 == last_combo17[15]) {
																																	for (const char a16 : combo17) {
																																		if (first_round17 || a16 == last_combo17[16]) {
																																			if (!first_round17) {
																																				first_round17 = true;
																																				continue;
																																			}
																																			password_list17 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << '\n';
																																			--count17;
																																			if (count17 == 0) {
																																				password_list17.close();
																																				last_password17 = last_password17 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16;
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
	return eightteen_combo(combo17, count17, password_file_name17, nullptr);
}

short eightteen_combo(const string & combo18, long long & count18, const char * password_file_name18, char * last_combo18){
	fstream password_list18;
	string last_password18{};
	bool first_round18{ false };
	if (last_combo18 == nullptr) {
		first_round18 = true;
		password_list18.open(password_file_name18, ios::app);
	}
	else {
		password_list18.open(password_file_name18, ios::out);
	}
	for (const char a0 : combo18) {
		if (first_round18 || a0 == last_combo18[0]) {
			for (const char a1 : combo18) {
				if (first_round18 || a1 == last_combo18[1]) {
					for (const char a2 : combo18) {
						if (first_round18 || a2 == last_combo18[2]) {
							for (const char a3 : combo18) {
								if (first_round18 || a3 == last_combo18[3]) {
									for (const char a4 : combo18) {
										if (first_round18 || a4 == last_combo18[4]) {
											for (const char a5 : combo18) {
												if (first_round18 || a5 == last_combo18[5]) {
													for (const char a6 : combo18) {
														if (first_round18 || a6 == last_combo18[6]) {
															for (const char a7 : combo18) {
																if (first_round18 || a7 == last_combo18[7]) {
																	for (const char a8 : combo18) {
																		if (first_round18 || a8 == last_combo18[8]) {
																			for (const char a9 : combo18) {
																				if (first_round18 || a9 == last_combo18[9]) {
																					for (const char a10 : combo18) {
																						if (first_round18 || a10 == last_combo18[10]) {
																							for (const char a11 : combo18) {
																								if (first_round18 || a11 == last_combo18[11]) {
																									for (const char a12 : combo18) {
																										if (first_round18 || a12 == last_combo18[12]) {
																											for (const char a13 : combo18) {
																												if (first_round18 || a13 == last_combo18[13]) {
																													for (const char a14 : combo18) {
																														if (first_round18 || a14 == last_combo18[14]) {
																															for (const char a15 : combo18) {
																																if (first_round18 || a15 == last_combo18[15]) {
																																	for (const char a16 : combo18) {
																																		if (first_round18 || a16 == last_combo18[16]) {
																																			for (const char a17 : combo18) {
																																				if (first_round18 || a17 == last_combo18[17]) {
																																					if (!first_round18) {
																																						first_round18 = true;
																																						continue;
																																					}
																																					password_list18 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << '\n';
																																					--count18;
																																					if (count18 == 0) {
																																						password_list18.close();
																																						last_password18 = last_password18 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17;
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
	return nineteen_combo(combo18, count18, password_file_name18, nullptr);
}

short nineteen_combo(const string & combo19, long long & count19, const char * password_file_name19, char * last_combo19){
	fstream password_list19;
	string last_password19{};
	bool first_round19{ false };
	if (last_combo19 == nullptr) {
		first_round19 = true;
		password_list19.open(password_file_name19, ios::app);
	}
	else {
		password_list19.open(password_file_name19, ios::out);
	}
	for (const char a0 : combo19) {
		if (first_round19 || a0 == last_combo19[0]) {
			for (const char a1 : combo19) {
				if (first_round19 || a1 == last_combo19[1]) {
					for (const char a2 : combo19) {
						if (first_round19 || a2 == last_combo19[2]) {
							for (const char a3 : combo19) {
								if (first_round19 || a3 == last_combo19[3]) {
									for (const char a4 : combo19) {
										if (first_round19 || a4 == last_combo19[4]) {
											for (const char a5 : combo19) {
												if (first_round19 || a5 == last_combo19[5]) {
													for (const char a6 : combo19) {
														if (first_round19 || a6 == last_combo19[6]) {
															for (const char a7 : combo19) {
																if (first_round19 || a7 == last_combo19[7]) {
																	for (const char a8 : combo19) {
																		if (first_round19 || a8 == last_combo19[8]) {
																			for (const char a9 : combo19) {
																				if (first_round19 || a9 == last_combo19[9]) {
																					for (const char a10 : combo19) {
																						if (first_round19 || a10 == last_combo19[10]) {
																							for (const char a11 : combo19) {
																								if (first_round19 || a11 == last_combo19[11]) {
																									for (const char a12 : combo19) {
																										if (first_round19 || a12 == last_combo19[12]) {
																											for (const char a13 : combo19) {
																												if (first_round19 || a13 == last_combo19[13]) {
																													for (const char a14 : combo19) {
																														if (first_round19 || a14 == last_combo19[14]) {
																															for (const char a15 : combo19) {
																																if (first_round19 || a15 == last_combo19[15]) {
																																	for (const char a16 : combo19) {
																																		if (first_round19 || a16 == last_combo19[16]) {
																																			for (const char a17 : combo19) {
																																				if (first_round19 || a17 == last_combo19[17]) {
																																					for (const char a18 : combo19) {
																																						if (first_round19 || a18 == last_combo19[18]) {
																																							if (!first_round19) {
																																								first_round19 = true;
																																								continue;
																																							}
																																							password_list19 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << '\n';
																																							--count19;
																																							if (count19 == 0) {
																																								password_list19.close();
																																								last_password19 = last_password19 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18;
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
	return twenty_combo(combo19, count19, password_file_name19, nullptr);
}

short twenty_combo(const string & combo20, long long & count20, const char * password_file_name20, char * last_combo20){
	fstream password_list20;
	string last_password20{};
	bool first_round20{ false };
	if (last_combo20 == nullptr) {
		first_round20 = true;
		password_list20.open(password_file_name20, ios::app);
	}
	else {
		password_list20.open(password_file_name20, ios::out);
	}
	for (const char a0 : combo20) {
		if (first_round20 || a0 == last_combo20[0]) {
			for (const char a1 : combo20) {
				if (first_round20 || a1 == last_combo20[1]) {
					for (const char a2 : combo20) {
						if (first_round20 || a2 == last_combo20[2]) {
							for (const char a3 : combo20) {
								if (first_round20 || a3 == last_combo20[3]) {
									for (const char a4 : combo20) {
										if (first_round20 || a4 == last_combo20[4]) {
											for (const char a5 : combo20) {
												if (first_round20 || a5 == last_combo20[5]) {
													for (const char a6 : combo20) {
														if (first_round20 || a6 == last_combo20[6]) {
															for (const char a7 : combo20) {
																if (first_round20 || a7 == last_combo20[7]) {
																	for (const char a8 : combo20) {
																		if (first_round20 || a8 == last_combo20[8]) {
																			for (const char a9 : combo20) {
																				if (first_round20 || a9 == last_combo20[9]) {
																					for (const char a10 : combo20) {
																						if (first_round20 || a10 == last_combo20[10]) {
																							for (const char a11 : combo20) {
																								if (first_round20 || a11 == last_combo20[11]) {
																									for (const char a12 : combo20) {
																										if (first_round20 || a12 == last_combo20[12]) {
																											for (const char a13 : combo20) {
																												if (first_round20 || a13 == last_combo20[13]) {
																													for (const char a14 : combo20) {
																														if (first_round20 || a14 == last_combo20[14]) {
																															for (const char a15 : combo20) {
																																if (first_round20 || a15 == last_combo20[15]) {
																																	for (const char a16 : combo20) {
																																		if (first_round20 || a16 == last_combo20[16]) {
																																			for (const char a17 : combo20) {
																																				if (first_round20 || a17 == last_combo20[17]) {
																																					for (const char a18 : combo20) {
																																						if (first_round20 || a18 == last_combo20[18]) {
																																							for (const char a19 : combo20) {
																																								if (first_round20 || a19 == last_combo20[19]) {
																																									if (!first_round20) {
																																										first_round20 = true;
																																										continue;
																																									}
																																									password_list20 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << '\n';
																																									--count20;
																																									if (count20 == 0) {
																																										password_list20.close();
																																										last_password20 = last_password20 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19;
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
	return twentyone_combo(combo20, count20, password_file_name20, nullptr);
}

short twentyone_combo(const string & combo21, long long & count21, const char * password_file_name21, char * last_combo21){
	fstream password_list21;
	string last_password21{};
	bool first_round21{ false };
	if (last_combo21 == nullptr) {
		first_round21 = true;
		password_list21.open(password_file_name21, ios::app);
	}
	else {
		password_list21.open(password_file_name21, ios::out);
	}
	for (const char a0 : combo21) {
		if (first_round21 || a0 == last_combo21[0]) {
			for (const char a1 : combo21) {
				if (first_round21 || a1 == last_combo21[1]) {
					for (const char a2 : combo21) {
						if (first_round21 || a2 == last_combo21[2]) {
							for (const char a3 : combo21) {
								if (first_round21 || a3 == last_combo21[3]) {
									for (const char a4 : combo21) {
										if (first_round21 || a4 == last_combo21[4]) {
											for (const char a5 : combo21) {
												if (first_round21 || a5 == last_combo21[5]) {
													for (const char a6 : combo21) {
														if (first_round21 || a6 == last_combo21[6]) {
															for (const char a7 : combo21) {
																if (first_round21 || a7 == last_combo21[7]) {
																	for (const char a8 : combo21) {
																		if (first_round21 || a8 == last_combo21[8]) {
																			for (const char a9 : combo21) {
																				if (first_round21 || a9 == last_combo21[9]) {
																					for (const char a10 : combo21) {
																						if (first_round21 || a10 == last_combo21[10]) {
																							for (const char a11 : combo21) {
																								if (first_round21 || a11 == last_combo21[11]) {
																									for (const char a12 : combo21) {
																										if (first_round21 || a12 == last_combo21[12]) {
																											for (const char a13 : combo21) {
																												if (first_round21 || a13 == last_combo21[13]) {
																													for (const char a14 : combo21) {
																														if (first_round21 || a14 == last_combo21[14]) {
																															for (const char a15 : combo21) {
																																if (first_round21 || a15 == last_combo21[15]) {
																																	for (const char a16 : combo21) {
																																		if (first_round21 || a16 == last_combo21[16]) {
																																			for (const char a17 : combo21) {
																																				if (first_round21 || a17 == last_combo21[17]) {
																																					for (const char a18 : combo21) {
																																						if (first_round21 || a18 == last_combo21[18]) {
																																							for (const char a19 : combo21) {
																																								if (first_round21 || a19 == last_combo21[19]) {
																																									for (const char a20 : combo21) {
																																										if (first_round21 || a20 == last_combo21[20]) {
																																											if (!first_round21) {
																																												first_round21 = true;
																																												continue;
																																											}
																																											password_list21 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << a20 << '\n';
																																											--count21;
																																											if (count21 == 0) {
																																												password_list21.close();
																																												last_password21 = last_password21 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20;
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
	return twentytwo_combo(combo21, count21, password_file_name21, nullptr);
}

short twentytwo_combo(const string & combo22, long long & count22, const char * password_file_name22, char * last_combo22){
	fstream password_list22;
	string last_password22{};
	bool first_round22{ false };
	if (last_combo22 == nullptr) {
		first_round22 = true;
		password_list22.open(password_file_name22, ios::app);
	}
	else {
		password_list22.open(password_file_name22, ios::out);
	}
	for (const char a0 : combo22) {
		if (first_round22 || a0 == last_combo22[0]) {
			for (const char a1 : combo22) {
				if (first_round22 || a1 == last_combo22[1]) {
					for (const char a2 : combo22) {
						if (first_round22 || a2 == last_combo22[2]) {
							for (const char a3 : combo22) {
								if (first_round22 || a3 == last_combo22[3]) {
									for (const char a4 : combo22) {
										if (first_round22 || a4 == last_combo22[4]) {
											for (const char a5 : combo22) {
												if (first_round22 || a5 == last_combo22[5]) {
													for (const char a6 : combo22) {
														if (first_round22 || a6 == last_combo22[6]) {
															for (const char a7 : combo22) {
																if (first_round22 || a7 == last_combo22[7]) {
																	for (const char a8 : combo22) {
																		if (first_round22 || a8 == last_combo22[8]) {
																			for (const char a9 : combo22) {
																				if (first_round22 || a9 == last_combo22[9]) {
																					for (const char a10 : combo22) {
																						if (first_round22 || a10 == last_combo22[10]) {
																							for (const char a11 : combo22) {
																								if (first_round22 || a11 == last_combo22[11]) {
																									for (const char a12 : combo22) {
																										if (first_round22 || a12 == last_combo22[12]) {
																											for (const char a13 : combo22) {
																												if (first_round22 || a13 == last_combo22[13]) {
																													for (const char a14 : combo22) {
																														if (first_round22 || a14 == last_combo22[14]) {
																															for (const char a15 : combo22) {
																																if (first_round22 || a15 == last_combo22[15]) {
																																	for (const char a16 : combo22) {
																																		if (first_round22 || a16 == last_combo22[16]) {
																																			for (const char a17 : combo22) {
																																				if (first_round22 || a17 == last_combo22[17]) {
																																					for (const char a18 : combo22) {
																																						if (first_round22 || a18 == last_combo22[18]) {
																																							for (const char a19 : combo22) {
																																								if (first_round22 || a19 == last_combo22[19]) {
																																									for (const char a20 : combo22) {
																																										if (first_round22 || a20 == last_combo22[20]) {
																																											for (const char a21 : combo22) {
																																												if (first_round22 || a21 == last_combo22[21]){
																																													if (!first_round22) {
																																														first_round22 = true;
																																														continue;
																																													}
																																													password_list22 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << a20 << a21 << '\n';
																																													--count22;
																																													if (count22 == 0) {
																																														password_list22.close();
																																														last_password22 = last_password22 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21;
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
	return twentythree_combo(combo22, count22, password_file_name22, nullptr);
}

short twentythree_combo(const string & combo23, long long & count23, const char * password_file_name23, char * last_combo23) {
	fstream password_list23;
	string last_password23{};
	bool first_round23{ false };
	if (last_combo23 == nullptr) {
		first_round23 = true;
		password_list23.open(password_file_name23, ios::app);
	}
	else {
		password_list23.open(password_file_name23, ios::out);
	}
	for (const char a0 : combo23) {
		if (first_round23 || a0 == last_combo23[0]) {
			for (const char a1 : combo23) {
				if (first_round23 || a1 == last_combo23[1]) {
					for (const char a2 : combo23) {
						if (first_round23 || a2 == last_combo23[2]) {
							for (const char a3 : combo23) {
								if (first_round23 || a3 == last_combo23[3]) {
									for (const char a4 : combo23) {
										if (first_round23 || a4 == last_combo23[4]) {
											for (const char a5 : combo23) {
												if (first_round23 || a5 == last_combo23[5]) {
													for (const char a6 : combo23) {
														if (first_round23 || a6 == last_combo23[6]) {
															for (const char a7 : combo23) {
																if (first_round23 || a7 == last_combo23[7]) {
																	for (const char a8 : combo23) {
																		if (first_round23 || a8 == last_combo23[8]) {
																			for (const char a9 : combo23) {
																				if (first_round23 || a9 == last_combo23[9]) {
																					for (const char a10 : combo23) {
																						if (first_round23 || a10 == last_combo23[10]) {
																							for (const char a11 : combo23) {
																								if (first_round23 || a11 == last_combo23[11]) {
																									for (const char a12 : combo23) {
																										if (first_round23 || a12 == last_combo23[12]) {
																											for (const char a13 : combo23) {
																												if (first_round23 || a13 == last_combo23[13]) {
																													for (const char a14 : combo23) {
																														if (first_round23 || a14 == last_combo23[14]) {
																															for (const char a15 : combo23) {
																																if (first_round23 || a15 == last_combo23[15]) {
																																	for (const char a16 : combo23) {
																																		if (first_round23 || a16 == last_combo23[16]) {
																																			for (const char a17 : combo23) {
																																				if (first_round23 || a17 == last_combo23[17]) {
																																					for (const char a18 : combo23) {
																																						if (first_round23 || a18 == last_combo23[18]) {
																																							for (const char a19 : combo23) {
																																								if (first_round23 || a19 == last_combo23[19]) {
																																									for (const char a20 : combo23) {
																																										if (first_round23 || a20 == last_combo23[20]) {
																																											for (const char a21 : combo23) {
																																												if (first_round23 || a21 == last_combo23[21]) {
																																													for (const char a22 : combo23) {
																																														if (first_round23 || a22 == last_combo23[22]) {
																																															if (!first_round23) {
																																																first_round23 = true;
																																																continue;
																																															}
																																															password_list23 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << a20 << a21 << a22 << '\n';
																																															--count23;
																																															if (count23 == 0) {
																																																password_list23.close();
																																																last_password23 = last_password23 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22;
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
	return twentyfour_combo(combo23, count23, password_file_name23, nullptr);
}

short twentyfour_combo(const string & combo24, long long & count24, const char * password_file_name24, char * last_combo24) {
	fstream password_list24;
	string last_password24{};
	bool first_round24{ false };
	if (last_combo24 == nullptr) {
		first_round24 = true;
		password_list24.open(password_file_name24, ios::app);
	}
	else {
		password_list24.open(password_file_name24, ios::out);
	}
	for (const char a0 : combo24) {
		if (first_round24 || a0 == last_combo24[0]) {
			for (const char a1 : combo24) {
				if (first_round24 || a1 == last_combo24[1]) {
					for (const char a2 : combo24) {
						if (first_round24 || a2 == last_combo24[2]) {
							for (const char a3 : combo24) {
								if (first_round24 || a3 == last_combo24[3]) {
									for (const char a4 : combo24) {
										if (first_round24 || a4 == last_combo24[4]) {
											for (const char a5 : combo24) {
												if (first_round24 || a5 == last_combo24[5]) {
													for (const char a6 : combo24) {
														if (first_round24 || a6 == last_combo24[6]) {
															for (const char a7 : combo24) {
																if (first_round24 || a7 == last_combo24[7]) {
																	for (const char a8 : combo24) {
																		if (first_round24 || a8 == last_combo24[8]) {
																			for (const char a9 : combo24) {
																				if (first_round24 || a9 == last_combo24[9]) {
																					for (const char a10 : combo24) {
																						if (first_round24 || a10 == last_combo24[10]) {
																							for (const char a11 : combo24) {
																								if (first_round24 || a11 == last_combo24[11]) {
																									for (const char a12 : combo24) {
																										if (first_round24 || a12 == last_combo24[12]) {
																											for (const char a13 : combo24) {
																												if (first_round24 || a13 == last_combo24[13]) {
																													for (const char a14 : combo24) {
																														if (first_round24 || a14 == last_combo24[14]) {
																															for (const char a15 : combo24) {
																																if (first_round24 || a15 == last_combo24[15]) {
																																	for (const char a16 : combo24) {
																																		if (first_round24 || a16 == last_combo24[16]) {
																																			for (const char a17 : combo24) {
																																				if (first_round24 || a17 == last_combo24[17]) {
																																					for (const char a18 : combo24) {
																																						if (first_round24 || a18 == last_combo24[18]) {
																																							for (const char a19 : combo24) {
																																								if (first_round24 || a19 == last_combo24[19]) {
																																									for (const char a20 : combo24) {
																																										if (first_round24 || a20 == last_combo24[20]) {
																																											for (const char a21 : combo24) {
																																												if (first_round24 || a21 == last_combo24[21]) {
																																													for (const char a22 : combo24) {
																																														if (first_round24 || a22 == last_combo24[22]) {
																																															for (const char a23 : combo24) {
																																																if (first_round24 || a23 == last_combo24[23]) {
																																																	if (!first_round24) {
																																																		first_round24 = true;
																																																		continue;
																																																	}
																																																	password_list24 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << a20 << a21 << a22 << a23 << '\n';
																																																	--count24;
																																																	if (count24 == 0) {
																																																		password_list24.close();
																																																		last_password24 = last_password24 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23;
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
	return twentyfive_combo(combo24, count24, password_file_name24, nullptr);
}

short twentyfive_combo(const string & combo25, long long & count25, const char * password_file_name25, char * last_combo25){
	fstream password_list25;
	string last_password25{};
	bool first_round25{ false };
	if (last_combo25 == nullptr) {
		first_round25 = true;
		password_list25.open(password_file_name25, ios::app);
	}
	else {
		password_list25.open(password_file_name25, ios::out);
	}
	for (const char a0 : combo25) {
		if (first_round25 || a0 == last_combo25[0]) {
			for (const char a1 : combo25) {
				if (first_round25 || a1 == last_combo25[1]) {
					for (const char a2 : combo25) {
						if (first_round25 || a2 == last_combo25[2]) {
							for (const char a3 : combo25) {
								if (first_round25 || a3 == last_combo25[3]) {
									for (const char a4 : combo25) {
										if (first_round25 || a4 == last_combo25[4]) {
											for (const char a5 : combo25) {
												if (first_round25 || a5 == last_combo25[5]) {
													for (const char a6 : combo25) {
														if (first_round25 || a6 == last_combo25[6]) {
															for (const char a7 : combo25) {
																if (first_round25 || a7 == last_combo25[7]) {
																	for (const char a8 : combo25) {
																		if (first_round25 || a8 == last_combo25[8]) {
																			for (const char a9 : combo25) {
																				if (first_round25 || a9 == last_combo25[9]) {
																					for (const char a10 : combo25) {
																						if (first_round25 || a10 == last_combo25[10]) {
																							for (const char a11 : combo25) {
																								if (first_round25 || a11 == last_combo25[11]) {
																									for (const char a12 : combo25) {
																										if (first_round25 || a12 == last_combo25[12]) {
																											for (const char a13 : combo25) {
																												if (first_round25 || a13 == last_combo25[13]) {
																													for (const char a14 : combo25) {
																														if (first_round25 || a14 == last_combo25[14]) {
																															for (const char a15 : combo25) {
																																if (first_round25 || a15 == last_combo25[15]) {
																																	for (const char a16 : combo25) {
																																		if (first_round25 || a16 == last_combo25[16]) {
																																			for (const char a17 : combo25) {
																																				if (first_round25 || a17 == last_combo25[17]) {
																																					for (const char a18 : combo25) {
																																						if (first_round25 || a18 == last_combo25[18]) {
																																							for (const char a19 : combo25) {
																																								if (first_round25 || a19 == last_combo25[19]) {
																																									for (const char a20 : combo25) {
																																										if (first_round25 || a20 == last_combo25[20]) {
																																											for (const char a21 : combo25) {
																																												if (first_round25 || a21 == last_combo25[21]) {
																																													for (const char a22 : combo25) {
																																														if (first_round25 || a22 == last_combo25[22]) {
																																															for (const char a23 : combo25) {
																																																if (first_round25 || a23 == last_combo25[23]) {
																																																	for (const char a24 : combo25) {
																																																		if (first_round25 || a24 == last_combo25[24]) {
																																																			if (!first_round25) {
																																																				first_round25 = true;
																																																				continue;
																																																			}
																																																			password_list25 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << a20 << a21 << a22 << a23 << a24 << '\n';
																																																			--count25;
																																																			if (count25 == 0) {
																																																				password_list25.close();
																																																				last_password25 = last_password25 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24;
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
	return twentysix_combo(combo25, count25, password_file_name25, nullptr);
}

short twentysix_combo(const string & combo26, long long & count26, const char * password_file_name26, char * last_combo26){
	fstream password_list26;
	string last_password26{};
	bool first_round26{ false };
	if (last_combo26 == nullptr) {
		first_round26 = true;
		password_list26.open(password_file_name26, ios::app);
	}
	else {
		password_list26.open(password_file_name26, ios::out);
	}
	for (const char a0 : combo26) {
		if (first_round26 || a0 == last_combo26[0]) {
			for (const char a1 : combo26) {
				if (first_round26 || a1 == last_combo26[1]) {
					for (const char a2 : combo26) {
						if (first_round26 || a2 == last_combo26[2]) {
							for (const char a3 : combo26) {
								if (first_round26 || a3 == last_combo26[3]) {
									for (const char a4 : combo26) {
										if (first_round26 || a4 == last_combo26[4]) {
											for (const char a5 : combo26) {
												if (first_round26 || a5 == last_combo26[5]) {
													for (const char a6 : combo26) {
														if (first_round26 || a6 == last_combo26[6]) {
															for (const char a7 : combo26) {
																if (first_round26 || a7 == last_combo26[7]) {
																	for (const char a8 : combo26) {
																		if (first_round26 || a8 == last_combo26[8]) {
																			for (const char a9 : combo26) {
																				if (first_round26 || a9 == last_combo26[9]) {
																					for (const char a10 : combo26) {
																						if (first_round26 || a10 == last_combo26[10]) {
																							for (const char a11 : combo26) {
																								if (first_round26 || a11 == last_combo26[11]) {
																									for (const char a12 : combo26) {
																										if (first_round26 || a12 == last_combo26[12]) {
																											for (const char a13 : combo26) {
																												if (first_round26 || a13 == last_combo26[13]) {
																													for (const char a14 : combo26) {
																														if (first_round26 || a14 == last_combo26[14]) {
																															for (const char a15 : combo26) {
																																if (first_round26 || a15 == last_combo26[15]) {
																																	for (const char a16 : combo26) {
																																		if (first_round26 || a16 == last_combo26[16]) {
																																			for (const char a17 : combo26) {
																																				if (first_round26 || a17 == last_combo26[17]) {
																																					for (const char a18 : combo26) {
																																						if (first_round26 || a18 == last_combo26[18]) {
																																							for (const char a19 : combo26) {
																																								if (first_round26 || a19 == last_combo26[19]) {
																																									for (const char a20 : combo26) {
																																										if (first_round26 || a20 == last_combo26[20]) {
																																											for (const char a21 : combo26) {
																																												if (first_round26 || a21 == last_combo26[21]) {
																																													for (const char a22 : combo26) {
																																														if (first_round26 || a22 == last_combo26[22]) {
																																															for (const char a23 : combo26) {
																																																if (first_round26 || a23 == last_combo26[23]) {
																																																	for (const char a24 : combo26) {
																																																		if (first_round26 || a24 == last_combo26[24]) {
																																																			for (const char a25 : combo26) {
																																																				if (first_round26 || a25 == last_combo26[25]) {
																																																					if (!first_round26) {
																																																						first_round26 = true;
																																																						continue;
																																																					}
																																																					password_list26 << a0 << a1 << a2 << a3 << a4 << a5 << a6 << a7 << a8 << a9 << a10 << a11 << a12 << a13 << a14 << a15 << a16 << a17 << a18 << a19 << a20 << a21 << a22 << a23 << a24 << a25 << '\n';
																																																					--count26;
																																																					if (count26 == 0) {
																																																						password_list26.close();
																																																						last_password26 = last_password26 + a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24 + a25;
																																																						create_progress_file(last_password26);
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
	return twentyseven_combo(combo26, count26, password_file_name26, nullptr);
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

