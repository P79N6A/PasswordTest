#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class FileHandling
{
public:
	static vector<string> getAllFilesRecursive(vector<string>& file_names, string dir);
	static void readFile(vector<string>& reading_Vector, string path);
	static void writeFile(vector<string>& writing_Vector, string file_Path);
	FileHandling();
	~FileHandling();
};

