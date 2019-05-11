#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "FileHandling.h"
#include "DataCleansing.h"

using namespace std;

class DataComparison
{
public:
	static vector<string> rawDataList;//raw data readed from Input files 
	static vector<string> namesList;//vecor to store all common name list
	static vector<string> dobsList;//vector to store all DOB combination
	static vector<string> locationsList;//vector to store all locations list
	static vector<string> commonsList;//vector to store all commons list
	static vector<string> passwordsList;//vector to store passwords of single files
	static vector<string> emailsList;//vector to store emails of single files
	static vector<string> emailNamesList;//vector to store email_names extracted from emails vector
	static vector<string> websitesList;//vector to store websites extracted from emails vector
	static vector<string> mobilesList;//
	struct patternStructure {
		string key;
		string value;
		int len;
		int loc;
	};
	static vector<patternStructure> results;

	//methods 
	void readNamesList(string path);
	void readDobsList(string path);
	void readLocationsList(string path);
	void readCommonsList(string path);
	void readRawDataList(string path);
	void lowerCaseRawDataList();
	void extractEmailAndPassword(string delimiter);
	void extractEmailNamesAndWebsites();
	void nameListComparison(string pass);
	void emailNameListComparison(string pass, vector<string>::iterator& pass_it);
	void websiteListComparison(string pass, vector<string>::iterator& pass_it);
	void dobListComparison(string pass);
	void locationListComparison(string pass);
	void commonWordListComparison(string pass);
	vector<patternStructure> getResults();
	DataComparison();
	~DataComparison();

private:
	FileHandling f;
	DataCleansing d;
	

};

