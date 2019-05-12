#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class DataCleansing
{
public:
	static vector<string> delimeterRemover(vector<string>& raw_vector, string delimeter);
	static void lowerCase(vector<string>& raw_data_vector);
};

