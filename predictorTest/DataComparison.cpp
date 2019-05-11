#include "stdafx.h"
#include "DataComparison.h"

using namespace std;

vector<string> DataComparison::rawDataList;//raw data readed from Input files 
vector<string> DataComparison::namesList;//vecor to store all common name list
vector<string> DataComparison::dobsList;//vector to store all DOB combination
vector<string> DataComparison::locationsList;//vector to store all locations list
vector<string> DataComparison::commonsList;//vector to store all commons list
vector<string> DataComparison::passwordsList;//vector to store passwords of single files
vector<string> DataComparison::emailsList;//vector to store emails of single files
vector<string> DataComparison::emailNamesList;//vector to store email_names extracted from emails vector
vector<string> DataComparison::websitesList;//vector to store websites extracted from emails vector
vector<string> DataComparison::mobilesList;//
vector<DataComparison::patternStructure> DataComparison::results;

DataComparison::DataComparison()
{
	/*readNamesList("datafiles/names.txt");
	readDobsList("datafiles/dobs.txt");
	readLocationsList("datafiles/locations.txt");
	readCommonsList("datafiles/Common.txt");*/
}


DataComparison::~DataComparison()
{
}

void DataComparison::readNamesList(string filePath) {//parameter refrence
	f.FileHandling::readFile(DataComparison::namesList, filePath);
}

void DataComparison::readDobsList(string filePath) {//parameter refrence
	f.FileHandling::readFile(DataComparison::dobsList, filePath);
}

void DataComparison::readLocationsList(string filePath) {//parameter refrence
	f.FileHandling::readFile(DataComparison::locationsList, filePath);
}

void DataComparison::readCommonsList(string filePath) {//parameter refrence
	f.FileHandling::readFile(DataComparison::commonsList, filePath);
}

void DataComparison::readRawDataList(string filePath) {//parameter refrence
	f.FileHandling::readFile(DataComparison::rawDataList, filePath);
}

void DataComparison::lowerCaseRawDataList() {
	d.lowerCase(DataComparison::rawDataList);
}

void DataComparison::extractEmailAndPassword(string delimiter) {//parameter refrence
	size_t found, foundDelimeter;
	for (auto it = DataComparison::rawDataList.begin(); it != DataComparison::rawDataList.end(); it++) {
		found = it->find("@");
		if (found != string::npos) {
			foundDelimeter = it->find(delimiter, found + 1);
			if (foundDelimeter != string::npos) {
				DataComparison::emailsList.push_back(it->substr(0, foundDelimeter));
				DataComparison::passwordsList.push_back(it->substr(foundDelimeter + 1, it->length() - 1));
				continue;
			}
		}
	}
	DataComparison::rawDataList.clear(); DataComparison::rawDataList.shrink_to_fit();
}


void DataComparison::extractEmailNamesAndWebsites() {
	size_t found;
	for (auto it = DataComparison::emailsList.begin(); it != DataComparison::emailsList.end(); it++) {
		found = it->find("@");
		if (found != string::npos) {
			if (found != string::npos) {
				DataComparison::emailNamesList.push_back(it->substr(0, found));
				DataComparison::websitesList.push_back(it->substr(found + 1, it->length() - 1));
				continue;
			}
		}
	}
	DataComparison::emailsList.clear(); DataComparison::emailsList.shrink_to_fit();
}

//checks if Name exists in Password
void DataComparison::nameListComparison(string pass) {//parameter refrence
	auto it = DataComparison::namesList.begin();
	while (it != DataComparison::namesList.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			DataComparison::results.push_back({ "Name/", *it, static_cast<int>(it->length()), static_cast<int>(found) });
		}
		it++;
	}
}

//checks if email_name exists in Password
void DataComparison::emailNameListComparison(string pass, vector<string>::iterator& pass_it) {//parameter refrence
	string temp = DataComparison::emailNamesList.at(distance(DataComparison::passwordsList.begin(), pass_it));
	size_t found = pass.find(temp);
	if (found != string::npos) {
		DataComparison::results.push_back({ "email_Name/", temp, static_cast<int>(temp.length()), static_cast<int>(found) });
	}
}

//checks if website exists in Password
void DataComparison::websiteListComparison(string pass, vector<string>::iterator& pass_it) {//parameter refrence
	string temp = DataComparison::websitesList.at(distance(DataComparison::passwordsList.begin(), pass_it));
	size_t found = pass.find(temp);
	if (found != string::npos) {
		DataComparison::results.push_back({ "Website/", temp, static_cast<int>(temp.length()), static_cast<int>(found) });
	}
}

//checks if DOB exists in Password
void DataComparison::dobListComparison(string pass) {//parameter refrence
	vector<string>::iterator it = DataComparison::dobsList.begin();
	while (it != DataComparison::dobsList.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			DataComparison::results.push_back({ "DOB/", *it, static_cast<int>(it->length()), static_cast<int>(found) });
		}
		it++;
	}
}

//checks if location exists in Password
void DataComparison::locationListComparison(string pass) {//parameter refrence
	vector<string>::iterator it = DataComparison::locationsList.begin();
	while (it != DataComparison::locationsList.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos) {
			DataComparison::results.push_back({ "Location/", *it, static_cast<int>(it->length()), static_cast<int>(found) });
		}
		it++;
	}
}

//checks if Mobile Number exists in Password

//checks if Common words exists in Password
void DataComparison::commonWordListComparison(string pass) {//parameter refrence 
	vector<string>::iterator it = DataComparison::commonsList.begin();
	string rawS1, rawS2;
	bool flag1 = false, flag2 = false, flag3 = false;
	while (it != DataComparison::commonsList.end()) {
		size_t found = pass.find(*it);
		if (found != string::npos && !flag1) {
			DataComparison::results.push_back({ "Common1/", *it, static_cast<int>(it->length()), static_cast<int>(found) });
			rawS1 = pass.substr(0, found);
			rawS2 = pass.substr(found + it->length(), pass.length() - 1);
			found = string::npos;
			flag1 = true;
		}
		found = rawS1.find(*it);
		if (found != string::npos && (flag1 && !flag2)) {
			DataComparison::results.push_back({ "Common2/", *it, static_cast<int>(it->length()), static_cast<int>(found) });
			found = string::npos;
			flag2 = true;
		}
		found = rawS2.find(*it);
		if ((found != string::npos && flag1) && (flag2 && !flag3)) {
			DataComparison::results.push_back({ "Common3/", *it, static_cast<int>(it->length()), static_cast<int>(found) });
			flag3 = true;
		}
		it++;
	}
	flag1 = false; flag2 = false; flag3 = false;
}

//return vector results
vector<DataComparison::patternStructure> DataComparison::getResults() {
	return DataComparison::results;
}