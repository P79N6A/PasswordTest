#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<fstream>
#include<filesystem>


using namespace std;


//Global Vectors 
vector<string> passwords;
vector<string> emails;
vector<string> email_Names;
vector<string> names;
vector<string> DOB;
vector<string> locations;
vector<string> websites;
vector<string> commons;
vector<string> mobiles;
vector<string> raw_Data_Vector;
vector<string> pattern_Strings_Vector;
vector<pair<pair<bool, string>, pair<int, int>>> comparison_Results;


//Global iterators
vector<string>::iterator raw_Vector_iterator;

//Booleans for Pattern detection
bool name_Bool = false;
bool email_Name_Bool = false;
bool website_Bool = false;
bool DOB_Bool = false;
bool location_Bool = false;
bool mobile_Bool = false;
bool common1_Bool = false;
bool common2_Bool = false;
bool common3_Bool = false;

string name_string;
string email_Name_string;
string website_string;
string DOB_string;
string location_string;
string mobile_string;
string common1_string;
string common2_string;
string common3_string;

//location of detected pattern
int name_loc = -1, name_len = -1;
int email_Name_loc = -1, email_Name_len = -1;
int website_loc = -1, website_len = -1;
int DOB_loc = -1, DOB_len = -1;
int location_loc = -1, location_len = -1;
int mobile_loc = -1, mobile_len = -1;
int common1_loc = -1, common1_len = -1;
int common2_loc = -1, common2_len = -1;
int common3_loc = -1, common3_len = -1;

//filesystem
vector<string> get_all_files_recursive(const string& path) {
	vector<string> file_names;
	using iterator = experimental::filesystem::recursive_directory_iterator;
	for (iterator iter(path); iter != iterator{}; ++iter) {
		file_names.push_back(iter->path().string());
	}
	return file_names;
}

//read file into a vector
void read_File(vector<string>& reading_Vector, string path) {
	cout << " reading File... " << path;
	string str;
	string* ptr = &str;
	ifstream input(path);
	if (!input.is_open()) {
		cout << "file not found(funtion-->readFile)"<<path<<"\n";
	}
	while (getline(input, *ptr)) {
		reading_Vector.push_back(*ptr);
	}
	input.close();
	cout << " Done\n ";
}

//write a file
void write_File(vector<string> writing_Vector, string file_Path) {
	cout << " writing File... " << file_Path;
	ofstream output(file_Path);
	for (auto it = writing_Vector.begin(); it != writing_Vector.end(); it++) {
		output << *it << "\n";
	}
	output.close();
	cout << " Done\n ";
}

//will remove delimeters from RAW data
void delimeter_Test(string path_of_file, string delimeter) {
	cout << " DelimeterTest.......... ";
	//read_File(raw_Data_Vector, path_of_file);
	string raw_String;
	size_t found;
	for (auto it = raw_Data_Vector.begin(); it != raw_Data_Vector.end(); it++) {
	again:
		found = it->find(delimeter);
		if (found != string::npos) {
			it->erase(found, 1);
			found = string::npos;
			goto again;
		}
	}

	//write_File(raw_Data_Vector, "C:\\Users\\atiqg\\Documents\\project\\test1\\predictorTest\\predictorTest\\Output\\raw.txt");
	cout << " Done\n";
}

//will lowercase
void lower_Case() {
	cout << " Lower Casing is...........";
	for (auto it = raw_Data_Vector.begin(); it != raw_Data_Vector.end(); it++) {
		transform(it->begin(), it->end(), it->begin(), ::tolower);
	}
	cout << " Done\n";
}

//Will extract passwords and emails seperately
void extract_Email_and_Passwrod(string delimeter) {
	cout << " Email_and_Password.......... ";
	size_t found, foundDelimeter;
	for (auto it = raw_Data_Vector.begin(); it != raw_Data_Vector.end(); it++) {
		found = it->find("@");
		if (found != string::npos) {
			foundDelimeter = it->find(delimeter, found + 1);
			if (foundDelimeter != string::npos) {
				emails.push_back(it->substr(0, foundDelimeter));
				passwords.push_back(it->substr(foundDelimeter + 1, it->length()-1));
				continue;
			}
		}
	}
	cout << "Done\n";
}

//extract mail_Name and Website from email part
void extract_Email_Names_and_Website() {
	cout << " Email_Names_and_Website.......... ";
	size_t found;
	for (auto it = emails.begin(); it != emails.end(); it++) {
		found = it->find("@");
		if (found != string::npos) {
			if (found != string::npos) {
				email_Names.push_back(it->substr(0, found));
				websites.push_back(it->substr(found + 1, it->length() - 1));
				continue;
			}
		}
	}
	cout << " Done\n";
}

