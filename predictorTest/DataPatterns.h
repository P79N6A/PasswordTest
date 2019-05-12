#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"DataComparison.h"

using namespace std;

class DataPatterns
{
public:
	static vector<DataComparison::patternStructure> rawResults;
	static vector<vector<DataComparison::patternStructure>> splittedResults;
	

	//methods
	static string patterns(string pass);
	static void sortVectorStructOnLength(vector<DataComparison::patternStructure>& x);
	static void sortVectorStructOnLocation(vector<DataComparison::patternStructure>& x);
	static void dividePatterns(vector<DataComparison::patternStructure>& x, string p);
	static void undetected(string p);

	DataPatterns();
	~DataPatterns();
};

