#include "stdafx.h"
#include "DataCleansing.h"


void DataCleansing::delimeterRemover(vector<string>& raw_vector, string delimeter) {//??? parameter as refrence
	string raw_String;
	size_t found;
	for (auto it = raw_vector.begin(); it != raw_vector.end(); it++) {
	again:
		found = it->find(delimeter);
		if (found != string::npos) {
			it->erase(found, 1);
			found = string::npos;
			goto again;
		}
	}
}

//will lowercase
void DataCleansing::lowerCase(vector<string>& raw_data_vector) {
	for (auto it = raw_data_vector.begin(); it != raw_data_vector.end(); it++) {
		transform(it->begin(), it->end(), it->begin(), ::tolower);
	}
}