//checks if Name exists in Password
void name_List_Comparison(string pass) {
	cout << " name_List_Comparison.......... ";
	vector<string>::iterator it = names.begin();
	size_t found;
	while (it != names.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			name_Bool = true;
			name_loc = found;
			name_len = it->length();
			name_string = *it;
		}
		it++;
	}
	cout << " Done\n";
}

//checks if email_name exists in Password
void email_Name_List_Comparison(string pass) {
	cout << " email_Name_List_Comparison.......... ";
	vector<string>::iterator it = email_Names.begin();
	size_t found;
	while (it != email_Names.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			email_Name_Bool = true;
			email_Name_loc = found;
			email_Name_len = it->length();
			email_Name_string = *it;
		}
		it++;
	}
	cout << " Done\n";
}

//checks if website exists in Password
void website_List_Comparison(string pass) {
	cout << " website_List_Comparison.......... ";
	vector<string>::iterator it = websites.begin();
	size_t found;
	while (it != websites.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			website_Bool = true;
			website_loc = found;
			website_len = it->length();
			website_string = *it;
		}
		it++;
	}
	cout << " Done\n";
}

//checks if DOB exists in Password
void dob_List_Comparison(string pass) {
	cout << " dob_List_Comparison.......... ";
	vector<string>::iterator it = DOB.begin();
	size_t found;
	while (it != DOB.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			DOB_Bool = true;
			DOB_loc = found;
			DOB_len = it->length();
			DOB_string = *it;
		}
		it++;
	}
	cout << " Done\n";
}

//checks if location exists in Password
void location_List_Comparison(string pass) {
	cout << " locations_List_Comparison.......... ";
	vector<string>::iterator it = locations.begin();
	size_t found;
	while (it != locations.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			location_Bool = true;
			location_loc = found;
			location_len = it->length();
			location_string = *it;
		}
		it++;
	}
	cout << " Done\n";
}

//checks if Mobile Number exists in Password

//checks if Common words exists in Password
void common_Word_List_Comparison(string pass) {
	cout << " common_Word_List_Comparison.......... ";
	vector<string>::iterator it = commons.begin();
	size_t found;
	string rawS1, rawS2;
	while (it != commons.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos && !common1_Bool) {
			common1_Bool = true;
			common1_loc = found;
			common1_len = it->length();
			common1_string = *it;
			rawS1 = pass.substr(0, found);
			rawS2 = pass.substr(found + common1_len, pass.length() - 1);
			found = string::npos;
		}
		found = rawS1.find(*it);
		if (found != string::npos && (common1_Bool && !common2_Bool)) {
			common2_Bool = true;
			common2_loc = found;
			common2_len = it->length();
			common2_string = *it;
			found = string::npos;
		}
		found = rawS2.find(*it);
		if ((found != string::npos && common1_Bool) && (common2_Bool && !common3_Bool)) {
			common3_Bool = true;
			common3_loc = found;
			common3_len = it->length();
			common3_string = *it;
		}
		it++;
	}
}

