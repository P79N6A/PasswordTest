#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class DataCleansing
{
public:
	static void delimeterRemover(vector<string>& raw_vector, string delimeter);
	static void lowerCase(vector<string>& raw_data_vector);
	//Experiment
	static void expLowerCase(string& str);

};

