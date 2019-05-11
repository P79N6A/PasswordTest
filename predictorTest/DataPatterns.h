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
	string patterns(string pass);
	void sortVectorStructOnLength(vector<DataComparison::patternStructure>& x);
	void sortVectorStructOnLocation(vector<DataComparison::patternStructure>& x);
	void dividePatterns(vector<DataComparison::patternStructure>& x, string p);
	void undetected(string p);

	DataPatterns();
	~DataPatterns();
};

