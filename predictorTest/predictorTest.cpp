#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <chrono>
//#include<thread>
//Myheaders
#include"FileHandling.h"
#include"DataComparison.h"
#include"DataPatterns.h"


using namespace std;


void programFlow() {
	vector<string> filePaths;
	vector<string> patternStringsVector;
	vector<string>::iterator rawIterator;
	FileHandling::getAllFilesRecursive(filePaths, "Input/");
	vector<string>::iterator file = filePaths.begin();
	DataComparison::readResources();
	cout << "\n Names, Dob, Locations and Commons files are readed \n";

	while (file != filePaths.end()) {
		cout << "\n" << " Starting file:" << *file << " \n";
		DataComparison::readRawDataList(*file);
		DataComparison::lowerCaseRawDataList();
		DataComparison::extractEmailAndPassword(":");
		DataComparison::extractEmailNamesAndWebsites();
		rawIterator = DataComparison::passwordsList.begin();
		while (rawIterator != DataComparison::passwordsList.end())
		{
			DataComparison::nameListComparison(*rawIterator);
			DataComparison::emailNameListComparison(*rawIterator, rawIterator);
			DataComparison::websiteListComparison(*rawIterator, rawIterator);
			DataComparison::dobListComparison(*rawIterator);
			DataComparison::locationListComparison(*rawIterator);
			DataComparison::commonWordListComparison(*rawIterator);
			DataPatterns::rawResults = DataComparison::getResults();
			DataComparison::results.clear();  DataComparison::results.shrink_to_fit();
			patternStringsVector.push_back(DataPatterns::patterns(*rawIterator));
			rawIterator++;
		}
		DataComparison::passwordsList.clear(); DataComparison::passwordsList.shrink_to_fit();
		DataComparison::emailNamesList.clear(); DataComparison::emailNamesList.shrink_to_fit();
		DataComparison::websitesList.clear(); DataComparison::websitesList.shrink_to_fit();
		FileHandling::writeFile(patternStringsVector, "Output/0.txt");
		file++;
	}
	patternStringsVector.clear(); patternStringsVector.shrink_to_fit();
	//sad
	cout << "\n\nProcess is Done";
}

void experimentProgramFlow() {
	vector<string> filePaths;
	vector<string> patternStringsVector;
	vector<string>::iterator rawIterator;
	FileHandling::getAllFilesRecursive(filePaths, "Input/");
	vector<string>::iterator file = filePaths.begin();
	DataComparison::readResources();
	cout << "\n Names, Dob, Locations and Commons files are readed \n";

	while (file != filePaths.end()) {
		cout << "\n" << " Starting file:" << *file << " \n";
		ifstream input(*file);
		if (!input.is_open()) {
			cout << "file not found(funtion-->readFile)" << *file << "\n";
			break;
		}
		else {
			input.seekg(0, input.end);
			int lengthOfBuffer = input.tellg();
			input.seekg(0, input.beg);
			char* buffer = new char[lengthOfBuffer];
			input.read(buffer, lengthOfBuffer);
			input.close();
			string tempStr;
			auto bufferIt = buffer;
			while (lengthOfBuffer!=0) {
				while (*bufferIt != '\n') {
					tempStr += *bufferIt;
					bufferIt++;
				}
				DataCleansing::expLowerCase(tempStr);
				DataComparison::expExtractEmailAndPassword(tempStr, ":");
				DataComparison::expExtractEmailNameAndWebsite();
				DataComparison::expEmailNameListCoparison();
				DataComparison::expWebsiteListComparison();
				DataComparison::nameListComparison(DataComparison::password);
				DataComparison::dobListComparison(tempStr);
				DataComparison::locationListComparison(tempStr);
				DataComparison::commonWordListComparison(tempStr);
				DataPatterns::rawResults = DataComparison::getResults();
				DataComparison::results.clear();  DataComparison::results.shrink_to_fit();
				patternStringsVector.push_back(DataPatterns::patterns(tempStr));
				tempStr.clear(); tempStr.shrink_to_fit();
				bufferIt++;
				lengthOfBuffer--;
			}
			delete[] buffer;
		}
		//input.close();
		file++;
	}
	patternStringsVector.clear(); patternStringsVector.shrink_to_fit();
	//sad
	cout << "\n\nProcess is Done";
}






int main() {
	auto start = std::chrono::high_resolution_clock::now();
	programFlow();
	//experimentProgramFlow();
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	return 0;
}
