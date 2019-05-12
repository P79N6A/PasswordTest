#include "stdafx.h"
#include "DataPatterns.h"


vector<DataComparison::patternStructure> DataPatterns::rawResults;
vector<vector<DataComparison::patternStructure>> DataPatterns::splittedResults;

DataPatterns::DataPatterns()
{
}


DataPatterns::~DataPatterns()
{
}

//Generate pattern by bool variables
string DataPatterns::patterns(string pass) {
	string final_pattern, value_pattern;
	DataPatterns::sortVectorStructOnLength(DataPatterns::rawResults);
	dividePatterns(DataPatterns::rawResults, pass);
	DataPatterns::rawResults.clear(); DataPatterns::rawResults.shrink_to_fit();

	for (size_t i = 0; i < DataPatterns::splittedResults.size(); i++) {
		DataPatterns::sortVectorStructOnLocation(DataPatterns::splittedResults[i]);
	}
	final_pattern += "Password: " + pass + "\n";
	for (size_t i = 0; i < DataPatterns::splittedResults.size(); i++)
	{

		final_pattern += "\t\t\tPattern" + to_string(i + 1) + ": ";
		value_pattern += "\t\t\tValues" + to_string(i + 1) + ": ";
		for (size_t j = 0; j < DataPatterns::splittedResults[i].size(); j++)
		{
			final_pattern += DataPatterns::splittedResults[i][j].key;
			value_pattern += "\"" + DataPatterns::splittedResults[i][j].value + "\"" + " Length:" + to_string(DataPatterns::splittedResults[i][j].len) + " Position:" + to_string(DataPatterns::splittedResults[i][j].loc) + ", ";
		}
		final_pattern += "\n";
		value_pattern += "\n";
	}
	final_pattern += value_pattern;
	for (size_t i = 0; i < DataPatterns::splittedResults.size(); i++) {
		DataPatterns::splittedResults[i].clear(); DataPatterns::splittedResults[i].shrink_to_fit();
	}
	DataPatterns::splittedResults.clear(); DataPatterns::splittedResults.shrink_to_fit();
	return final_pattern;
}

//will sort a vector of structure on length then location
void DataPatterns::sortVectorStructOnLength(vector<DataComparison::patternStructure>& x) {
	sort(x.begin(), x.end(), [](DataComparison::patternStructure a, DataComparison::patternStructure b) -> bool
		{
			if (a.len != b.len) {
				return a.len > b.len;
			}
			else {
				return a.loc < b.loc;
			}
		});
}

//will sort a vector of structure on location then length 
void DataPatterns::sortVectorStructOnLocation(vector<DataComparison::patternStructure>& x) {
	sort(x.begin(), x.end(), [](DataComparison::patternStructure a, DataComparison::patternStructure b) -> bool
		{
			if (a.loc != b.loc) {
				return a.loc < b.loc;
			}
			else {
				return a.len > b.len;
			}
		});
}


//will devide overlapping patterns in results
void DataPatterns::dividePatterns(vector<DataComparison::patternStructure>& x, string p) {
	vector<DataComparison::patternStructure> temp;
	if (x.size() != 0) {
		for (size_t i = 0; i < x.size() - 1; ++i) {
			for (size_t j = i + 1; j < x.size(); ++j) {
				if ((x[j].loc >= x[i].loc) && (x[j].loc <= (x[i].loc + x[i].len - 1))) {
					temp.push_back(x[j]);
					x.erase(x.begin() + j);
					j--;
				}
			}
		}
		if (temp.size() == 0) {
			DataPatterns::splittedResults.push_back(x);
		}
		else {
			DataPatterns::splittedResults.push_back(x);
			return dividePatterns(temp, p);
		}
		undetected(p);
	}
	else
	{
		x.push_back({ "Undetected/", p, int(p.length()), 0 });
		DataPatterns::splittedResults.push_back(x);
	}
}

//will add undetected part into splited results
void DataPatterns::undetected(string p) {

	if (DataPatterns::splittedResults.size() != 0) {
		int p_size = p.length();
		vector<DataComparison::patternStructure> x_i_temp;
		for (size_t i = 0; i < DataPatterns::splittedResults.size(); i++) {
			int x_i_size = DataPatterns::splittedResults[i].size();
			if (DataPatterns::splittedResults[i][0].loc != 0) {
				x_i_temp.push_back({ "Undetected/", p.substr(0, DataPatterns::splittedResults[i][0].loc), DataPatterns::splittedResults[i][0].loc, 0 });
			}
			for (int j = 0; j < x_i_size - 1; j++) {
				if ((DataPatterns::splittedResults[i][j + 1].loc - (DataPatterns::splittedResults[i][j].loc + DataPatterns::splittedResults[i][j].len - 1) - 1) > 0) {
					x_i_temp.push_back({ "Undetected/", p.substr((DataPatterns::splittedResults[i][j].loc + DataPatterns::splittedResults[i][j].len), (DataPatterns::splittedResults[i][j + 1].loc - (DataPatterns::splittedResults[i][j].loc + DataPatterns::splittedResults[i][j].len - 1) - 1)), (DataPatterns::splittedResults[i][j + 1].loc - (DataPatterns::splittedResults[i][j].loc + DataPatterns::splittedResults[i][j].len - 1) - 1), (DataPatterns::splittedResults[i][j].loc + DataPatterns::splittedResults[i][j].len) });
				}
			}
			if ((DataPatterns::splittedResults[i][x_i_size - 1].loc + DataPatterns::splittedResults[i][x_i_size - 1].len) != p_size) {
				x_i_temp.push_back({ "Undetected/", p.substr((DataPatterns::splittedResults[i][x_i_size - 1].loc + DataPatterns::splittedResults[i][x_i_size - 1].len), (p_size - (DataPatterns::splittedResults[i][x_i_size - 1].loc + DataPatterns::splittedResults[i][x_i_size - 1].len))), (p_size - (DataPatterns::splittedResults[i][x_i_size - 1].loc + DataPatterns::splittedResults[i][x_i_size - 1].len)), (DataPatterns::splittedResults[i][x_i_size - 1].loc + DataPatterns::splittedResults[i][x_i_size - 1].len ) });
			}
			DataPatterns::splittedResults[i].insert(DataPatterns::splittedResults[i].end(), x_i_temp.begin(), x_i_temp.end());
			x_i_temp.clear(); x_i_temp.shrink_to_fit();
		}
	}
}