//Generate pattern by bool variables
string patterns(string pass) {
	cout << " Patterns.......... ";
	comparison_Results.push_back(make_pair(make_pair(name_Bool, "Name/"), make_pair(name_loc, name_len)));
	comparison_Results.push_back(make_pair(make_pair(email_Name_Bool, "Email_Name/"), make_pair(email_Name_loc, email_Name_len)));
	comparison_Results.push_back(make_pair(make_pair(website_Bool, "Website/"), make_pair(website_loc, website_len)));
	comparison_Results.push_back(make_pair(make_pair(DOB_Bool, "DOB/"), make_pair(DOB_loc, DOB_len)));
	comparison_Results.push_back(make_pair(make_pair(location_Bool, "Location/"), make_pair(location_loc, location_len)));
	comparison_Results.push_back(make_pair(make_pair(common1_Bool, "Common1/"), make_pair(common1_loc, common1_len)));
	comparison_Results.push_back(make_pair(make_pair(common2_Bool, "Common2/"), make_pair(common2_loc, common2_len)));
	comparison_Results.push_back(make_pair(make_pair(common3_Bool, "Common3/"), make_pair(common3_loc, common3_len)));

	//sorting comparison_results on its second.first pair value
	sort(comparison_Results.begin(), comparison_Results.end(), [](pair<pair<bool, string>, pair<int, int>> a, pair<pair<bool, string>, pair<int, int>> b) -> bool
	{
		return (a.second.first < b.second.first);
	});
	string final_pattern, rawS1, rawS2;
	for (int it = 0; it != comparison_Results.size(); it++) {
		if (comparison_Results[it].first.first) {
			rawS1 += comparison_Results[it].first.second;
			//P= position L = location
			rawS2 += comparison_Results[it].first.second + "P " + to_string(comparison_Results[it].second.first) + " L " + to_string(comparison_Results[it].second.second) + "/ ";
		}
		//cout << comparison_Results[it].first.second << " ";
	}
	name_Bool = false;
	email_Name_Bool = false;
	website_Bool = false;
	DOB_Bool = false;
	location_Bool = false;
	mobile_Bool = false;
	common1_Bool = false;
	common2_Bool = false;
	common3_Bool = false;
	name_loc = -1, name_len = -1;
	email_Name_loc = -1, email_Name_len = -1;
	website_loc = -1, website_len = -1;
	DOB_loc = -1, DOB_len = -1;
	location_loc = -1, location_len = -1;
	mobile_loc = -1, mobile_len = -1;
	common1_loc = -1, common1_len = -1;
	common2_loc = -1, common2_len = -1;
	common3_loc = -1, common3_len = -1;


	final_pattern = pass + ":- " + rawS1 + " -- " + rawS2;

	return final_pattern;
	cout << "Done\n";
}







int main() {
	int stop_console;
	vector<string> file_list = get_all_files_recursive("C:\\Users\\atiqg\\OneDrive\\Documents\\project\\test1\\predictorTest\\predictorTest\\Input\\");
	vector<string>::iterator file_Path = file_list.begin();
	/*for (auto it = file_list.begin(); it != file_list.end(); it++) {
		cout << *it << "\n";
	}*/
	read_File(names, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/datafiles/names.txt");
	read_File(DOB, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/datafiles/dobs.txt");
	read_File(locations, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/datafiles/locations.txt");
	read_File(commons, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/datafiles/Common.txt");
	
	while (file_Path != file_list.end()) {
		cout << "\n" << " Starting file:" << *file_Path << " \n";
		read_File(raw_Data_Vector, *file_Path);
		lower_Case();
		extract_Email_and_Passwrod(":");
		write_File(emails, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/Output/emails.txt");
		write_File(passwords, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/Output/paswords.txt");
		raw_Data_Vector.clear(); raw_Data_Vector.shrink_to_fit();
		extract_Email_Names_and_Website();
		write_File(email_Names, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/Output/email_names.txt");
		write_File(websites, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/Output/websites.txt");
		//write_File(emails, "C:/Users/atiqg/Documents/project/test1/predictorTest/predictorTest/datafiles/emails.txt");
		//write_File(passwords, "C:/Users/atiqg/Documents/project/test1/predictorTest/predictorTest/datafiles/passwords.txt");
		//write_File(email_Names, "C:/Users/atiqg/Documents/project/test1/predictorTest/predictorTest/datafiles/email_Names.txt");
		//write_File(websites, "C:/Users/atiqg/Documents/project/test1/predictorTest/predictorTest/datafiles/websites.txt");
		raw_Vector_iterator = passwords.begin();
		while (raw_Vector_iterator!=passwords.end())
		{
			name_List_Comparison(*raw_Vector_iterator);
			email_Name_List_Comparison(*raw_Vector_iterator);
			website_List_Comparison(*raw_Vector_iterator);
			dob_List_Comparison(*raw_Vector_iterator);
			location_List_Comparison(*raw_Vector_iterator);
			common_Word_List_Comparison(*raw_Vector_iterator);
			pattern_Strings_Vector.push_back(patterns(*raw_Vector_iterator));
			
			raw_Vector_iterator++;
		}
		write_File(pattern_Strings_Vector, "C:/Users/atiqg/OneDrive/Documents/project/test1/predictorTest/predictorTest/Output/0.txt");
		pattern_Strings_Vector.clear(); pattern_Strings_Vector.shrink_to_fit();
		passwords.clear(); passwords.shrink_to_fit();
		emails.clear(); emails.shrink_to_fit();
		email_Names.clear(); email_Names.shrink_to_fit();
		websites.clear(); websites.shrink_to_fit();


		file_Path++;
	}

	cout << "\n\nProcess is Done";
	cin >> stop_console;
	return 0;
}