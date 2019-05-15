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
	static void readResources();
	static void readNamesList(string path);
	static void readDobsList(string path);
	static void readLocationsList(string path);
	static void readCommonsList(string path);
	static void readRawDataList(string path);
	static void lowerCaseRawDataList();
	static void extractEmailAndPassword(string delimiter);
	static void extractEmailNamesAndWebsites();
	static void nameListComparison(string pass);
	static void emailNameListComparison(string pass, vector<string>::iterator& pass_it);
	static void websiteListComparison(string pass, vector<string>::iterator& pass_it);
	static void dobListComparison(string pass);
	static void locationListComparison(string pass);
	static void commonWordListComparison(string pass);
	static vector<patternStructure> getResults();

	DataComparison();
	~DataComparison();
};

