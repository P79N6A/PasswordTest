#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class FileHandling
{
public:
	vector<string> getAllFilesRecursive(vector<string>& file_names, string dir);
	void readFile(vector<string>& reading_Vector, string path);
	void writeFile(vector<string>& writing_Vector, string file_Path);
	FileHandling();
	~FileHandling();
};

