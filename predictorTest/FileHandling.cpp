#include "stdafx.h"
#include "FileHandling.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>


FileHandling::FileHandling()
{
}


FileHandling::~FileHandling()
{
}

//read a file
void FileHandling::readFile(vector<string>& reading_Vector, string file_path) {//??? parameter should be refrenced
	string str;
	string* ptr = &str;
	ifstream input(file_path);
	if (!input.is_open()) {
		cout << "file not found(funtion-->readFile)" << file_path << "\n";
	}
	while (getline(input, *ptr)) {
		reading_Vector.push_back(*ptr);
	}
	input.close();
}

//write a file
void FileHandling::writeFile(vector<string>& writing_Vector, string file_Path) {//??? parameter should be refrenced
	ofstream output(file_Path);
	for (auto it = writing_Vector.begin(); it != writing_Vector.end(); it++) {
		output << *it << "\n";
	}
	output.close();
}

vector<string> FileHandling::getAllFilesRecursive(vector<string>& file_names,string dir) {//??? parameter should be refrenced
	for (const auto& entry : filesystem::directory_iterator(dir))
		file_names.push_back(entry.path().string());
	return file_names;
}
